import pandas as pd

fish = pd.read_csv(r'C:\\配套资源\\第4章\\fish.csv', engine='python')  # 解释器引擎设为'python'以支持中文
print(fish)
fish.dropna(axis=1, how='all', inplace=True)
print(fish)
fish.dropna(inplace=True)
print(fish)
