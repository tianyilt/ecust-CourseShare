from tkinter import Tk
import tkinter as tk
from tkinter import ttk
import datetime
import math
import sqlite3

地址 = r"这里填入数据库的绝对路径"

main = Tk()
main.wm_title("电子商务")
main.wm_geometry("800x600")
ttk.Label(main, text="产品名称").pack()
产品名称 = ttk.Entry(main)
产品名称.pack()
产品数量 = ttk.Entry(main)
ttk.Label(main, text="产品数量").pack()
产品数量.pack()
ttk.Label(main, text="交付日期,yyyy-mm-dd").pack()
交付日期 = ttk.Entry(main)
交付日期.pack_configure()

# ---


def search():
    global ansList
    # product_name1 = "眼镜"
    product_name1 = 产品名称.get()
    # number1 = 100
    number1 = int(产品数量.get())
    # year, month, day = 2020, 12, 20
    year, month, day = map(int, 交付日期.get().split("-"))
    sub_material(product_name1, 1, int(number1))
    for item in ansList:
        item[2] = math.ceil(item[2])
    warehouse_List = [list(item[:2]) for item in c.execute("select 子物料名称,工序库存+资材库存 from temp")]  # 获得仓库的原料存储情况
    ansList = sorted(ansList, key=lambda x: x[1], reverse=True)  # 反向排序，避免碰撞
    for item in warehouse_List:
        if item[1] != 0:
            for material_item in ansList:
                if item[0] == material_item[0]:
                    temp = min(item[1], material_item[2])
                    item[1] -= temp
                    material_item[2] -= temp
    plan_show(产品名称.get(), year, month, day)
    ansList.clear()


# ---

ttk.Button(main, text="确认", command=search).pack_configure()
show_listbox = tk.Listbox(main)
show_listbox.pack_configure(expand=True, padx=10, pady=10, fill=tk.BOTH)
# ---

conn = sqlite3.connect(地址)
c = conn.cursor()
ansList = []


def sub_material(产品名称: str, 提前天数, 父物料需求数):
    """

    产品名称: 产品名称

    提前天数: 提前日期

    父物料需求数: 产品数量

    """
    sub_material_l = c.execute("select 子物料名称 from temp where 父物料名称=?", (产品名称,)).fetchall()
    ansList.append([产品名称, 提前天数, 父物料需求数])
    if len(sub_material_l) != 0:
        for item in sub_material_l:
            构成数 = c.execute("select 构成数 from temp where 父物料名称=? and 子物料名称=?", (产品名称, item[0])).fetchone()[0]
            损耗率 = c.execute("select 损耗率 from temp where 子物料名称=?", (item[0],)).fetchone()[0]
            day_list = c.execute(
                "select 作业提前期,配料提前期,供应商提前期 from temp where 父物料名称=? and 子物料名称=?",
                (产品名称, item[0]),
            ).fetchone()
            sub_material(item[0], 提前天数 + sum(day_list), 父物料需求数 * 构成数 / (1.0 - 损耗率))


def date_calculate(year, month, day, pre提前天数):
    return datetime.date(year, month, day) - datetime.timedelta(pre提前天数)


def plan_show(plan_name: str, year: int, month: int, day: int):
    for index, item in enumerate(ansList):
        after_提前天数 = c.execute("select 作业提前期+配料提前期+供应商提前期 from temp where 子物料名称=?", (item[0],)).fetchone()[0]
        method = c.execute("select 调配方式 from temp where 子物料名称=?", (item[0],)).fetchone()[0]
        show_listbox.insert(
            index,
            f"{item[0]} {method} {date_calculate(year, month, day, item[1])} {date_calculate(year, month, day, item[1] - after_提前天数)} {item[2]}",
        )


main.mainloop()
conn.close()
