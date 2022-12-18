import pandas as pd
import numpy as np
from sklearn.preprocessing import MinMaxScaler
from sklearn.preprocessing import Normalizer

# 创建表示5×5的随机矩阵的DataFrame对象frame
ar = np.random.randint(1, 51, 25).reshape(5, 5)
frame = pd.DataFrame(ar)
print(frame)

# 转换器实例化
minmax_scaler = MinMaxScaler()
# 数据归一化
minmax_result = minmax_scaler.fit_transform(frame)
print("数据归一化：\n", minmax_result)

# 转换器实例化
normalization_scaler = Normalizer()
# 数据正则化
normalization_result = normalization_scaler.fit_transform(frame)
print("数据正则化：\n", normalization_result)
