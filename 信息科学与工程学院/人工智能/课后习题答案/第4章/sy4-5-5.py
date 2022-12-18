import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

plt.rcParams['font.sans-serif'] = ['SimHei']  # 避免中文出现乱码
plt.rcParams['axes.unicode_minus'] = False

N = 20
fig = plt.figure(figsize=(6, 5))
ax = Axes3D(fig, elev=45, azim=45)
ax.scatter(np.random.randint(25, 38, N), np.random.randint(50, 90, N), np.random.randint(10, 30, N), marker='x',
           label='夏季', c='r', edgecolors='r')
ax.scatter(np.random.randint(1, 10, N), np.random.randint(10, 40, N), np.random.randint(50, 90, N), marker='>',
           label='冬季', c='g', edgecolors='g')
ax.set_xlabel('温度℃')
ax.set_ylabel('湿度%')
ax.set_zlabel('空气质量')
ax.dist = 11
plt.legend()
plt.show()
