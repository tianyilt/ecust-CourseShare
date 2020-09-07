CPI1 = 1.5
CPU1_GHz = 3
CPI2 = 1
CPU2_GHz = 2.5
CPI3 = 2.2
CPU3_GHz = 4
IPS1 = CPU1_GHz*10 ** 9/CPI1
IPS2 = CPU2_GHz*10 ** 9/CPI2
IPS3 = CPU3_GHz*10 ** 9/CPI3
# 判断：谁IPS大，谁性能强，在这里CPU2最强
t = 10  # 执行10秒钟，自己改
# 处理器1
clockcycles1 = t*CPU1_GHz*10 ** 9
instructions1 = clockcycles1/CPI1
# 处理器2
clockcycles2 = t*CPU2_GHz*10 ** 9
instructions2 = clockcycles2/CPI2
# 处理器3
clockcycles3 = t*CPU3_GHz*10 ** 9
instructions3 = clockcycles3/CPI3
i = 0.3  # 执行时间减少比率，自己改
j = 0.2  # CPI增加比率，自己改
CPU1_GHz = instructions1*CPI1*(1+j)/t/(1-i)/10 ** 9
print(f'CPU1_GHz={CPU1_GHz}')
CPU2_GHz = instructions2*CPI2*(1+j)/t/(1-i)/10 ** 9
print(f'CPU2_GHz={CPU2_GHz}')
CPU3_GHz = instructions3*CPI3*(1+j)/t/(1-i)/10 ** 9
print(f'CPU3_GHz={CPU3_GHz}')
