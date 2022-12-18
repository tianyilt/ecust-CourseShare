import pandas as pd
import numpy as np

vegetable = pd.read_csv(r'C:\\配套资源\\第4章\\vegetable.csv', engine='python')  # 解释器引擎设为'python'以支持中文
print(vegetable)
vegetable_new1 = vegetable.drop_duplicates(keep='first')
print(vegetable_new1)
vegetable_new2 = vegetable.drop_duplicates(keep='last')
print(vegetable_new2)
