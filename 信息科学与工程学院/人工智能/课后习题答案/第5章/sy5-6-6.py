# _*_coding:utf-8_*_
# （1）导入库
from sklearn import datasets
from sklearn.decomposition import PCA
import matplotlib.pyplot as plt

# （2）导入数据集
digits = datasets.load_digits()
X = digits.data
y = digits.target

# （3）降维
pca = PCA(n_components=2)
X_p = pca.fit_transform(X)

# （4）可视化
plt.figure
colors = ['black', 'blue', 'purple', 'yellow', 'green', 'red', 'lime', 'cyan', 'orange', 'gray']
label = digits.target_names
for i in range(10):
    plt.scatter(X_p[y == i, 0], X_p[y == i, 1], c=colors[i], label=label[i])
plt.legend()
plt.show()
