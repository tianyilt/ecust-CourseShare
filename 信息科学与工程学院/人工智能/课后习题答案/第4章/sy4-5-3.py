import pandas as pd
import matplotlib.pyplot as plt

gdp = pd.read_csv(r'C:\\配套资源\\第4章\\GDP.csv')
print(gdp)
gdp = gdp.dropna()  # 删除有缺失值的行
print(gdp)
gdp = gdp.drop_duplicates()  # 删除重复数据
print(gdp)
plt.rcParams['font.sans-serif'] = ['SimHei']  # 显示中文
plt.plot(gdp.Date, gdp.America, color='b', linewidth=2.0, linestyle='--')  # 绘制折线图
plt.plot(gdp.Date, gdp.China, color='r', linewidth=2.0, linestyle='-.')  # 绘制折线图
plt.plot(gdp.Date, gdp.Japan, color='c', linewidth=2.0, linestyle=':')  # 绘制折线图
plt.plot(gdp.Date, gdp.Germany, color='g', linewidth=2.0, linestyle='-')  # 绘制折线图
# 添加标题和坐标轴标签
plt.title('中美日德的国内生产总值')
plt.xlabel('日期')
plt.ylabel('年生产总值（亿元）')
# 显示图形
plt.show()
