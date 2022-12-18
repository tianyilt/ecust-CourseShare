import numpy as np

arr = np.linspace(1, 16, 16).reshape(4, 4)
print(arr)
num_1 = arr[1, 0]
num_2 = arr[2, 1]
print(num_1, num_2)
arr2 = arr[1:, 1:]
print(arr2)
mask = (arr % 2 == 1)
arr[mask] = 0
print(arr)
