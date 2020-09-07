clockcycle_ns = 1  # 自己改
instructionsA = 1.0*10 ** 9  # 自己改
t_A = 1.1  # 自己改
instructionsB = 1.2*10 ** 9  # 自己改
t_B = 1.5  # 自己改
average_CPIA = t_A/(instructionsA*(1/(clockcycle_ns*10 ** 9)))
average_CPIB = t_B/(instructionsB*(1/(clockcycle_ns*10 ** 9)))
CPUA_GHz_CPUB_GHz_ratio = (instructionsB*average_CPIB) / \
    (instructionsA*average_CPIA)
clockcycle_ns_new = 1  # 自己改
CPI_new = 1.1  # 自己改
instructions_new = 6*10 ** 8  # 自己改
clockcycles_new = 1*10 ** -9  # 自己改, 建立在第一问条件上
t_new = CPI_new*instructions_new*clockcycles_new
jiasubi_A = t_A/t_new
jiasubi_B = t_B/t_new
