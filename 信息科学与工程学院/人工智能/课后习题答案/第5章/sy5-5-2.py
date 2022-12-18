# _*_coding:utf-8_*_
# （1）导入库
import matplotlib.pyplot as plt
from sklearn.datasets import load_wine
from sklearn.decomposition import PCA

plt.rcParams['font.sans-serif'] = ['SimHei']  # 避免中文出现乱码
plt.rcParams['axes.unicode_minus'] = False

# （2）导入数据集
wine = load_wine()
X = wine.data
y = wine.target

# （3）降维
pca = PCA(n_components=2)
X_p = pca.fit_transform(X)

# （4）输出图像
plt.figure()
colors = 'rgw'
edge_colors = 'rgb'
marker = 'x>o'
label = wine.target_names
for i in range(3):  # 类别数
    plt.scatter(X_p[y == i, 0], X_p[y == i, 1], c=colors[i], edgecolors=edge_colors[i], marker=marker[i],
                label=label[i])
plt.xlabel('维度1')
plt.ylabel('维度2')
plt.title('葡萄酒')
plt.legend()
plt.show()
