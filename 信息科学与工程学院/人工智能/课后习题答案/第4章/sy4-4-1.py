import numpy as np
import matplotlib.pyplot as plt

plt.rcParams['font.sans-serif'] = ['SimHei']  # 避免中文出现乱码
plt.rcParams['axes.unicode_minus'] = False
humidity = np.random.randint(50, 90, (10, 12))
labels = ['Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun', 'Jul', 'Aug', 'Sept', 'Oct', 'Nov', 'Dec']
plt.boxplot(humidity, labels=labels, sym='*', whis=1.25, widths=0.6)
plt.xlabel('平均相对湿度百分比')
plt.show()
