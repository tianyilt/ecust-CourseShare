"""
问题一：9种情景批量求解（CP-SAT版本）
- 去除 K 约束
- 出口编号 35
- 自动适配 CSV 编码
- 性能优化（预裁剪、对称性破除）
"""
import os
import math
import pandas as pd
from ortools.sat.python import cp_model

# ================== 全局参数 ==================
DATA_DIR = "data"
SCALE = 1000                     # 目标系数放大倍数（保证整数）
SOLVE_TIME_LIMIT = 300           # 单次求解最大时间（秒）

# ================== 辅助：自动编码读取 CSV ==================
def read_csv_auto(filepath, **kwargs):
    """尝试 utf-8, gbk, gb18030 编码读取 CSV"""
    for enc in ['utf-8-sig', 'utf-8', 'gbk', 'gb18030']:
        try:
            return pd.read_csv(filepath, encoding=enc, **kwargs)
        except UnicodeDecodeError:
            continue
    raise UnicodeDecodeError(f"无法解码文件 {filepath}，请检查编码。")

# ================== 数据读取（只读一次） ==================
print("读取数据...")
nodes_df = read_csv_auto(os.path.join(DATA_DIR, "nodes.csv"))
performs_df = read_csv_auto(os.path.join(DATA_DIR, "performs.csv"))
walk_orig = read_csv_auto(os.path.join(DATA_DIR, "walk_matrix.csv"), index_col=0)
walk_orig = walk_orig.values.tolist()
wait_df = read_csv_auto(os.path.join(DATA_DIR, "wait_time.csv")).set_index('node_id')
benefit_df = read_csv_auto(os.path.join(DATA_DIR, "benefit.csv")).set_index('node_id')
settings = read_csv_auto(os.path.join(DATA_DIR, "settings.csv"))
params = dict(zip(settings['param'], settings['value']))
T = int(params['T'])
lam = float(params['lambda'])

# 步行时间四舍五入为整数
for i in range(len(walk_orig)):
    for j in range(len(walk_orig)):
        walk_orig[i][j] = round(walk_orig[i][j])

# ================== 节点扩充（与情景无关） ==================
print("扩充节点...")
expanded_nodes = []          # 每个元素 dict
show_groups = []             # 每个元素 list，同一演出的场次 exp_id

# 入口
expanded_nodes.append({
    'exp_id': 0, 'orig_id': 0, 'name': '入口', 'play': 0, 'E': 0, 'L': 0, 'is_show': False
})

# 遍历原始节点（跳过入口0和出口35）
for _, row in nodes_df.iterrows():
    nid = row['node_id']
    if nid == 0 or nid == 35:
        continue
    is_show = (row['is_show'] == 1)
    if is_show:
        perfs = performs_df[performs_df['show_node_id'] == nid]
        if len(perfs) == 0:
            raise ValueError(f"演出节点 {nid} 缺少场次数据！")
        group_ids = []
        for _, pf in perfs.iterrows():
            new_id = len(expanded_nodes)
            expanded_nodes.append({
                'exp_id': new_id,
                'orig_id': nid,
                'name': f"{row['name']}(场{int(pf['perform_id'])})",
                'play': round(row['play_time']),
                'E': int(pf['start_time']),
                'L': int(pf['start_time']),
                'is_show': True
            })
            group_ids.append(new_id)
        show_groups.append(group_ids)
    else:
        new_id = len(expanded_nodes)
        E_val = int(row['E_time']) if not pd.isna(row['E_time']) else 0
        L_val = int(row['L_time']) if not pd.isna(row['L_time']) else T
        expanded_nodes.append({
            'exp_id': new_id,
            'orig_id': nid,
            'name': row['name'],
            'play': round(row['play_time']),
            'E': E_val,
            'L': L_val,
            'is_show': False
        })

# 出口（orig_id=35）
exit_id = len(expanded_nodes)
expanded_nodes.append({
    'exp_id': exit_id, 'orig_id': 35, 'name': '出口', 'play': 0, 'E': 0, 'L': 0, 'is_show': False
})

n_total = len(expanded_nodes)
IN = 0
OUT = exit_id

# 构建扩充后的步行矩阵
walk = [[0] * n_total for _ in range(n_total)]
for i_node in expanded_nodes:
    for j_node in expanded_nodes:
        if i_node['exp_id'] == j_node['exp_id']:
            continue
        walk[i_node['exp_id']][j_node['exp_id']] = walk_orig[i_node['orig_id']][j_node['orig_id']]

