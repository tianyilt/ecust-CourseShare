import importlib.util
import os
from typing import Callable, Tuple


ROUNDS_PER_MATCH = 200
FILE_1 = "25013515_吕家宝.py"
FILE_2 = "25013515_吕家宝2.py"


def load_strategy(file_path: str, module_tag: str) -> Callable[[list, list], str]:
    spec = importlib.util.spec_from_file_location(module_tag, file_path)
    if spec is None or spec.loader is None:
        raise RuntimeError(f"无法加载文件: {file_path}")

    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)

    strategy = getattr(module, "my_strategy", None)
    if not callable(strategy):
        raise RuntimeError(f"文件中未找到可调用的 my_strategy: {file_path}")
    return strategy


def score_round(action1: str, action2: str) -> Tuple[int, int]:
    if action1 == "C" and action2 == "C":
        return 3, 3
    if action1 == "D" and action2 == "D":
        return 1, 1
    if action1 == "D" and action2 == "C":
        return 5, 0
    if action1 == "C" and action2 == "D":
        return 0, 5
    raise ValueError(f"非法动作: 1方={action1}, 2方={action2}")


def run_one_match(file1: str, file2: str, rounds: int = ROUNDS_PER_MATCH) -> Tuple[int, int]:
    # 每场重新加载策略，避免全局变量跨场污染
    strategy1 = load_strategy(file1, "player_one")
    strategy2 = load_strategy(file2, "player_two")

    history1 = []
    history2 = []
    total1 = 0
    total2 = 0

    for _ in range(rounds):
        action1 = strategy1(history1, history2)
        action2 = strategy2(history2, history1)

        if action1 not in ("C", "D"):
            raise ValueError(f"1方返回非法动作: {action1}")
        if action2 not in ("C", "D"):
            raise ValueError(f"2方返回非法动作: {action2}")

        s1, s2 = score_round(action1, action2)
        total1 += s1
        total2 += s2

        history1.append(action1)
        history2.append(action2)

    return total1, total2


def main() -> None:
    base_dir = os.path.dirname(os.path.abspath(__file__))
    file1 = os.path.join(base_dir, FILE_1)
    file2 = os.path.join(base_dir, FILE_2)

    if not os.path.exists(file1):
        raise FileNotFoundError(f"找不到1方策略文件: {file1}")
    if not os.path.exists(file2):
        raise FileNotFoundError(f"找不到2方策略文件: {file2}")

    try:
        matches = int(input(f"请输入对战场数（每场{ROUNDS_PER_MATCH}轮）: ").strip())
        if matches <= 0:
            raise ValueError
    except ValueError:
        print("输入无效：请输入正整数场数。")
        return

    win1 = 0
    win2 = 0
    draw = 0

    print("\n开始擂台模拟...\n" + "-" * 40)

    for idx in range(1, matches + 1):
        score1, score2 = run_one_match(file1, file2, ROUNDS_PER_MATCH)

        if score1 > score2:
            win1 += 1
            result = "1方胜"
        elif score2 > score1:
            win2 += 1
            result = "2方胜"
        else:
            draw += 1
            result = "平局"

        print(f"第{idx}场：1方={score1} 分，2方={score2} 分，结果：{result}")

    print("-" * 40)
    print("统计结果：")
    print(f"1方获胜次数：{win1}")
    print(f"2方获胜次数：{win2}")
    print(f"平局次数：{draw}")


if __name__ == "__main__":
    main()
