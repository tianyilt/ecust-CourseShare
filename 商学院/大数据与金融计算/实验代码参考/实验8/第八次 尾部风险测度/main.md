```python
import numpy as np
import pandas as pd
import requests
from scipy.stats import norm, chi2, genpareto
import matplotlib.pyplot as plt
from arch import arch_model
%matplotlib inline
```


```python
res = requests.get('http://money.finance.sina.com.cn/quotes_service/api/json_v2.php/CN_MarketData.getKLineData?symbol=sh000001&scale=240&ma=no&datalen=10000')
# scale单位是分钟。这个地址数据很全，开盘、收盘、最高、最低、成交量。
# ma 移动平均参数
# datalen 数据量参数
data_json = res.json()
data = pd.DataFrame(data_json)
data.to_csv('data_ssec.csv')
print(data)
```

                 day      open      high       low     close       volume
    0     1990-12-19    96.050    99.980    95.790    99.980       126000
    1     1990-12-20   104.300   104.390    99.980   104.390        19700
    2     1990-12-21   109.070   109.130   103.730   109.130         2800
    3     1990-12-24   113.570   114.550   109.130   114.550         3200
    4     1990-12-25   120.090   120.250   114.550   120.250         1500
    ...          ...       ...       ...       ...       ...          ...
    7930  2023-06-07  3197.468  3210.330  3188.005  3197.759  25806340000
    7931  2023-06-08  3194.835  3225.526  3180.535  3213.586  29353074100
    7932  2023-06-09  3213.033  3231.406  3206.103  3231.406  31415550100
    7933  2023-06-12  3225.305  3239.437  3210.714  3228.834  31378444400
    7934  2023-06-13  3223.896  3235.085  3215.499  3233.673  28062845400
    
    [7935 rows x 6 columns]



```python
data = pd.read_csv('data_ssec.csv')
data['return'] = np.log(data['close']) - np.log(data['close'].shift(periods=1))
data['day'] = pd.to_datetime(data['day'], format='%Y-%m-%d')
ind = data['day'] >= pd.to_datetime('2011-01-01', format='%Y-%m-%d')
r = data[ind]['return'].values*100
plt.plot(r)
plt.show()
```


![png](output_2_0.png)
    



```python
# RiskMetrics方法
l = np.fix(len(r)/3).astype(int) 解析：np.fix是进行向0取整：3.5->3;-4.5->-4。这里len(r)/3是三分位点，样本内外数据为1/2（注意这里不是样本内外数据1/1）#请根据题目要求更改#
VaR_RM = np.zeros(len(r)) 解析：获取长度为len（r）的全零ndarray
qalpha = norm.ppf(0.05) 解析：这里的qalpha是标准正态分布对应的-5%的分位数 #请根据题目要求更改#
for i in range(l, len(r)):  
    mhat, shat = norm.fit(r[i-50:i]) 解析：这里是对i时间点之前的50个历史数据进行正态分布拟合，然后返回mhat均值和shat标准差  #请根据题设要求修改历史数据量#
    VaR_RM[i] = -(mhat + qalpha*shat) 解析：计算公式采取尾部风险PPT第6页公式，计算单期VaR   #请根据题设条件修改VaR期数#
plt.plot(r)
plt.plot(VaR_RM*-1)
plt.show()
```


![png](output_3_0.png)
    



```python
#gamma-normal方法 改编于尾部风险ppt第27页
l = np.fix(len(r)/3).astype(int)  解析：同上#请根据题设改变#
VaR_GN = np.zeros(len(r))  解析：同上
qalpha = norm.ppf(0.05)  解析：同上
for i in range(l, len(r)):
    am_ar_garch = arch_model(r[:i], mean='ar', lags=1, vol='garch', dist='normal', p=2, q=2) 
    解析：请参照尾部风险ppt27页和实验报告实验内容中的gamma-normal进行阅读   r[:i]表示使用i时间点之前的数据，lags=1表示均值方程的滞后项为1阶，vol=‘garch’表示采用garch，dist=‘normal’表示采用标准正态分布，p、q=2表示条件方差方程中的两个滞后项为2.
    #请根据题目要求修改dist的分布类型：t分布直接将normal改为t，对应实验报告思考题内容；将p、q、lags也进行题目条件修改。
    res_ar_garch = am_ar_garch.fit()   解析：进行拟合
    a = res_ar_garch.forecast(horizon=1, align='origin') 解析：使用拟合结果进行预测，horizon=1表示预测1期的值
    mu = a.mean['h.1'].iloc[-1] 解析：取出预测结果的均值
    sigma = a.variance['h.1'].iloc[-1] 解析：取出预测结果的方差，注意是方差而不是标准差
    VaR_GN[i] = -(mu + qalpha * np.sqrt(sigma))  解析：公式同上，但因为是方差而非标准差所以要开方
plt.plot(r)
plt.plot(VaR_GN*-1)
plt.show()
```


