# （1）导入库
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from sklearn.cluster import KMeans
from sklearn import datasets

plt.rcParams['font.sans-serif'] = ['SimHei']  # 避免中文出现乱码
plt.rcParams['axes.unicode_minus'] = False

# （2）利用load_iris()函数导入数据，并付给变量X
iris = datasets.load_iris()  # 导入iris数据
X = iris.data

# （3）设置变量存储类簇数，并分别进行Kmeans聚类，同时进行可视化
n_clusters_list = [2, 3, 4, 5]
for n_clusters in n_clusters_list:
    est = KMeans(n_clusters)  # 调用KMeans进行聚类
    est.fit(X)  # 模型训练
    labels = est.labels_
    fig = plt.figure(figsize=(8, 5), dpi=144)
    ax = Axes3D(fig, rect=[0, 0, 0.95, 1], elev=48, azim=134)
    ax.scatter(X[:, 3], X[:, 0], X[:, 2], c=labels.astype(np.float), edgecolor='k')
    ax.w_xaxis.set_ticklabels([])
    ax.w_yaxis.set_ticklabels([])
    ax.w_zaxis.set_ticklabels([])
    ax.set_xlabel('花萼宽度')
    ax.set_ylabel('萼片长度')
    ax.set_zlabel('花瓣长度')
    ax.set_title(str(n_clusters) + '类')
    ax.dist = 12
    plt.show()
