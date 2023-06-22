import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import statsmodels.api as sm
from scipy.stats import chi2, f
import warnings
warnings.filterwarnings("ignore")
risk_free=pd.read_csv('risk_free.csv',encoding='utf-8')
risk_free.columns=['date','rfreturn']
risk_free.dropna(inplace=True)
risk_free['date'] = pd.to_datetime(risk_free['date'], format='%Y/%m/%d')#注意进行日期格式的变换
index=pd.read_csv('index.csv',encoding='utf-8')
index.columns=['date','indexclose']
index['indexreturn']=np.log(index['indexclose'])-np.log(index['indexclose'].shift(periods=1))##这里是对每一行数据，减去前一行数据，所得值保存在该行，会出现na值，需要dropna
index.dropna(inplace=True)
index['date'] = pd.to_datetime(index['date'], format='%Y/%m/%d')

def OneAsset():
    path='600820.csv'
    stock_data1 = pd.read_csv(path,encoding='utf-8',usecols=[1,2])  # 0：股票代码；1：日期；2：收盘价
    stock_data1.columns=['date','close']
    stock_data1.dropna(inplace=True)
    stock_data1['return']=np.log(stock_data1['close'])-np.log(stock_data1['close'].shift(periods=1))
    # m=stock_data1['close'].values
    # l=np.log(m[1:])-np.log(m[:-1])  通过这个方法会少一个数据项，而索引值的项数不变，因此索引值的项数数据多1，出现问题
    # print(m)
    # print(l)
    stock_data1.dropna(inplace=True)
    stock_data1['date'] = pd.to_datetime(stock_data1['date'], format='%Y/%m/%d')
    stock_data1['return'].plot()
    plt.show()
    ind = (stock_data1['return'] >= -0.1) & (stock_data1['return'] <= 0.1)
    stock_data1 = stock_data1.loc[ind, :]
    stock_data1['return'].plot()
    plt.show()
    merge_data=pd.merge(left=stock_data1[['date','close','return']],right=risk_free[['date','rfreturn']],on='date',how='inner')
    merge_data.dropna(inplace=True)
    merge_data=pd.merge(left=merge_data[['date','close','rfreturn','return']],right=index[['date','indexreturn']],on='date',how='inner')
    merge_data.dropna(inplace=True)
    stk_ret=merge_data['return'].values
    rf_ret=merge_data['rfreturn'].values
    ind_ret=merge_data['indexreturn'].values
    plt.plot(ind_ret - rf_ret, stk_ret - rf_ret, 'o', ms=5, mfc='w', lw=2)
    plt.xlabel(r'$r_m - r_f$', fontsize=20)
    plt.ylabel(r'$r_i - r_f$', fontsize=20)
    plt.show()
    x = sm.add_constant(ind_ret - rf_ret)
    y = stk_ret - rf_ret
    model = sm.OLS(y, x)
    results = model.fit()
    print(results.summary())


    # merge_data['return']=np.log(merge_data['close'][1:])-np.log(merge_data['close'][0:len(merge_data['close'])])
    # print(merge_data['close'][1:])

