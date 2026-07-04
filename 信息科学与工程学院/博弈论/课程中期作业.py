# 策略定义后请直接运行此文件，系统会自动校验你的代码是否会报错或返回违规值
# 运行无误后提交，文件名必须为：学号_姓名.py

def my_strategy(my_history, opponent_history):
    """
    在此处编写你的博弈策略
    my_history (list): 我方历史出牌，如 ['C', 'C', 'D']。第一轮为空 []。
    opponent_history (list): 对手历史出牌，如 ['C', 'D', 'D']。第一轮为空 []。
    """
    
    # 以下为示例策略：以牙还牙 (Tit-for-Tat)（按要求注释保留）
    # if len(opponent_history) == 0: #第一轮输入参数为空，单独考虑
    #     return 'C' # 以牙还牙策略第一轮默认合作
    # else:
    #     return opponent_history[-1] # 以牙还牙策略每次模仿对手上一轮动作
    # 
    # 请删除上方示例，替换为你的代码！必须返回 'C' 或 'D'。

    # 最终采用方案：强化 Pavlov（赢留输变）+ 类型识别
    rounds_played = len(my_history)

    # 首轮合作，优先争取互利轨道
    if rounds_played == 0:
        return 'C'

    opp_total_d = opponent_history.count('D')
    opp_d_rate = opp_total_d / rounds_played

    # 终局收缩为防守，降低末轮被偷袭风险
    if rounds_played >= 197:
        return 'D'

    # 对持续背叛型对手直接防守
    if rounds_played >= 6 and opponent_history[-6:].count('D') >= 5:
        return 'D'
    if rounds_played >= 10 and opp_d_rate >= 0.8:
        return 'D'

    # 对高度随机型对手，合作回报低，优先防守
    if rounds_played >= 12:
        recent = opponent_history[-12:]
        switches = 0
        for i in range(1, 12):
            if recent[i] != recent[i - 1]:
                switches += 1
        recent_d_rate = recent.count('D') / 12
        if switches >= 8 and 0.3 <= recent_d_rate <= 0.7:
            return 'D'

    my_last = my_history[-1]
    opp_last = opponent_history[-1]

    # 强化 Pavlov 规则
    if my_last == 'C' and opp_last == 'C':
        return 'C'
    if my_last == 'C' and opp_last == 'D':
        return 'D'
    if my_last == 'D' and opp_last == 'C':
        return 'D'

    # 出现 (D, D) 时：若对手并非高背叛，周期性尝试修复合作
    if opp_d_rate < 0.6 and rounds_played % 5 == 0:
        return 'C'
    return 'D'


# ==========================================================
# 本地验证脚本（以下内容请勿修改）
# ==========================================================
if __name__ == "__main__":
    import random
    print("正在进行代码规范校验...\n" + "-"*30)
    
    try:
        if my_strategy([], []) not in ['C', 'D']:
            print("失败：第一轮返回值必须是 'C' 或 'D'")
            exit()
    except Exception as e:
        print(f"失败：首轮执行报错 (传入空数组时)。错误: {e}")
        exit()
        
    test_my_hist, test_opp_hist = [], []
    try:
        for i in range(200):
            me = my_strategy(test_my_hist, test_opp_hist)
            opp = random.choice(['C', 'D'])
            if me not in ['C', 'D']:
                print(f"失败：第 {i+1} 轮返回了非法值 '{me}'")
                exit()
            test_my_hist.append(me)
            test_opp_hist.append(opp)
        print("通过！代码可稳定运行 200 轮，格式正确，可提交。")
    except Exception as e:
        print(f"失败：在第 {len(test_my_hist)+1} 轮发生崩溃。错误: {e}")