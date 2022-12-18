# -*- coding: utf-8 -*-
"""
针对以下数据集，编程训练一个日均学习时间和成绩关系的线性回归模型，
请基于该模型进行预测，输出日均学习时间为2小时的学生，他们的成绩。
"""
import matplotlib.pyplot as plt

# （1）导入库
from sklearn import linear_model
import numpy as np

# （2）加载数据集 
x = [3, 4, 5, 6, 7, 8, 9, 10, 11, 12]
y = [50, 50, 60, 70, 80, 88, 85, 90, 85, 90]
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
X_test = [[2]]

prediction = clf.predict(X_test)

print("时间：\n", X_test, "\n成绩预测值：\n", prediction)

"""
运行结果
[[4.8969697]]
[38.07272727]
时间：
 [[2]] 
成绩预测值：
 [[47.86666667]]
"""
