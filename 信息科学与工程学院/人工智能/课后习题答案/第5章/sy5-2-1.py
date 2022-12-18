#（1）导入库
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from sklearn.neighbors import KNeighborsClassifier
from sklearn.model_selection import train_test_split
from sklearn.metrics import classification_report

#（2） 加载数据
data = pd.read_csv('配套资源/第五章/diabetes.csv')
X = data.iloc[:, 0:8]
Y = data.iloc[:, 8]
X_train, X_test, Y_train, Y_test = train_test_split(X, Y, test_size=0.2);

#（3）利用KNN模型进行分类
knc = KNeighborsClassifier()
knc.fit(X_train, Y_train)
y_predict = knc.predict(X_test)

# （4）使用模型自带的评估函数进行准确性测评。
print('The accuracy of K-Nearest Neighbor Classifier is', knc.score(X_test, Y_test)) 

#（5）使用sklearn.metrics里面的classification_report模块对预测结果做更加详细的分析。
print(classification_report(Y_test,y_predict))