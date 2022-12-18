import numpy as np
import matplotlib.pyplot as plt

N = 30
p1 = plt.scatter(np.random.randint(50, 70, N), np.random.randint(50, 70, N), c='r', s=50, marker='*')
p2 = plt.scatter(np.random.randint(80, 100, N), np.random.randint(80, 100, N), c='b', s=50, marker='v')
plt.legend([p1, p2], ['class1', 'class2'])  # 分别为数据集p1和p2添加图例班级1和班级2
plt.xlabel('Math')
plt.ylabel('English')
plt.grid()  # 显示网格
plt.show()