def multiasset():
    stock_data=pd.read_csv('month.csv',encoding='utf-8')
    stock_data.sort_values(by='code',inplace=True)
    stk_codes=np.unique(stock_data['code'].values)
    stock_data['date']=pd.to_datetime(stock_data['date'])
    stock_data['date']=stock_data['date'].dt.strftime('%Y-%m')
    risk_free['date'] = risk_free['date'].dt.strftime('%Y-%m')
    index['date']=index['date'].dt.strftime('%Y-%m')
    stock_datas=list(pd.DataFrame())##使用list来装载各个不同代码的股票的dataframe
    count=-1
    for i in stk_codes:
        count+=1
        m=stock_data[stock_data['code']==i]
        m.sort_values(by=['date'], inplace=True)
        m['return'] = np.log(m['close']) - np.log(m['close'].shift(periods=1))
        m.dropna(inplace=True)
        ind=(m['return']>=-0.1)&(m['return']<=0.1)
        m=m.loc[ind, :]
        stock_datas.append(m)
    stock_dataall = stock_datas[0][['date','return']]
    for i in stock_datas[1:]:
        stock_dataall=pd.merge(left=stock_dataall,right=i[['date','return']],on='date',how='inner')
    stock_dataall = pd.merge(left=stock_dataall, right=index[['date', 'indexreturn']], on='date', how='inner')
    stock_dataall=pd.merge(left=stock_dataall,right=risk_free[['date','rfreturn']],on='date',how='inner')
    stock_dataall.columns=['date','x1','x2','x3','x4','x5','x6','x7','x8','indexreturn','rfreturn']
    for i in stock_dataall.columns[1:-1]:
        stock_dataall[i]=stock_dataall[i]-stock_dataall['rfreturn']
    ret_ind=stock_dataall['indexreturn'].values
    T=len(ret_ind)
    N = 8
    mu_market = np.mean(ret_ind)
    sigma_market = np.sum((ret_ind - mu_market) ** 2) / T
    ret_stocks = stock_dataall[['x1', 'x2', 'x3', 'x4', 'x5', 'x6','x7','x8']].values
    x = sm.add_constant(ret_ind)
    y = ret_stocks[:, 3]
    model = sm.OLS(y, x)
    results = model.fit()
    # print(results.summary())
    x = np.ones((T, 2))
    x[:, 1] = ret_ind
    y = ret_stocks
    xTx = np.dot(np.transpose(x), x)
    xTy = np.dot(np.transpose(x), y)
    AB_hat = np.dot(np.linalg.inv(xTx), xTy)
    ALPHA = AB_hat[0]
    print(ALPHA)
    BETA = AB_hat[1]
    RESD = y - np.dot(x, AB_hat)
    COV = np.dot(np.transpose(RESD), RESD) / T
    invCOV = np.linalg.inv(COV)

    xr = np.ones((T, 1))
    xr[:, 0] = ret_ind
    yr = ret_stocks
    xrTxr = np.dot(np.transpose(xr), xr)
    xrTyr = np.dot(np.transpose(xr), yr)
    ABr_hat = np.dot(np.linalg.inv(xrTxr), xrTyr)
    RESDr = yr - np.dot(xr, ABr_hat)
    COVr = np.dot(np.transpose(RESDr), RESDr) / T
    invCOVr = np.linalg.inv(COVr)
    trans_ALPHA = np.ones((len(ALPHA), 1))
    trans_ALPHA[:, 0] = ALPHA
    SWchi2 = T * (1 / (1 + mu_market ** 2 / sigma_market)) * np.dot(np.dot(ALPHA, invCOV), trans_ALPHA)
    SWF = (T - N - 1) / N * (1 / (1 + mu_market ** 2 / sigma_market)) * np.dot(np.dot(ALPHA, invCOV), trans_ALPHA)
    pvalue_Wchi2 = 1 - chi2.cdf(SWchi2[0], N)
    pvalue_WF = 1 - f.cdf(SWF[0], N, T - N - 1)
    print(pvalue_Wchi2)
    print(pvalue_WF)
    SLRchi2 = T * (np.log(np.linalg.det(COVr)) - np.log(np.linalg.det(COV)))
    pvalue_SLRchi2 = 1 - chi2.cdf(SLRchi2, N)
    print(pvalue_SLRchi2)
    a = np.zeros((8, 1))
    a[:, 0] = np.sum(RESDr, axis=0)
    salpha = np.dot(invCOVr, a)
    b = np.dot(ret_ind, RESDr)
    sbeta = np.zeros((8, 1))
    sbeta[:, 0] = np.dot(invCOVr, b)
    score = np.concatenate((salpha, sbeta), axis=0)
    a = np.concatenate((invCOVr * T, invCOVr * np.sum(ret_ind)), axis=1)
    b = np.concatenate((invCOVr * np.sum(ret_ind), invCOVr * np.sum(ret_ind ** 2)), axis=1)
    Minfo = np.concatenate((a, b), axis=0)
    SLMchi2 = np.dot(np.dot(np.transpose(score), np.linalg.inv(Minfo)), score)
    pvalue_SLMchi2 = 1 - chi2.cdf(SLMchi2[0][0], N)
    print(pvalue_SLMchi2)
    print('{:>10s}, {:>10s}, {:>10s}, {:>10s}'.format('Wald Test1', 'Wald Test2', 'LR Test', 'LM Test'))
    print('{:10.5f}, {:10.5f}, {:10.5f}, {:10.5f}'.format(SWchi2[0], SWF[0], SLRchi2, SLMchi2[0][0]))
    print('{:10.5f}, {:10.5f}, {:10.5f}, {:10.5f}'.format(pvalue_Wchi2, pvalue_WF, pvalue_SLRchi2, pvalue_SLMchi2))




    # pathlist=['000020.csv','000420.csv','600120.csv','600220.csv','600320.csv','600620.csv','600720.csv','600820.csv']
    # stock_data=[]
    # stock_dataall = pd.DataFrame()#创建一个空的dataframe对象
    # count=-1
    # for i in pathlist:
    #     count+=1
    #     stock_data.append(pd.read_csv(i,encoding='utf-8'))
    #     stock_data[count].dropna(inplace=True)
    #     stock_data[count].columns=['code','date','close']
    #     stock_data[count]['date']=pd.to_datetime(stock_data[count]['date'],format='%Y/%m/%d')
    #     stock_data[count]=pd.merge(left=stock_data[count][['code','date','close']],right=risk_free[['date','rfreturn']],on='date',how='inner')
    #     stock_dataall=stock_dataall.append(stock_data[count],ignore_index=True)  #这里使用了ignore_index=Tr
    #     # ue，实现了行的编号从零开始，这就将原本行号不连续的问题消除了  。而且这里是dataframe的append，可以使用参数。list的append是不能使用参数的
    # stock_dataall.columns=['code','date','close','rfreturn']
    # stock_dataall.dropna(inplace=True)
    # stock_dataall.sort_values(by=['code'],inplace=True)#按照code进行升序排列
    # stk_codes=np.unique(stock_dataall['code'].values)
    # stock_dataclass=list(pd.DataFrame())
    # count=-1
    # for i in range(0,len(stock_data)):
    #     count+=1
    #     stock_dataclass.append(stock_dataall[stock_dataall['code']==stk_codes[i]])
    #     stock_dataclass[count].sort_values(by='date',inplace=True)##在原数据集上操作
    #     stock_dataclass[count]['return']=np.log(stock_dataclass[count]['close'])-np.log(stock_dataclass[count]['close'].shift(periods=1))
    #     stock_dataclass[count].dropna(inplace=True)
    #     ind=(stock_dataclass[count]['return']>=-0.1)&(stock_dataclass[count]['return']<=0.1)
    #     stock_dataclass[count]=stock_dataclass[count].loc[ind,:]
    #     plt.plot(stock_dataclass[count]['return'].values)
    #     plt.title(pathlist[count][0:6])
    #     plt.show()


