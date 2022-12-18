import pandas as pd
import numpy as np

mon1 = np.random.rand(5)
mon2 = np.random.rand(5)
mon3 = np.random.rand(5)
mon4 = np.random.rand(5)
mon5 = np.random.rand(5)
mon6 = np.random.rand(5)
yf = ['1月', '2月', '3月', '4月', '5月', '6月']
city = ['北京', '上海', '太原', '乌鲁木齐', '扬州']
PM = pd.DataFrame([mon1, mon2, mon3, mon4, mon5, mon6], index=yf, columns=city)
print(PM)
PM = PM.drop(['1月', '3月', '5月'], axis=0)
print(PM)
PM_new = PM[PM['北京'] >= 0.5]
print(list(PM_new.index))
