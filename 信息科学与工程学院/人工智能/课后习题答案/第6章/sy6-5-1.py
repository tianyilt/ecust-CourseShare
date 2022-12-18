# 导入TensorFlow
import tensorflow as tf
import matplotlib.pyplot as plt

# 载入Fashion-MNIST数据集
fashion_mnist = tf.keras.datasets.fashion_mnist
(X_train, y_train), (X_test, y_test) = fashion_mnist.load_data()

# 查看训练集和测试集的形状
print('The shape of train data=', X_train.shape)
print('The shape of y_train:', y_train.shape)
print('The shape of test data=', X_test.shape)
print('The shape of y_test:', y_test.shape)

# 建立映射表
class_names = ['T-shirt/top', 'Trouser', 'Pullover', 'Dress', 'Coat',
               'Sandal', 'Shirt', 'Sneaker', 'Bag', 'Ankle boot']

# 显示训练集的前20个图像和标签
plt.figure(figsize=(10, 9))
num = 20
for i in range(0, num):
    plt.subplot(4, 5, i + 1)
    plt.imshow(X_train[i], cmap='gray')
    plt.xticks([])
    plt.yticks([])
    plt.title("True=" + str(class_names[y_train[i]]))
plt.show()

# 显示训练集第二个图像及其内容
plt.figure()
plt.imshow(X_train[1], cmap='gray')
plt.savefig('2.jpg')
plt.show()
print(X_train[1])

# 利用reshape函数转换数字图像
X_train_reshape = X_train.reshape(X_train.shape[0], 28 * 28)
X_test_reshape = X_test.reshape(X_test.shape[0], 28 * 28)
# 查看经过reshape之后训练集和测试集的形状
print('The shape of train reshape data=', X_train_reshape.shape)
print('The shape of y_train:', y_train.shape)
print('The shape of test reshape data=', X_test_reshape.shape)
print('The shape of y_test:', y_test.shape)

# 标准化数字图像
X_train_norm, X_test_norm = X_train_reshape / 255.0, X_test_reshape / 255.0

# 构建Sequential模型
model = tf.keras.models.Sequential()
model.add(tf.keras.layers.Dense(50, input_dim=28 * 28, activation='relu', name='Hidden1'))
model.add(tf.keras.layers.Dense(50, activation='relu', name='Hidden2'))
model.add(tf.keras.layers.Dense(50, activation='relu', name='Hidden3'))
model.add(tf.keras.layers.Dense(500, activation='relu', name='Hidden4'))
model.add(tf.keras.layers.Dense(10, activation='softmax', name='Output'))

# 打印模型的概况
print(model.summary())

# 模型编译
model.compile(optimizer='adam',
              loss='sparse_categorical_crossentropy',
              metrics=['accuracy'])

# 模型训练
model.fit(X_train_norm, y_train, epochs=10, verbose=1, validation_split=0.1)

# 模型评估
model.evaluate(X_test_norm, y_test, verbose=1)

# 模型预测
prediction = model.predict_classes(X_test_norm)

# 显示测试集的前20个图像的预测类别和真实类别
plt.figure(figsize=(18, 9))
num = 20
for i in range(0, num):
    plt.subplot(4, 5, i + 1)
    plt.imshow(X_test[i], cmap='gray')
    plt.xticks([])
    plt.yticks([])
    plt.title('Predict=' + str(class_names[prediction[i]]) + ';True=' + str(class_names[y_test[i]]))
plt.show()

# 保存训练好的模型
modelname = 'my_model.h5'
model.save(modelname)
print('保存的模型名称 ', modelname)

# 利用保存的模型进行预测
model = tf.keras.models.load_model(modelname)
prediction = model.predict_classes(X_test_norm)
