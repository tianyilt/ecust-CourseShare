import matplotlib.pyplot as plt

plt.rcParams['font.sans-serif'] = 'SimHei'  # 设置中文显示
plt.rcParams['font.size'] = 16
plt.figure(figsize=(12, 12))  # 设置画布尺寸
Items = ['教育', '食品', '服装', '旅游', '保险', '其它']  # 定义饼图的标签
explode = [0.1, 0.01, 0.01, 0.01, 0.01, 0.01]  # 设定各项距离圆心距离
Expenses = [30000, 12000, 8000, 24000, 3500, 8000]
plt.pie(Expenses, explode=explode, labels=Items, autopct='%4.2f%%', shadow=True)  # 绘制饼图
plt.title('家庭年各项消费比较表')
plt.legend(Items, loc=3)
plt.show()