def load_data():
    # 请将数据文件路径替换为你的数据文件路径
    data = pd.read_csv('your_data_file.csv')
    data['date'] = pd.to_datetime(data['date'])
    data.set_index('date', inplace=True)
    return data

def calculate_cumulative_returns(data, n_months):
    return data.pct_change(n_months).rolling(n_months).apply(lambda x: np.prod(1 + x) - 1)

# 构建投资组合
def build_portfolios(cumulative_returns, n_portfolios):
    sorted_cumulative_returns = cumulative_returns.rank(axis=1, method="first")
    portfolio_bins = pd.qcut(sorted_cumulative_returns.stack(), n_portfolios, labels=list(range(n_portfolios))).unstack()
    portfolios = []

    for i in range(n_portfolios):
        portfolio = data.where(portfolio_bins == i).dropna(how="all", axis=1)
        portfolios.append(portfolio)

    return portfolios

# 计算投资组合收益率
def calculate_portfolio_returns(portfolios, m_months):
    portfolio_returns = []
    for portfolio in portfolios:
        portfolio_return = portfolio.pct_change(m_months).dropna()
        portfolio_returns.append(portfolio_return.mean(axis=1))
    return pd.DataFrame(portfolio_returns).T

# 分析结果
def analyze_results(portfolio_returns):
    return_diff = portfolio_returns.iloc[:, -1] - portfolio_returns.iloc[:, 0]
    if return_diff.mean() > 0:
        print("市场具有惯性效应")
    else:
        print("市场具有反转效应")





