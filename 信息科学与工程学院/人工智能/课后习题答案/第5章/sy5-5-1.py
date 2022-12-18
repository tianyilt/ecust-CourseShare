# _*_coding:utf-8_*_
# （1）导入库
import matplotlib.pyplot as plt
from sklearn.datasets import load_boston
from sklearn.decomposition import PCA
from sklearn.preprocessing import StandardScaler
import numpy as np

plt.rcParams['font.sans-serif'] = ['SimHei']  # 避免中文出现乱码
plt.rcParams['axes.unicode_minus'] = False

# （2）导入数据集
boston = load_boston()
X = boston.data
y = boston.target

# （3）标准化
scaler = StandardScaler()
X_input = scaler.fit(X).transform(X)

# （4）PCA降维
pca = PCA()
pca.fit(X_input).transform(X_input)

# （5）可视化
p = [0]
explained_sum = 0
for i in pca.explained_variance_ratio_:
    explained_sum = explained_sum + i * 100
    p.append(explained_sum)  # 获得的每一个目标维度下方差占比
plt.plot(p)
plt.xlabel('保留的主成分')
plt.ylabel('解释的方差值占总方差比例')
plt.xticks(np.arange(0, 14, 1))  # 设置x轴刻度
plt.yticks(np.arange(0, 101, 10))  # 设置y轴刻度
plt.grid()  # 添加网格
plt.show()
