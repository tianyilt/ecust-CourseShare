import matplotlib.pyplot as plt
import pandas as pd

data = pd.read_csv(r'C:\\配套资源\\第4章\\Iris_plot.csv')
X = data['petal_length']
Y = data['petal_width']
fig = plt.figure(figsize=(12, 10))
plt.scatter(X[:50], Y[:50], color='green', marker='o', label='setosa')  # 前50个样本
plt.scatter(X[50:100], Y[50:100], color='blue', marker='x', label='versicolor')  # 中间50个
plt.scatter(X[100:], Y[100:], color='red', marker='+', label='Virginica')  # 后50个样本
plt.legend(loc=2)  # 左上角
plt.grid()
plt.show()
