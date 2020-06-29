instructions = 10 ** 6  # 自己修改
a_zhanbi = 0.1  # 自己修改
b_zhanbi = 0.2  # 自己修改
c_zhanbi = 0.5  # 自己修改
d_zhanbi = 0.2  # 自己修改
CPI1 = [1, 2, 2.7]  # 自己修改
CPI2 = [1, 1, 1]  # 自己修改
average_CPI1 = (
    instructions*a_zhanbi*CPI1[0] +
    instructions*b_zhanbi*CPI1[1] +
    instructions*c_zhanbi*CPI1[2] +
    instructions*d_zhanbi*CPI1[3]
)/instructions
average_CPI2 = (
    instructions*a_zhanbi*CPI2[0] +
    instructions*b_zhanbi*CPI2[1] +
    instructions*c_zhanbi*CPI2[2] +
    instructions*d_zhanbi*CPI2[3]
)/instructions
clockcycles1 = average_CPI1*instructions
clockcycles2 = average_CPI2*instructions
