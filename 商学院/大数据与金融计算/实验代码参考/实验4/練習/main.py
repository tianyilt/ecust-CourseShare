import numpy as np
import pandas as pd



# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    df1 = pd.DataFrame({'a': [1, 2], 'b': [5, 6]})
    df2 = pd.DataFrame({'a': [2, 1, 0,2], 'y': [6, 7, 8,3]})
    # 按a列进行连接，数据顺序取df1的顺序
    res = pd.merge(df1, df2, on='a',how='left')
    print(res)


# See PyCharm help at https://www.jetbrains.com/help/pycharm/
