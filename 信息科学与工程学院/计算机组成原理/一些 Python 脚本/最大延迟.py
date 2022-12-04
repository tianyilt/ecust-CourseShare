t_command = [250, 350, 150, 300, 200]  # 按需修改
t_nonpipeline = sum(t_command)
t_pipeline = max(t_command)
procedures = len(t_command)
t_latency_pipeline = procedures*t_pipeline
t_latency_nonpipeline = sum(t_command)
seperation_ratio = 2  # 按需修改
selected = max(t_command)
t_command_temp = t_command
t_command_temp(find(t_command_temp == max(t_command_temp))) = []
t_command_temp(end+1) = selected/seperation_ratio
t_nonpipeline_new = max(t_command_temp)
t_one_cycle = t_nonpipeline
t_pipeline = t_pipeline
# 考虑各种情形下指令的使用情况：
# LW5cycles SW4cycles(无WB)
# ALU4cycles （无mem）
# BEQ3cycles（无wb无mem）
multicycle = [5, 4, 4, 3]  # 自己修改
usage = [0.2, 0.45, 0.15, 0.2]  # 参照上面两问的计算方法修改
multicycles_pipeline_ratio = sum(i*j for i, j in zip(multicycle, usage))
onecycle_pipeline_ratio = t_one_cycle/t_pipeline
# 这个matlab没法转了
