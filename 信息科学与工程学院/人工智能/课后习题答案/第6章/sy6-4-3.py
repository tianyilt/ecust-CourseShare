# 导入外部库和Fashion-MNIST数据集
import tensorflow as tf
import matplotlib.pyplot as plt
from sklearn import metrics

fashion_mnist = tf.keras.datasets.fashion_mnist
(X_train, y_train), (X_test, y_test) = fashion_mnist.load_data()

# 建立映射表
class_names = ['T-shirt/top', 'Trouser', 'Pullover', 'Dress', 'Coat', \
               'Sandal', 'Shirt', 'Sneaker', 'Bag', 'Ankle boot']

# 利用reshape函数转换数字图像
X_train_reshape = X_train.reshape(X_train.shape[0], 28, 28, 1)
X_test_reshape = X_test.reshape(X_test.shape[0], 28, 28, 1)

# 归一化数字图像
X_train_norm, X_test_norm = X_train_reshape / 255.0, X_test_reshape / 255.0

# 构建Sequential模型
model = tf.keras.models.Sequential()

# 构造卷积神经网络
# 构建卷积层
model.add(tf.keras.layers.Conv2D(32, (3, 3), activation='relu', input_shape=(28, 28, 1)))
# 构建池化层
model.add(tf.keras.layers.MaxPooling2D((2, 2)))
# 构建Dropout层
model.add(tf.keras.layers.Dropout(rate=0.2))

# 构建全连接层
model.add(tf.keras.layers.Flatten())
model.add(tf.keras.layers.Dense(50, activation='relu'))
model.add(tf.keras.layers.Dense(10, activation='softmax'))

# 打印模型的概况
print(model.summary())

# 模型编译
model.compile(optimizer='adam',
              loss='sparse_categorical_crossentropy',
              metrics=['accuracy'])

# 模型训练
history = model.fit(X_train_norm, y_train, validation_split=0.2, epochs=10, verbose=1)

# 模型评估
model.evaluate(X_test_norm, y_test, verbose=1)
