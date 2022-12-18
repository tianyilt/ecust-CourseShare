import pandas as pd
import numpy as np

iris = pd.read_csv(r'C:\\配套资源\\第4章\\Iris_numpy.csv')
# 创建NumPy数组
arrL = np.array(iris)
# 创建切片
arr1 = arrL[0:50, 0]
arr2 = arrL[50:100, 0]
arr3 = arrL[100:150, 0]
# 求三种鸢尾花花萼的平均值
print(arr1.mean())
print(arr2.mean())
print(arr3.mean())
