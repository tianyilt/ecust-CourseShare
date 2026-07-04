from __future__ import annotations

from contextlib import asynccontextmanager
from pathlib import Path
from io import BytesIO
import logging
from PIL import Image
from typing import Callable, Dict, List

import cv2
import numpy as np
from fastapi import FastAPI, HTTPException
from fastapi.middleware.cors import CORSMiddleware
from fastapi.staticfiles import StaticFiles

BASE_DIR = Path(__file__).resolve().parent
DATA_DIR = BASE_DIR / "data"
OUTPUT_DIR = BASE_DIR / "output"
SOURCE_IMAGE = DATA_DIR / "test.png"

@asynccontextmanager
async def lifespan(app: FastAPI):
    # Precompute enhanced variants for fast serving
    app.state.images = generate_outputs()
    yield

app = FastAPI(title="Fill Light API", version="0.1.0", lifespan=lifespan)

app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)


# Simple gamma curve

def gamma_boost(image: np.ndarray, gamma: float = 1.6) -> np.ndarray:
    inv_gamma = 1.0 / gamma
    table = (np.linspace(0, 1, 256) ** inv_gamma) * 255.0
    lut = table.astype(np.uint8)
    return cv2.LUT(image, lut)


# Contrast Limited Adaptive Histogram Equalization in LAB space

def clahe_boost(image: np.ndarray) -> np.ndarray:
    lab = cv2.cvtColor(image, cv2.COLOR_BGR2LAB)
    l, a, b = cv2.split(lab)
    clahe = cv2.createCLAHE(clipLimit=3.0, tileGridSize=(8, 8))
    l_eq = clahe.apply(l)
    lab_eq = cv2.merge((l_eq, a, b))
    return cv2.cvtColor(lab_eq, cv2.COLOR_LAB2BGR)


# Warm fill light using HSV lift and slight color balance

def warm_fill(image: np.ndarray, lift: float = 0.18, saturation: float = 1.06) -> np.ndarray:
    hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV).astype(np.float32)
    h, s, v = cv2.split(hsv)
    v = np.clip(v + lift * 255.0, 0, 255)
    s = np.clip(s * saturation, 0, 255)
    hsv_boost = cv2.merge((h, s, v)).astype(np.uint8)
    boosted = cv2.cvtColor(hsv_boost, cv2.COLOR_HSV2BGR)
    # Soft light blend for a gentle contrast lift
    blend = cv2.addWeighted(boosted, 0.85, image, 0.15, 0)
    return blend


Enhancer = Dict[str, str]


