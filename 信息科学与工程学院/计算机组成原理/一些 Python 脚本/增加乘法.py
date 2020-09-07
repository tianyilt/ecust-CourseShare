latency = [400, 100, 30, 120, 200, 350, 100]
cost = [1000, 30, 10, 100, 200, 2000, 500]
CPI = 1  # 本题设为常数
instructions = 1  # 本题设为常数
i = 0.05  # 指令减少量
j = 600  # 增加的成本
# 检查最长的指令访存的关键路径
total_latency = 400+2*100+30+120+350+30+200  # 按照走过的路径改
improved_latency = total_latency+300  # 按需要改
jiasubi = (CPI*instructions*total_latency) / \
    (CPI*instructions*(1-i)*improved_latency)
total_cost = 1000+30*2+10*3+100+200+2000+500  # 按照走过的路径改
improved_total_latency = total_cost+j
cost_ratio = improved_total_latency/total_cost
result = cost_ratio/jiasubi
# result > 1, 考虑成本增加的比较多，所以话费大与收益