```python
# 历史模拟方法
l = np.fix(len(r)/3).astype(int) 解析：同上#请根据题设改变#
VaR_HS = np.zeros(len(r)) 解析：同上
qalpha = int(200*0.05) 解析：qalpha = int(200*0.05)表示200个历史数据中第10个#请根据题设修改历史数据量和分位数值
for i in range(l, len(r)):
    his_sample = r[i-200:i] 解析：200个历史数据量
    his_sample = np.sort(his_sample) 解析：np.sort默认升序
    VaR_HS[i] = -his_sample[qalpha-1] 解析：序号从0开始，qalpha-1就是第qalpha个。之所以要乘个负号，是因为his_sample[qalpha-1]是实际的收益率。这里不乘的话，因为后面要再乘一个-1，就会导致如果明明是正的收益率却结果会亏钱
plt.plot(r)
plt.plot(VaR_HS*-1)
plt.show()
```


​    
![png](output_5_0.png)
​    



```python
# POT方法
l = np.fix(len(r)/3).astype(int) 解析：同上#请根据题设改变#
VaR_EVT = np.zeros(len(r)) 解析：同上
alpha = 0.05 解析：显著性水平#请根据题设改变#
for i in range(l, len(r)):  
    his_sample = r[i-200:i] 解析：i时间点前200个历史数据#请根据题设改变#
    his_sample = np.sort(his_sample)  解析：默认升序
    ind = np.ceil(len(his_sample)*0.1).astype(int) 解析：这里np.ceil是向上取整（1.1变2）和np.fix不同。阈值设置u为样本内数据十分位对应的值0.1#请根据题设条件改变#
    evt_sample = np.abs(his_sample[:ind]) 解析：取绝对值
    u = evt_sample[-1]解析：evt_sample来自于his_sample，所以是升序排序的，最后一项就是其中最大项
    evt_sample = evt_sample - u 解析：各个亏损超过u所对应的超额亏损
    evt_sample = np.delete(evt_sample, -1)解析：把最大项u给删除，得到超出阈值部分样本
    n = len(his_sample)解析：历史数据量个数
    Nu = len(evt_sample)解析：超出阈值的样本个数，删除了一个u。如果存在和u等大的，也称作超出阈值的样本个数就行了。
    parmhat = genpareto.fit(evt_sample, floc=0)解析：用于拟合广义帕累托分布GPD尾部风险PPT第十五页
    kHat = parmhat[0]; 解析：提取形状参数  尾部风险PPT第十五页
    sigmaHat = parmhat[2]; 解析：提取尺度参数    尾部风险PPT第十五页
    解析：尺度参数σ 大于0形状参数ε大于0时, GPD具有厚尾的特点，尾部风险PPT第十五页，注意可能出题要求判断
    VaR_EVT[i] = u + sigmaHat / kHat * ((alpha * n / Nu) ** -kHat - 1)
    解析：公式来自于尾部风险PPT第16页   这里老师原来的代码是alpha，但是应该用置信水平而不是显著性水平我直接就改了
plt.plot(r)
plt.plot(VaR_EVT*-1)
plt.show()
```


​    
![png](output_6_0.png)
​    



```python
data = pd.DataFrame({'return': r, 'VaR_RM': VaR_RM, 'VaR_GN': VaR_GN, 'VaR_HS': VaR_HS, 'VaR_EVT': VaR_EVT})
data.to_csv('Data_VaR.csv')
```