def generate_outputs() -> List[Enhancer]:
    if not SOURCE_IMAGE.exists():
        raise FileNotFoundError(
            f"Source image not found at {SOURCE_IMAGE}. Place test.png there and restart."
        )

    OUTPUT_DIR.mkdir(parents=True, exist_ok=True)
    # Robust read: try reading bytes then decode with imdecode. Add diagnostics on failure.
    try:
        data = Path(SOURCE_IMAGE).read_bytes()
    except Exception as exc:
        raise RuntimeError(f"Cannot read source image bytes: {exc}")

    size = len(data)
    # save a raw debug copy so user can inspect the bytes if needed
    try:
        (OUTPUT_DIR / "debug_source.bin").write_bytes(data)
        # also try saving as png so explorer can open it directly
        try:
            (OUTPUT_DIR / "debug_source.png").write_bytes(data)
        except Exception:
            pass
    except Exception:
        pass

    # Print diagnostics to console and to a file
    try:
        header = data[:16]
        header_hex = header.hex()
    except Exception:
        header_hex = ""

    info = (
        f"Reading source={SOURCE_IMAGE} size={size} bytes, header={header_hex}, "
        f"cv2={cv2.__version__}, numpy={np.__version__}"
    )
    print(info)
    try:
        (OUTPUT_DIR / "load_info.txt").write_text(info)
    except Exception:
        pass

    arr = np.frombuffer(data, dtype=np.uint8)
    image = cv2.imdecode(arr, cv2.IMREAD_COLOR)
    if image is None:
        print("cv2.imdecode returned None, attempting PIL fallback...")
        # Try PIL fallback
        try:
            pil_img = Image.open(BytesIO(data)).convert("RGB")
            image = cv2.cvtColor(np.array(pil_img), cv2.COLOR_RGB2BGR)
            print("PIL fallback succeeded")
            try:
                (OUTPUT_DIR / "debug_from_pil.jpg").write_bytes(cv2.imencode('.jpg', image)[1].tobytes())
            except Exception:
                pass
        except Exception as exc:
            err_msg = (
                f"imdecode failed and PIL fallback failed: {exc}. source_path={SOURCE_IMAGE!s}, size={size}, arr_len={arr.size}"
            )
            print(err_msg)
            try:
                (OUTPUT_DIR / "load_error.txt").write_text(err_msg)
            except Exception:
                pass
            raise RuntimeError("Unable to read source image. Check file integrity. " + err_msg)

    enhancers: List[Dict[str, Callable[[np.ndarray], np.ndarray]]] = [
        {"key": "gamma", "name": "Gamma", "fn": lambda img: gamma_boost(img, gamma=1.6)},
        {"key": "clahe", "name": "CLAHE", "fn": clahe_boost},
        {"key": "warm", "name": "Warm Fill", "fn": warm_fill},
    ]

    results: List[Enhancer] = []

    original_path = OUTPUT_DIR / "original.jpg"
    try:
        ok = cv2.imwrite(str(original_path), image)
    except Exception as exc:
        ok = False
        print(f"cv2.imwrite raised: {exc}")

    if not ok:
        print("cv2.imwrite failed for original.jpg, attempting PIL save fallback...")
        try:
            pil = Image.fromarray(cv2.cvtColor(image, cv2.COLOR_BGR2RGB))
            pil.save(str(original_path), format="JPEG", quality=95)
            ok = True
            print("PIL save succeeded for original.jpg")
        except Exception as exc:
            print(f"PIL fallback save failed: {exc}")

    results.append({"key": "original", "name": "Original", "url": f"/images/{original_path.name}"})

    for enhancer in enhancers:
        output_path = OUTPUT_DIR / f"{enhancer['key']}.jpg"
        enhanced = enhancer["fn"](image)
        try:
            ok2 = cv2.imwrite(str(output_path), enhanced)
        except Exception as exc:
            ok2 = False
            print(f"cv2.imwrite raised for {output_path.name}: {exc}")

        if not ok2:
            print(f"cv2.imwrite failed for {output_path.name}, attempting PIL fallback...")
            try:
                pil2 = Image.fromarray(cv2.cvtColor(enhanced, cv2.COLOR_BGR2RGB))
                pil2.save(str(output_path), format="JPEG", quality=92)
                print(f"PIL save succeeded for {output_path.name}")
            except Exception as exc:
                print(f"PIL fallback save failed for {output_path.name}: {exc}")
        results.append(
            {"key": enhancer["key"], "name": enhancer["name"], "url": f"/images/{output_path.name}"}
        )

    return results


@asynccontextmanager
async def lifespan(app: FastAPI):
    # Precompute enhanced variants for fast serving
    app.state.images = generate_outputs()
    yield


@app.get("/health")
def health() -> dict:
    return {"status": "ok"}


@app.get("/images")
def list_images() -> List[Enhancer]:
    try:
        return app.state.images
    except Exception as exc:  # pragma: no cover - defensive for startup issues
        raise HTTPException(status_code=500, detail=str(exc))


app.mount("/images", StaticFiles(directory=OUTPUT_DIR), name="images")


if __name__ == "__main__":
    import uvicorn

    uvicorn.run(app, host="0.0.0.0", port=8000)