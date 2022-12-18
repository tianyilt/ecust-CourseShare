# -*- coding: utf-8 -*-
# （1）导入库
from sklearn import linear_model

# （2）加载训练数据
X = [[0, 0], [1, 1], [2, 2]]
y = [0, 1, 2]

# （3）创建线性回归模型对象
clf = linear_model.LinearRegression()

# 在下面填写一行代码，实现使用数据集训练模型，拟合直线
clf.fit(X, y)

# （4）输出拟合好的函数的系数和截距
print(clf.coef_)

# 在下面填写一行代码，实现输出拟合好函数的截距
print(clf.intercept_)
