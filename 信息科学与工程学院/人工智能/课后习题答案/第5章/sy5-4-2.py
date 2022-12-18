# （1）导入库
from sklearn.datasets import make_blobs
from matplotlib import pyplot as plt
from sklearn.cluster import KMeans

# （2）利用make_blobs函数生成200个样本数据，特征数为3的数据
x, y = make_blobs(n_samples=200, n_features=2);

# （3）利用散点图展示出来
plt.figure(figsize=(6, 4), dpi=144)
plt.xticks(())
plt.yticks(())
plt.scatter(x[:, 0], x[:, 1], s=20, marker='o');

# （4）利用Kmeans函数聚类，聚类簇设为4
n_clusters = 4
kmean = KMeans(n_clusters)
kmean.fit(x)

# （5）将结果利用散点图显示出来
labels = kmean.labels_
centers = kmean.cluster_centers_
markers = ['o', '^', '*', 'D']
colors = ['r', 'b', 'y', 'g']
plt.figure(figsize=(6, 4), dpi=144)
plt.xticks(())
plt.yticks(())
for c in range(n_clusters):
    cluster = x[labels == c]
    plt.scatter(cluster[:, 0], cluster[:, 1], marker=markers[c], s=20, c=colors[c])
plt.scatter(centers[:, 0], centers[:, 1], marker='o', c="white", alpha=0.9, s=300)
for i, c in enumerate(centers):
    plt.scatter(c[0], c[1], marker='$%d$' % i, s=50, c=colors[i])
plt.show()
