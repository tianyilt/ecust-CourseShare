import pandas as pd
import numpy as np

data = np.random.randint(0, 101, (10, 10), np.int32)
index = np.arange(1, 11, 1)
matrix = pd.DataFrame(data, index, index)  # 创建DataFrame对象
print(matrix)
matrix_max = matrix.max(axis=0)  # 求每列最大值
print(matrix_max)
matrix_min = matrix.min(axis=0)  # 求每列最小值
print(matrix_min)