def new0():
    data = pd.read_csv('file.csv')
    data['month'] = pd.to_datetime(data['month'], format='%Y/%m/%d')
    data['month']=data['month'].dt.strftime('%Y-%m')
    data.set_index('month', inplace=True)
    returns = data.groupby('股票代码_Stkcd')['月收益率_Monret']
    six_month_returns = returns.apply(lambda x: (1 + x).rolling(6, min_periods=1).apply(lambda x: x.prod()) - 1)
    result = pd.merge(data, six_month_returns, left_index=True, right_index=True)
    print(six_month_returns)
    mean_returns = six_month_returns.groupby('股票代码_Stkcd').mean()
    mean_returns_sorted = mean_returns.sort_values(by='月收益率_Monret')
    portfolio_bins = pd.qcut(mean_returns_sorted['月收益率_Monret'], 3, labels=False)
    portfolios = []
    for i in range(3):
        portfolio = mean_returns_sorted[portfolio_bins == i].index
        portfolio_returns = six_month_returns.loc[portfolio].mean(axis=1)
        portfolios.append(portfolio_returns)

    #risk_free['date'] = risk_free['date'].dt.strftime('%Y-%m')


def new1():
    import pandas as pd

    # 读取 csv 文件，假设文件名为 data.csv，第一行为表头
    df = pd.read_csv('file.csv')

    # 将月份转换为日期格式
    df['month'] = pd.to_datetime(df['month'], format='%Y-%m')

    # 将数据按照股票代码分组
    groups = df.groupby('股票代码_Stkcd')

    # 计算每个股票的过去 6 个月的累计收益率
    returns = []
    for name, group in groups:
        # 将数据按照日期排序
        group = group.sort_values('month')
        # 计算每个月份的收益率变化率
        group['return'] = group['月收益率_Monret'].pct_change()
        # 计算每个月份的累计收益率
        group['cum_return'] = (1 + group['return']).rolling(window=6).apply(lambda x: x.prod()) - 1
        # 只保留股票代码和累计收益率两列数据，并将结果添加到列表中
        returns.append(group[['股票代码_Stkcd', 'cum_return']])
    # 将结果合并为一个 DataFrame
    result = pd.concat(returns)
    result.dropna(inplace=True)
    # 将结果按照股票代码和累计收益率排序
    result = result.sort_values(['股票代码_Stkcd', 'cum_return'])
    # 使用 qcut() 方法将累计收益率分成三个组合，并添加一个新列 group
    result['group'] = pd.qcut(result['cum_return'], 3, labels=['low', 'mid', 'high'])
    print(result)
    # 将结果按照 group 和 month 排序
    result = result.sort_values(['group', 'month'])
    # 计算每个投资组合在接下来 6 个月的累计收益率
    returns = []
    for group_name, group in result.groupby('group'):
        # 计算每个月份的收益率变化率
        group['return'] = group['月收益率_Monret'].pct_change()
        # 计算每个月份的累计收益率
        group['cum_return_next6m'] = (1 + group['return']).rolling(window=6).apply(lambda x: x.prod()) - 1
        # 只保留 group 和 cum_return_next6m 两列数据，并将结果添加到列表中
        returns.append(group[['group', 'cum_return_next6m']])
    # 将结果合并为一个 DataFrame
    result_next6m = pd.concat(returns)

    print(result_next6m)

def new2():
    import pandas as pd
    df = pd.read_csv('file.csv')
    df_grouped = df.groupby('_Stkcd').apply(lambda x: x.sort_values('month'))
    df_grouped['6m_return'] = df_grouped.groupby('_Stkcd')['月收益率_Monret'].rolling(6).apply(
        lambda x: (1 + x).prod() - 1, raw=True).reset_index(0, drop=True)
    df_grouped = df_grouped.sort_values(['_Stkcd', 'month'])
    df_grouped.dropna(inplace=True)
    df = df.sort_values('month')
    df_grouped = df_grouped.groupby('month')
    df_sorted = df_grouped.apply(lambda x: x.sort_values('6m_return'))
    df_sorted = df_sorted.reset_index(drop=True)
    df_sorted['group'] = df_sorted.groupby('month')['6m_return'].apply(
        lambda x: pd.qcut(x, q=4,duplicates='drop'))
    labels = ['low', 'mid', 'high']
    df_sorted['future_return'] = df_sorted.groupby('group')['月收益率_Monret'].rolling(6).apply(
        lambda x: (1 + x).prod() - 1, raw=True).reset_index(0, drop=True)
    df_sorted = df_sorted.sort_values(['group', 'month'])
    df_sorted['change'] = df_sorted.groupby('month')['group'].apply(lambda x: x.ne(x.shift()))
    print(df_sorted)


if __name__ == '__main__':
    new2()



