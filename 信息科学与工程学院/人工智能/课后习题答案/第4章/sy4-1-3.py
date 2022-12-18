import numpy as np

arr = np.random.uniform(20, 40, size=(4, 5))
print(arr)
row_mean = arr.mean(axis=1)
col_max = arr.max(axis=0)
index_max = arr.argmin()
print(row_mean)
print(col_max)
print(index_max)
