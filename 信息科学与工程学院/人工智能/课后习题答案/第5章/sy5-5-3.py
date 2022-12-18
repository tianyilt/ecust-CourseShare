# _*_coding:utf-8_*_
# （1）导入库
import matplotlib.pyplot as plt
from sklearn import datasets
from sklearn.decomposition import PCA
from sklearn.cluster import KMeans
import time
import numpy as np

# （2）导入数据集
wine = datasets.load_wine()
X = wine.data
y = wine.target
print(X.shape)  # 查验扩展前数据规模
for i in np.arange(10):
    X = np.vstack((X, X))
    y = np.hstack((y, y))
print(X.shape)  # 查验扩展后数据规模

# （3）降维前K-Means算法耗时
ticks = time.time()
kmean = KMeans(3)
kmean.fit(X)
print('降维前耗时:', time.time() - ticks, 's')

# （4）降维
pca = PCA(n_components=2)
X_p = pca.fit_transform(X)

# （5）降维后K-Means算法耗时
ticks = time.time()
kmean = KMeans(3)
kmean.fit(X_p)
print('降维后耗时:', time.time() - ticks, "s")

# （6）聚类结果可视化
labels = kmean.labels_
centers = kmean.cluster_centers_
colors = 'rgw'
edge_colors = 'rgb'
marker = 'x>o'
for i in range(3):
    plt.scatter(X_p[labels == i, 0], X_p[labels == i, 1], c=colors[i], edgecolors=edge_colors[i], marker=marker[i])
plt.scatter(centers[:, 0], centers[:, 1], s=50, marker='*')  # 显示质心
plt.show()
