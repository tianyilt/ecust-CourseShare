# 导入库
import matplotlib.pyplot as plt
from sklearn import linear_model
import numpy as np

# 加载数据集
x = [173, 155, 160, 165, 170, 175, 180, 170, 190, 180]
y = [170, 162, 164, 169, 175, 178, 185, 172, 180, 175]
X = np.array(x).reshape(-1, 1)
Y = np.array(y).reshape(-1, 1)
# 创建线性回归模型对象
clf = linear_model.LinearRegression()

# 使用数据集训练模型，拟合直线
clf.fit(X, Y)

# 输出拟合好的函数的系数和截距
print(clf.coef_)
# [ 0.5 0.5]
print(clf.intercept_)

# 测试
X_test = [[170]]

# 预测身高
prediction = clf.predict(X_test)

print("父母身高：\n", X_test, "\n儿子身高预测值：\n", prediction)
