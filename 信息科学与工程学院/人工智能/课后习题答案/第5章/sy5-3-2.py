# （1）导入库
from sklearn.datasets import load_boston
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
import matplotlib.pyplot as plt
from matplotlib import rcParams

# （2）加载数据集 
boston = load_boston()
x = boston['data']
y = boston['target']
names = boston['feature_names']

# 分割数据为训练集和测试集,设置测试集为所有样本数据的10%
x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=0.1, random_state=22)
print('x_train前3行数据为：', x_train[0:3], '\n', 'y_train前3行数据为：', y_train[0:3])

# （3）创建线性回归模型对象lr
lr = LinearRegression()

# 使用训练集训练模型
lr.fit(x_train, y_train)
# 显示模型
print(lr)
# 显示模型13个系数
print(lr.coef_)
# 显示模型截距
print(lr.intercept_)

# （4）使用测试集获取预测结果,实现基于测试集中的前10个样本进行预测，输出前10个预测值。
print(lr.predict(x_test[:5]))

# （5）模型评估
# 计算并输出决定系数R2
print(lr.score(x_test, y_test))
