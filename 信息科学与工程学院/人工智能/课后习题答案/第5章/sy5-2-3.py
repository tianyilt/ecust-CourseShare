# （1）导入库
from sklearn.datasets import load_digits
import matplotlib.pyplot as plt
import numpy as np
from sklearn.neighbors import KNeighborsClassifier
from sklearn.model_selection import train_test_split
from sklearn.metrics import classification_report

# （2）调用load_digits()读入手写数字信息，并显示前十张图片展示手写数字
digits = load_digits()
images = digits.images
plt.figure(figsize=(10, 5))
plt.suptitle('handwritten_Image')
# 前十张图片
for i in range(10):
    plt.subplot(2, 5, i + 1), plt.title('image%i' % (i + 1))
    plt.imshow(images[i]), plt.axis('off')
plt.show()

# （3）分割数据
X_train, X_test, Y_train, Y_test = train_test_split(digits.data, digits.target, test_size=0.2, random_state=33)

# （4）利用KNN模型进行分类
knc = KNeighborsClassifier()
knc.fit(X_train, Y_train)
y_predict = knc.predict(X_test)

# （5）使用模型自带的评估函数进行准确性测评。
print('The accuracy of K-Nearest Neighbor Classifier is', knc.score(X_test, Y_test))

# （6）使用sklearn.metrics里面的classification_report模块对预测结果做更加详细的分析。
print(classification_report(Y_test, y_predict))
