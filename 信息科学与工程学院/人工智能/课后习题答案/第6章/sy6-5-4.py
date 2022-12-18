# 导入外部库和CIFAR10数据集
import tensorflow as tf
import matplotlib.pyplot as plt
from sklearn import metrics

cifar10 = tf.keras.datasets.cifar10
(X_train, y_train), (X_test, y_test) = cifar10.load_data()

# 建立映射表
class_names = ['airplane', 'automobile', 'bird', 'cat', 'deer',
               'dog', 'frog', 'horse', 'ship', 'truck']

# 显示训练集的前20个图像和标签
plt.figure(figsize=(10, 9))
num = 20
for i in range(0, num):
    plt.subplot(4, 5, i + 1)
    plt.imshow(X_train[i])
    plt.xticks([])
    plt.yticks([])
    plt.title("True=" + str(class_names[y_train[i][0]]))
    plt.savefig('20.jpg')
plt.show()

# 归一化数字图像
X_train_norm, X_test_norm = X_train / 255.0, X_test / 255.0

# 构建Sequential模型
model = tf.keras.models.Sequential()

# 构造卷积神经网络
# 构建卷积层
model.add(tf.keras.layers.Conv2D(______, (3, 3), activation='relu', input_shape=(32, 32, 3)))  # 此处答案不固定，只要符合题目要求即可
# 构建池化层
model.add(tf.keras.layers.MaxPooling2D((2, 2)))
# 构建卷积层
model.add(tf.keras.layers.Conv2D(______, (3, 3), activation='relu', ))  # 此处答案不固定，只要符合题目要求即可
# 构建池化层
model.add(tf.keras.layers.MaxPooling2D((2, 2)))
# 构建Dropout层
model.add(tf.keras.layers.Dropout(rate=0.2))

# 构建全连接层
model.add(tf.keras.layers.Flatten())
model.add(tf.keras.layers.Dense(80, activation='relu'))
model.add(tf.keras.layers.Dense((10), activation='softmax'))

# 打印模型的概况
print(model.summary())

# 模型编译
model.compile(optimizer='adam',
              loss='sparse_categorical_crossentropy',
              metrics=['accuracy'])

# 模型训练
history = model.fit(X_train_norm, y_train, validation_split=0.1, epochs=20, verbose=1)

# 模型评估
model.evaluate(X_test_norm, y_test, verbose=1)
