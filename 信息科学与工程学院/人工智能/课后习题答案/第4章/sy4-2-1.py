import pandas as pd
import numpy as np

data = np.arange(21, 31, 1, np.int32)
index = np.arange(1, 11, 1)
num = pd.Series(data, index)
print(num)
num[num.values <= 25] = 0
print(num)