# 原始排队和收益字典
orig_wait_dict = wait_df.to_dict(orient='index')
orig_benefit_dict = benefit_df.to_dict(orient='index')

# ================== 情景组合 ==================
date_types = ['weekday', 'weekend', 'holiday']
tourist_types = ['normal', 'family', 'couple']

# 结果容器
results_summary = []

# ================== 主循环 ==================
output_file = "results_problem1.txt"
with open(output_file, 'w', encoding='utf-8') as f_out:
    f_out.write("========== 问题一：9种情景求解结果 ==========\n\n")

    for date in date_types:
        for tourist in tourist_types:
            scenario = f"日期:{date}  游客类型:{tourist}"
            print(f"正在求解：{scenario} ...")
            f_out.write(f"---------- {scenario} ----------\n")

            # ---- 按情景准备排队和收益 ----
            wait = [0] * n_total
            p_raw = [0] * n_total
            for i in range(n_total):
                orig_id = expanded_nodes[i]['orig_id']
                wait[i] = round(orig_wait_dict[orig_id][date])
                p_raw[i] = orig_benefit_dict[orig_id][tourist]

            # 目标系数整数化
            lam_scaled = round(lam * SCALE)
            p_scaled = [int(round(p * SCALE)) for p in p_raw]

            # ---- 构建模型 ----
            model = cp_model.CpModel()

            # ---- 变量 y ----
            y = {}
            # 预裁剪：步行时间超过 60 分钟且不是必经的边可删除（考虑时间限制 T=780，步行 60 分钟占太大比例）
            WALK_CUTOFF = 60  # 可根据数据调整
            for i in range(n_total):
                if i == OUT:
                    continue
                for j in range(n_total):
                    if j == IN or i == j:
                        continue
                    # 预裁剪条件：步行时间过大且不是从入口出发的唯一必要（入口/出口可保留）
                    if walk[i][j] > WALK_CUTOFF:
                        # 入口出发或到达出口保留，其他边裁剪
                        if i == IN or j == OUT:
                            pass  # 保留
                        else:
                            continue  # 裁剪这条边
                    y[i, j] = model.NewBoolVar(f'y_{i}_{j}')

            # 时间变量 t[i]（开始游玩时刻）
            max_play = max(node['play'] for node in expanded_nodes)
            max_walk = max(walk[i][j] for (i, j) in y) if y else 0
            t_max = T + max_walk + max(wait) + max_play + 100
            t = [model.NewIntVar(0, t_max, f't_{i}') for i in range(n_total)]
            model.Add(t[IN] == 0)

            # ---- 约束 ----
            # C1: 起点终点唯一
            model.Add(sum(y[IN, j] for j in range(n_total) if (IN, j) in y) == 1)
            model.Add(sum(y[i, OUT] for i in range(n_total) if (i, OUT) in y) == 1)

            # C3: 中间节点流量守恒且最多访问一次
            for k in range(1, OUT):
                in_edges = [y[i, k] for i in range(n_total) if (i, k) in y]
                out_edges = [y[k, j] for j in range(n_total) if (k, j) in y]
                if not in_edges:  # 可能被裁剪导致无入边，则该节点不可能被访问
                    continue
                model.Add(sum(in_edges) <= 1)
                model.Add(sum(in_edges) == sum(out_edges))

            # 注意：删除了 K 约束，不再限制总项目数

            # C4: 时间递推（使用紧致大 M）
            if y:
                max_walk_used = max(walk[i][j] for (i, j) in y)
                M_val = T + max_walk_used + max(wait) + max_play + 100
            else:
                M_val = T + 100
            for (i, j), y_var in y.items():
                model.Add(t[j] >= t[i] + wait[j] + expanded_nodes[i]['play'] + walk[i][j]
                          - M_val * (1 - y_var))

            # C5: 出口时间不超闭园
            model.Add(t[OUT] <= T)

            # C6: 时间窗（所有中间节点）
            for i in range(1, OUT):
                in_edges_i = [y[k, i] for k in range(n_total) if (k, i) in y]
                if not in_edges_i:   # 该节点不可达
                    continue
                is_visited = sum(in_edges_i)
                model.Add(t[i] >= expanded_nodes[i]['E'] - M_val * (1 - is_visited))
                model.Add(t[i] <= expanded_nodes[i]['L'] + M_val * (1 - is_visited))

            # 演出互斥组：同一演出不同场次最多选一
            for group in show_groups:
                group_visits = [sum(y[k, node] for k in range(n_total) if (k, node) in y)
                                for node in group]
                # 过滤掉可能没有入边的节点
                group_visits = [v for v in group_visits if v is not None]
                if group_visits:
                    model.Add(sum(group_visits) <= 1)

            # 对称性破除：同组内优先早场（visit[早] >= visit[晚]）
            for group in show_groups:
                # 按开始时间升序排列（已经在构建时按场次顺序，假设 perform_id 从小到大是时间先后）
                for idx in range(len(group) - 1):
                    # 获取早场和晚场的访问指示变量
                    early_visit = sum(y[k, group[idx]] for k in range(n_total)
                                      if (k, group[idx]) in y)
                    late_visit = sum(y[k, group[idx+1]] for k in range(n_total)
                                     if (k, group[idx+1]) in y)
                    # 如果早场访问为0，晚场必须为0；即早场 >= 晚场
                    # 注意：sum 可能是非线性表达式，CP-SAT 支持 BoolVar 线性不等式
                    model.Add(early_visit >= late_visit)

            # ---- 目标函数 ----
            # 游玩指示变量 = sum_{j} y[i][j] (有出边即被认为游玩)
            played_indicators = []
            for i in range(1, OUT):
                out_edges_i = [y[i, j] for j in range(n_total) if (i, j) in y]
                if out_edges_i:
                    played_indicators.append(sum(out_edges_i))
                else:
                    played_indicators.append(0)  # 不可达节点
            obj_expr = sum(p_scaled[i] * played_indicators[i-1] for i in range(1, OUT)) \
                       - lam_scaled * sum(walk[i][j] * y_var for (i, j), y_var in y.items())
            model.Maximize(obj_expr)

            # ---- 求解器配置 ----
            solver = cp_model.CpSolver()
            solver.parameters.max_time_in_seconds = SOLVE_TIME_LIMIT
            solver.parameters.num_search_workers = 8        # 多线程
            solver.parameters.log_search_progress = True    # 显示求解日志
            # 设置日志输出前缀，方便识别情景（但无法直接修改，可忽略）

            # 开始求解
            print(f"  求解 {scenario} ...")
            status = solver.Solve(model)

            f_out.write(f"求解状态: {solver.StatusName(status)}\n")

            if status in (cp_model.OPTIMAL, cp_model.FEASIBLE):
                # 提取路径
                edges = [(i, j) for (i, j), y_var in y.items() if solver.BooleanValue(y_var)]
                path = [IN]
                while path[-1] != OUT:
                    nxt = [j for (i, j) in edges if i == path[-1]]
                    if not nxt:
                        break
                    path.append(nxt[0])

                f_out.write("最优路线：\n  " + " → ".join(expanded_nodes[n]['name'] for n in path) + "\n")

                real_obj = solver.ObjectiveValue() / SCALE
                total_walk = sum(walk[i][j] for (i, j) in edges)
                played = [n for n in path if n not in (IN, OUT)]
                exit_time = solver.Value(t[OUT])

                f_out.write(f"总净收益（还原后）: {real_obj:.2f}\n")
                f_out.write(f"游玩项目数: {len(played)}\n")
                f_out.write(f"总步行时间: {total_walk} 分钟\n")
                f_out.write(f"出口到达时刻: {exit_time} 分钟 (约 {8.5 + exit_time/60:.2f} 点)\n")
                f_out.write("详细时间表（开始游玩时刻）：\n")
                for idx in played:
                    start = solver.Value(t[idx])
                    f_out.write(f"  {expanded_nodes[idx]['name']:25s} | 开始 {start} 分 | 时长 {expanded_nodes[idx]['play']} 分\n")
                # 记录汇总
                results_summary.append((scenario, real_obj, len(played), total_walk, exit_time))
            else:
                f_out.write("未找到可行解。\n")
                results_summary.append((scenario, None, None, None, None))
            f_out.write("\n")

    # 写入汇总表
    f_out.write("========== 汇总 ==========\n")
    f_out.write(f"{'情景':<25s} {'总净收益':>10s} {'项目数':>6s} {'步行(分)':>8s} {'出口时刻(分)':>12s}\n")
    for (scenario, obj, cnt, walk_t, exit_t) in results_summary:
        obj_str = f"{obj:.2f}" if obj is not None else "  -"
        cnt_str = f"{cnt}" if cnt is not None else " -"
        walk_str = f"{walk_t}" if walk_t is not None else " -"
        exit_str = f"{exit_t}" if exit_t is not None else " -"
        f_out.write(f"{scenario:<25s} {obj_str:>10s} {cnt_str:>6s} {walk_str:>8s} {exit_str:>12s}\n")

print(f"全部完成，结果已保存至 {output_file}")