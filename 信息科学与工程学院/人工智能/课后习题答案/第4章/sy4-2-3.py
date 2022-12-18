import pandas as pd

# 从CSV文件读取数据到DataFrame对象
boston = pd.read_csv(r'C:\\配套资源\\第4章\\Boston_pandas.csv')
print(boston)
# 删除行索引值为1、2和3的元素
boston = boston.drop([1, 2, 3], axis=0)
print(boston)
# 修改 'MEDV' 列的数据内容为15
boston['MEDV'] = 15
print(boston)
