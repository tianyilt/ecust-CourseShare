import pandas as pd
import numpy as np

month = ['1月', '2月', '3月', '4月', '5月', '6月', '7月', '8月', '9月', '10月', '11月', '12月']
money = np.random.randint(5000, 10001, (12, 2), np.int32)
account = pd.DataFrame(money, month, columns=['收入', '支出'])  # 创建DataFrame对象
print(account)
account_new = account['支出']
print(account_new)
# 从DataFrame对象写入数据到CSV文件
account_new.to_csv(r'C:\\配套资源\\第4章\\account.csv')
