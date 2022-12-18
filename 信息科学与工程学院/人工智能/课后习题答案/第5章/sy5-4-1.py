# （1）导入库
import numpy as np
from sklearn.cluster import KMeans
from matplotlib import pyplot as plt

# （2）随机生成500个数据
X = np.random.rand(500, 3)  # 生成一个随机数据，样本大小为500, 特征数为3

# （3）利用散点图将数据展示出来
plt.figure(figsize=(16, 10), dpi=144)
plt.scatter(X[:, 0], X[:, 1], s=200, cmap='cool')
plt.show()

# （4）使用KMeans模型拟合，聚类数设为5。
kmean = KMeans(5)
kmean.fit(X)

# （5）将聚类结果利用散点图显示出来
labels = kmean.labels_
centers = kmean.cluster_centers_
fig = plt.figure(figsize=(8, 5), dpi=144)
plt.scatter(X[:, 0], X[:, 1], c=labels.astype(int), edgecolor='k')  # 显示聚类结果
plt.scatter(centers[:, 0], centers[:, 1], s=50, marker="*")  # 显示质心
plt.show()
