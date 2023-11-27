import pandas as pd
import statsmodels.api as sm
import numpy as np
from scipy.stats import f

def FF3factorsmulti_and_GRStest(data_matrix,assetnum):#FF多资产联合检验;data_matrix格式:date mkt smb hml rfreturn ……资产……
    T=len(data_matrix)##时间序列长度
    K=3##三因子
    N=assetnum##资产数量
    y=data_matrix.iloc[:,5:5+N].values-data_matrix.loc[:,['rfreturn']].values##各个资产的超额收益.reshape((107,1)
    x = data_matrix.loc[:, ['mkt', 'smb', 'hml']].values
    x=sm.add_constant(x)##加一列全1
    xTx=np.dot(np.transpose(x),x)
    yTx=np.dot(np.transpose(y),x)
    AB_hat=np.dot(yTx,np.linalg.inv(xTx))
    AB_hat=np.transpose(AB_hat)##从N*4变成了4*N
    ALPHA=AB_hat[0]
    RESD = y - np.dot(x, AB_hat)##用实际值减去系数计算出来的值，得到差值
    COV = np.dot(np.transpose(RESD), RESD) / T
    invCOV = np.linalg.inv(COV)
    fs = x[:, [1, 2, 3]]##x加在第一列上  x=sm.add_constant(x)加在第一列上
    muhat = np.mean(fs, axis=0)##axis=0,axis=1分别对应按列求平均和按行求平均
    fs = fs - np.mean(fs, axis=0)
    omegahat = np.dot(np.transpose(fs), fs) / T
    invOMG = np.linalg.inv(omegahat)
    xxx = np.dot(np.dot(np.transpose(muhat), invOMG), muhat)
    yyy = np.dot(np.dot(ALPHA, invCOV), np.transpose(ALPHA))
    GRS = (T - N - K) / N * (1 / (1 + xxx)) * yyy
    print(GRS)
    pvalue = 1 - f.cdf(GRS, N, T - N - K)
    print('三因子模型的多资产检验结果')
    print(
        '{:>7s},{:>7s},{:>7s},{:>7s},{:>7s},{:>7s},{:>7s},{:>7s},{:>7s}'.format('alpha1', 'alpha2', 'alpha3', 'alpha4',
                                                                                'alpha5', 'alpha6', 'alpha7', 'GRS',
                                                                                'pvalue'))
    print('{:7.4f},{:7.4f},{:7.4f},{:7.4f},{:7.4f},{:7.4f},{:7.4f},{:7.4f},{:7.4f}'.format(ALPHA[0], ALPHA[1], ALPHA[2],
                                                                                           ALPHA[3], ALPHA[4], ALPHA[5],
                                                                                           ALPHA[6], GRS, pvalue))
