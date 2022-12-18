# -*- coding: utf-8 -*-
"""
2某出租公司出租车使用年限x和该年支出维修费用y（万元）数据如下：
（1）求线性回归方程； 
（2）据（1）的结果预测第10年所支出的维修费用

"""
import matplotlib.pyplot as plt

# （1）导入库
from sklearn import linear_model
import numpy as np

# （2）加载数据集 
x = [2, 3, 4, 5, 6]
y = [2.2, 3.8, 5.5, 6.5, 7]
X = np.array(x).reshape(-1, 1)
Y = np.array(y).reshape(-1, 1)
# （3）创建线性回归模型对象
clf = linear_model.LinearRegression()
# 使用数据集训练模型，拟合直线
clf.fit(X, Y)

# （4）输出拟合好的函数的系数和截距
print(clf.coef_)
# [ 0.5 0.5]
print(clf.intercept_)
# 1.11022302463e-16

# 测试
X_test = [[10]]
prediction = clf.predict(X_test)
print("时间：\n", X_test, "\n第10年所支出的维修费用预测值：\n", prediction)

"""
运行结果
[[4.8969697]]
[38.07272727]
时间：
 [[2]] 
成绩预测值：
 [[47.86666667]]
"""
