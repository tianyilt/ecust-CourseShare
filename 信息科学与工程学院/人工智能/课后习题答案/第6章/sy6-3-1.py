# （1）导入TensorFlow
import tensorflow as tf

# （2）载入Fashion-MNIST 数据集
fashion_mnist = tf.keras.datasets.fashion_mnist
(X_train, y_train), (X_test, y_test) = fashion_mnist.load_data()

# （3）利用reshape函数转换数字图像
X_train_reshape = X_train.reshape(X_train.shape[0], 28 * 28)
X_test_reshape = X_test.reshape(X_test.shape[0], 28 * 28)

# （4）归一化数字图像
X_train_norm, X_test_norm = X_train_reshape / 255.0, X_test_reshape / 255.0

# （5）构建Sequential模型
model = tf.keras.models.Sequential()
model.add(tf.keras.layers.Dense(______, input_dim=28 * 28, activation='relu'))  # 答案不固定，满足题目要求即可
model.add(tf.keras.layers.Dense(10, activation='softmax'))

# （6）模型编译
model.compile(optimizer='adam',
              loss='sparse_categorical_crossentropy',
              metrics=['accuracy'])

# （7）模型训练
model.fit(X_train_norm, y_train, epochs=10)

# （8）模型评估
model.evaluate(X_test_norm, y_test, verbose=1)