#FF多资产联合检验;data_matrix格式:date mkt smb hml rfreturn ……资产……
##assetnum:资产个数
def FF3factors_readcsv():##
    data_factors = pd.read_csv('E:\大三下study\蒋志强\実験3\学习通资料\Data_FFFactors.csv', encoding='GB2312',
                               usecols=[2, 6, 7, 8])
    data_factors.columns = ['date', 'mkt', 'smb', 'hml']
    data_factors['date'] = pd.to_datetime(data_factors['date'])
    data_factors['yearmonth'] = data_factors['date'].dt.strftime('%Y%m')
    data_index = pd.read_csv('E:\大三下study\蒋志强\実験3\学习通资料\Data_Index.csv', encoding='GB2312',
                             usecols=[1, 2, 4])
    data_index.columns = ['idxname', 'date', 'return']
    data_index['date'] = pd.to_datetime(data_index['date'])
    data_index['yearmonth'] = data_index['date'].dt.strftime('%Y%m')
    idxname = np.unique(data_index['idxname'].values)
    data_xinxi = data_index[data_index['idxname'] == idxname[0]]
    data_gongyong = data_index[data_index['idxname'] == idxname[1]]
    data_yiyao = data_index[data_index['idxname'] == idxname[2]]
    data_kexuan = data_index[data_index['idxname'] == idxname[3]]
    data_gongye = data_index[data_index['idxname'] == idxname[4]]
    data_cailiao = data_index[data_index['idxname'] == idxname[6]]
    data_xiaofei = data_index[data_index['idxname'] == idxname[7]]
    data_dianxin = data_index[data_index['idxname'] == idxname[8]]
    data_nengyuan = data_index[data_index['idxname'] == idxname[9]]
    data_jinrong = data_index[data_index['idxname'] == idxname[10]]
    data_rf = pd.read_csv('E:\大三下study\蒋志强\実験3\学习通资料\Data_RiskFreeReturn.csv', encoding='GB2312',
                          usecols=[0, 3])
    data_rf.columns = ['date', 'rfreturn']
    data_rf['date'] = pd.to_datetime(data_rf['date'])
    data_rf['yearmonth'] = data_rf['date'].dt.strftime('%Y%m')
    data_matrix = pd.merge(left=data_factors[['yearmonth', 'date', 'mkt', 'smb', 'hml']],
                           right=data_xinxi[['yearmonth', 'return']],
                           on=['yearmonth'],
                           how='inner')
    data_matrix = pd.merge(left=data_matrix,
                           right=data_gongyong[['yearmonth', 'return']],
                           on=['yearmonth'],
                           how='inner')
    data_matrix = pd.merge(left=data_matrix,
                           right=data_yiyao[['yearmonth', 'return']],
                           on=['yearmonth'],
                           how='inner')
    data_matrix = pd.merge(left=data_matrix,
                           right=data_kexuan[['yearmonth', 'return']],
                           on=['yearmonth'],
                           how='inner')
    data_matrix = pd.merge(left=data_matrix,
                           right=data_gongye[['yearmonth', 'return']],
                           on=['yearmonth'],
                           how='inner')
    data_matrix = pd.merge(left=data_matrix,
                           right=data_cailiao[['yearmonth', 'return']],
                           on=['yearmonth'],
                           how='inner')
    data_matrix = pd.merge(left=data_matrix,
                           right=data_xiaofei[['yearmonth', 'return']],
                           on=['yearmonth'],
                           how='inner')
    data_matrix = pd.merge(left=data_matrix,
                           right=data_dianxin[['yearmonth', 'return']],
                           on=['yearmonth'],
                           how='inner')
    data_matrix = pd.merge(left=data_matrix,
                           right=data_nengyuan[['yearmonth', 'return']],
                           on=['yearmonth'],
                           how='inner')
    data_matrix = pd.merge(left=data_matrix,
                           right=data_jinrong[['yearmonth', 'return']],
                           on=['yearmonth'],
                           how='inner')
    data_matrix = pd.merge(left=data_matrix,
                           right=data_rf[['yearmonth', 'rfreturn']],
                           on=['yearmonth'],
                           how='inner')
    data_matrix.columns = ['yearmonth', 'date', 'mkt', 'smb', 'hml', 'xinxi', 'gongyong', 'yiyao', 'kexuan',
                           'gongye', 'cailiao', 'xiaofei', 'dianxin', 'nengyuan', 'jinrong', 'rfreturn']
    data_matrix.dropna(inplace=True)
    data_matrix.sort_values(by='date', inplace=True)
    return data_matrix##
##三因子文件格式交易所标识_Exchflg	市场标识_Mktflg	日期_Date	市场溢酬因子__流通市值加权_Rmrf_tmv	市值因子__流通市值加权_Smb_tmv	账面市值比因子__流通市值加权_Hml_tmv	市场溢酬因子__总市值加权_Rmrf_mc	市值因子__总市值加权_Smb_mc	账面市值比因子__总市值加权_Hml_mc
##资产文件格式指数代码_IdxCd	指数名称_IdxNm	交易日期_TrdDt	收盘价()_ClPr	指数月收益率_IdxMonRet
##无风险收益率文件格式日期_Date	年份_Year	月份_Month	月无风险收益率_MonRFRet




# def GRStest():








if __name__ == '__main__':
    data_factors = pd.read_csv('E:\大三下study\蒋志强\実験3\学习通资料\Data_FFFactors.csv', encoding='GB2312', usecols=[2, 6, 7, 8])

    FF3factorsmulti_and_GRStest(data_matrix,10)

# See PyCharm help at https://www.jetbrains.com/help/pycharm/
