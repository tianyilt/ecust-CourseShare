import numpy as np

Z = np.random.randint(10, 20, (5, 5))
print("矩阵 Z=\n", Z)
Zmin = Z.min()
Zmax = Z.max()
Z = (Z - Zmin) / (Zmax - Zmin)
print("归一化后的Z：\n", Z)
