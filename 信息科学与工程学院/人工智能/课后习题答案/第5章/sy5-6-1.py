from sklearn import metrics

true = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
pred = [0, 2, 2, 3, 5, 3, 5, 7, 9, 8]

# （1）计算平均绝对误差MAE
print('MAE： %s' % metrics. mean_absolute_error (true, pred))
# （2）计算均方误差MSE
print('MSE： %s' % metrics. mean_squared_error (true, pred))
# （3）计算决定系数
print('R^2： %s' % metrics. r2_score (true, pred))