```python
def myfun_Kupiec(r, VaR, pstar):
    N = np.sum(r > VaR)
    T = len(r)
    LRuc = -2*((T-N)*np.log(1-pstar)+N*np.log(pstar)) + 2*((T-N)*np.log(1-N/T)+N*np.log(N/T))
    pvalue_LRuc = 1 - chi2.cdf(LRuc, 1)
    return LRuc, pvalue_LRuc

def myfun_Christoffersen(r, VaR):
    ind = r > VaR
    ind1 = ind[:-1]
    ind2 = ind[1:]
    n00 = np.sum((ind1==0) & (ind2==0))
    n01 = np.sum((ind1==0) & (ind2==1))
    n10 = np.sum((ind1==1) & (ind2==0))
    n11 = np.sum((ind1==1) & (ind2==1))

    Pi01 = n01/(n01+n00)
    Pi11 = n11/(n10+n11)
    Pi2 = (n01+n11)/(n00+n01+n10+n11)

    LRind = (n00+n10)*np.log(1-Pi2) + (n01+n11)*np.log(Pi2) - \
            n00*np.log(1-Pi01) - n01*np.log(Pi01) - n10*np.log(1-Pi11) - n11*np.log(Pi11)
    LRind = LRind*-2
    pvalue_LRind = 1 - chi2.cdf(LRind, 1)
    return LRind, pvalue_LRind

def myfun_Kupiec_Christoffersen(LRuc, LRind):
    LRcc = LRuc + LRind
    pvalue_LRcc = 1 - chi2.cdf(LRcc, 2)
    return LRcc, pvalue_LRcc

data = pd.read_csv('Data_VaR.csv')
ind = data['VaR_RM'] > 0
r = data.loc[ind, ['return']].values*-1
VaR_RM = data.loc[ind, ['VaR_RM']].values
VaR_GN = data.loc[ind, ['VaR_GN']].values
VaR_HS = data.loc[ind, ['VaR_HS']].values
VaR_EVT = data.loc[ind, ['VaR_EVT']].values

pstar = 0.05;
[LRuc_RM, pvalue_LRuc_RM] = myfun_Kupiec(r, VaR_RM, pstar)
[LRind_RM, pvalue_LRind_RM] = myfun_Christoffersen(r, VaR_RM)
[LRcc_RM, pvalue_LRcc_RM] = myfun_Kupiec_Christoffersen(LRuc_RM, LRind_RM)

[LRuc_GN, pvalue_LRuc_GN] = myfun_Kupiec(r, VaR_GN, pstar)
[LRind_GN, pvalue_LRind_GN] = myfun_Christoffersen(r, VaR_GN)
[LRcc_GN, pvalue_LRcc_GN] = myfun_Kupiec_Christoffersen(LRuc_GN, LRind_GN)

[LRuc_HS, pvalue_LRuc_HS] = myfun_Kupiec(r, VaR_HS, pstar)
[LRind_HS, pvalue_LRind_HS] = myfun_Christoffersen(r, VaR_HS)
[LRcc_HS, pvalue_LRcc_HS] = myfun_Kupiec_Christoffersen(LRuc_HS, LRind_HS)

[LRuc_EVT, pvalue_LRuc_EVT] = myfun_Kupiec(r, VaR_EVT, pstar)
[LRind_EVT, pvalue_LRind_EVT] = myfun_Christoffersen(r, VaR_EVT)
[LRcc_EVT, pvalue_LRcc_EVT] = myfun_Kupiec_Christoffersen(LRuc_EVT, LRind_EVT)


print('{:12s}, {:>12s}, {:>12s}, {:>12s}, {:>12s}, {:>12s}, {:>12s}'.format('', 'LRuc', 'pLRuc', 'LRind', 'pLRind', 'LRcc', 'pLRcc'))
print('{:12s}, {:12.4f}, {:12.4f}, {:12.4f}, {:12.4f}, {:12.4f}, {:12.4f}'.format('RiskMetrics', LRuc_RM, pvalue_LRuc_RM, LRind_RM, pvalue_LRind_RM, LRcc_RM, pvalue_LRcc_RM))
print('{:12s}, {:12.4f}, {:12.4f}, {:12.4f}, {:12.4f}, {:12.4f}, {:12.4f}'.format('GarchNormal', LRuc_GN, pvalue_LRuc_GN, LRind_GN, pvalue_LRind_GN, LRcc_GN, pvalue_LRcc_GN))
print('{:12s}, {:12.4f}, {:12.4f}, {:12.4f}, {:12.4f}, {:12.4f}, {:12.4f}'.format('HisSim', LRuc_HS, pvalue_LRuc_HS, LRind_HS, pvalue_LRind_HS, LRcc_HS, pvalue_LRcc_HS))
print('{:12s}, {:12.4f}, {:12.4f}, {:12.4f}, {:12.4f}, {:12.4f}, {:12.4f}'.format('EVT GPD', LRuc_EVT, pvalue_LRuc_EVT, LRind_EVT, pvalue_LRind_EVT,LRcc_EVT, pvalue_LRcc_EVT))
```
