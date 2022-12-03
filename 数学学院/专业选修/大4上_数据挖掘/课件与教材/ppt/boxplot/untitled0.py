import pandas as pd
import matplotlib.pyplot as plt
titanic = pd.read_csv('titanic_train.csv') # 读取Titanic数据集
any(titanic.Age.isnull()) # 检查年龄是否有缺失
titanic.dropna(subset=['Age'], inplace=True) # 不妨删除含有缺失年龄的观察
plt.style.use('ggplot') # 设置图形的显示风格
plt.rcParams['font.sans-serif'] = 'Microsoft YaHei'  # 设置中文和负号正常显示
plt.rcParams['axes.unicode_minus'] = False
# 绘图：整体乘客的年龄箱线图
plt.boxplot(x = titanic.Age, # 指定绘图数据
patch_artist=True, # 要求用自定义颜色填充盒形图，默认白色填充
showmeans=True, # 以点的形式显示均值
boxprops = {'color':'black','facecolor':'#9999ff'}, # 设置箱体属性，填充色和边框色
flierprops = {'marker':'o','markerfacecolor':'red','color':'black'}, # 设置异常值属性，点的形状、填充色和边框色
meanprops = {'marker':'D','markerfacecolor':'indianred'}, # 设置均值点的属性，点的形状、填充色
medianprops = {'linestyle':'--','color':'orange'}) # 设置中位数线的属性，线的类型和颜色
# 设置y轴的范围
plt.ylim(0,85)
# 去除箱线图的上边框与右边框的刻度标签
plt.tick_params(top='off', right='off')
# 显示图形
plt.show()


