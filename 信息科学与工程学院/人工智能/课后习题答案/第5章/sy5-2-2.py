# （1）导入库
from sklearn.datasets import make_blobs
from matplotlib import pyplot as plt
from sklearn.neighbors import KNeighborsClassifier
from sklearn.model_selection import train_test_split
from sklearn.metrics import classification_report

# （2）利用make_blobs函数生成200个样本数据，特征数为2的数据
X, Y = make_blobs(n_samples=150, n_features=2);

# （3）利用散点图展示出来
plt.figure(figsize=(6, 4), dpi=144)
plt.xticks(())
plt.yticks(())
plt.scatter(X[:, 0], X[:, 1], s=20, marker='o');

X_train, X_test, Y_train, Y_test = train_test_split(X, Y, test_size=0.2);
# （3）利用KNN模型进行分类
knc = KNeighborsClassifier()
knc.fit(X_train, Y_train)
y_predict = knc.predict(X_test)

# （4）使用模型自带的评估函数进行准确性测评。
print('The accuracy of K-Nearest Neighbor Classifier is', knc.score(X_test, Y_test))

# （5）使用sklearn.metrics里面的classification_report模块对预测结果做更加详细的分析。
print(classification_report(Y_test, y_predict))
