```python
import pandas as pd
import numpy as np
```


```python
data = pd.read_csv('3-B_EXAM4.csv', encoding='GB2312')
data
```


<div>
<style scoped>
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }
    
    .dataframe thead th {
        text-align: right;
    }
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>日期</th>
      <th>市场指数</th>
      <th>组合1</th>
      <th>组合2</th>
      <th>组合3</th>
      <th>组合4</th>
      <th>组合5</th>
      <th>无风险利率</th>
      <th>市场溢酬因子</th>
      <th>市值因子</th>
      <th>账面市值比因子</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>20090109</td>
      <td>1904.86</td>
      <td>1727.01</td>
      <td>1281.30</td>
      <td>1591.43</td>
      <td>2469.13</td>
      <td>1822.58</td>
      <td>0.000043</td>
      <td>0.0204</td>
      <td>0.0083</td>
      <td>0.0010</td>
    </tr>
    <tr>
      <th>1</th>
      <td>20090112</td>
      <td>1900.35</td>
      <td>1715.86</td>
      <td>1300.27</td>
      <td>1590.85</td>
      <td>2488.00</td>
      <td>1829.90</td>
      <td>0.000042</td>
      <td>0.0044</td>
      <td>0.0102</td>
      <td>-0.0021</td>
    </tr>
    <tr>
      <th>2</th>
      <td>20090113</td>
      <td>1863.37</td>
      <td>1667.97</td>
      <td>1273.80</td>
      <td>1551.21</td>
      <td>2407.01</td>
      <td>1774.56</td>
      <td>0.000041</td>
      <td>-0.0249</td>
      <td>-0.0019</td>
      <td>0.0074</td>
    </tr>
    <tr>
      <th>3</th>
      <td>20090114</td>
      <td>1928.87</td>
      <td>1750.08</td>
      <td>1329.63</td>
      <td>1607.21</td>
      <td>2463.77</td>
      <td>1817.24</td>
      <td>0.000041</td>
      <td>0.0427</td>
      <td>0.0029</td>
      <td>-0.0022</td>
    </tr>
    <tr>
      <th>4</th>
      <td>20090115</td>
      <td>1920.21</td>
      <td>1739.64</td>
      <td>1334.24</td>
      <td>1614.49</td>
      <td>2456.65</td>
      <td>1814.10</td>
      <td>0.000040</td>
      <td>0.0033</td>
      <td>0.0079</td>
      <td>-0.0031</td>
    </tr>
    <tr>
      <th>...</th>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
    </tr>
    <tr>
      <th>2422</th>
      <td>20181224</td>
      <td>2527.01</td>
      <td>1289.12</td>
      <td>1634.66</td>
      <td>1869.08</td>
      <td>7276.91</td>
      <td>5275.89</td>
      <td>0.000088</td>
      <td>0.0056</td>
      <td>-0.0008</td>
      <td>-0.0045</td>
    </tr>
    <tr>
      <th>2423</th>
      <td>20181225</td>
      <td>2504.82</td>
      <td>1259.94</td>
      <td>1605.20</td>
      <td>1846.48</td>
      <td>7256.91</td>
      <td>5251.07</td>
      <td>0.000090</td>
      <td>-0.0088</td>
      <td>-0.0034</td>
      <td>-0.0057</td>
    </tr>
    <tr>
      <th>2424</th>
      <td>20181226</td>
      <td>2498.29</td>
      <td>1250.42</td>
      <td>1598.94</td>
      <td>1843.40</td>
      <td>7216.06</td>
      <td>5193.21</td>
      <td>0.000091</td>
      <td>-0.0030</td>
      <td>0.0048</td>
      <td>0.0030</td>
    </tr>
    <tr>
      <th>2425</th>
      <td>20181227</td>
      <td>2483.09</td>
      <td>1236.36</td>
      <td>1587.71</td>
      <td>1831.41</td>
      <td>7233.59</td>
      <td>5144.72</td>
      <td>0.000091</td>
      <td>-0.0080</td>
      <td>-0.0095</td>
      <td>0.0024</td>
    </tr>
    <tr>
      <th>2426</th>
      <td>20181228</td>
      <td>2493.90</td>
      <td>1225.71</td>
      <td>1592.22</td>
      <td>1848.19</td>
      <td>7349.07</td>
      <td>5177.93</td>
      <td>0.000092</td>
      <td>0.0039</td>
      <td>-0.0031</td>
      <td>-0.0009</td>
    </tr>
  </tbody>
</table>
<p>2427 rows × 11 columns</p>





```python
p1 = data.iloc[:, 2].values
p2 = data.iloc[:, 3].values
p3 = data.iloc[:, 4].values
p4 = data.iloc[:, 5].values
p5 = data.iloc[:, 6].values
rf = data.iloc[:, 7].values
mkt = data.iloc[:, 8].values
p1    解析：得到收盘价
```




    array([1727.01, 1715.86, 1667.97, ..., 1250.42, 1236.36, 1225.71])




```python
r1 = np.log(p1[1:]) - np.log(p1[:-1])
r2 = np.log(p2[1:]) - np.log(p2[:-1])
r3 = np.log(p3[1:]) - np.log(p3[:-1])
r4 = np.log(p4[1:]) - np.log(p4[:-1])
r5 = np.log(p5[1:]) - np.log(p5[:-1])
r1  解析：得到对数收益率
```




    array([-0.00647718, -0.02830709,  0.04805418, ..., -0.00758461,
           -0.01130792, -0.00865131])




```python
rexc1 = r1 - rf[1:]
rexc2 = r2 - rf[1:]
rexc3 = r3 - rf[1:]
rexc4 = r4 - rf[1:]
rexc5 = r5 - rf[1:]
rexc1
解析：得到超额收益率
```




    array([-0.00651918, -0.02834809,  0.04801318, ..., -0.00767561,
           -0.01139892, -0.00874331])




```python
R = np.concatenate([rexc1[:, None], 
                    rexc2[:, None],
                    rexc3[:, None], 
                    rexc4[:, None],
                    rexc5[:, None]], 
                   axis=1)
R  解析：转为shape为(2426, 5)的ndarray.R中一列代表一个超额收益率序列
```




    array([[-0.00651918,  0.01465475, -0.00040652,  0.00757131,  0.00396624],
           [-0.02834809, -0.02060838, -0.02527419, -0.03313486, -0.03074982],
           [ 0.04801318,  0.04285515,  0.03542348,  0.02326638,  0.02372536],
           ...,
           [-0.00767561, -0.00399845, -0.00176043, -0.00573602, -0.01117086],
           [-0.01139892, -0.00713918, -0.00661653,  0.00233536, -0.00947206],
           [-0.00874331,  0.00274454,  0.00902862,  0.01574632,  0.00634242]])




```python
Cov_Sample = np.mat(np.cov(R, rowvar=False))解析：np.cov计算协方差矩阵，这里输入参数为ndarray类型的R，rowvar=False代表将每列作为一个随机变量。R的shape为(2426, 5)。np.cov返回的是ndarray类型，所以用np.mat将其转化为matrix类型
Cov_Sample  解析：方法1：样本方差-协方差矩阵  见协方差PPT第十页
```




    matrix([[0.00036161, 0.00031648, 0.00026988, 0.00021371, 0.00019017],
            [0.00031648, 0.00036965, 0.00028689, 0.00024158, 0.00022704],
            [0.00026988, 0.00028689, 0.00029853, 0.00021888, 0.00020663],
            [0.00021371, 0.00024158, 0.00021888, 0.00026741, 0.0002325 ],
            [0.00019017, 0.00022704, 0.00020663, 0.0002325 , 0.0002925 ]])




```python
X = np.mat(np.concatenate([np.ones((len(mkt)-1, 1)), mkt[1:, None]], axis=1))
X  解析:见协方差PPT第十二页。mkt[1:, None]就对应了ft。之所以mkt从序号1开始是因为mkt是和收盘价一一对应的
```




    matrix([[ 1.    ,  0.0044],
            [ 1.    , -0.0249],
            [ 1.    ,  0.0427],
            ...,
            [ 1.    , -0.003 ],
            [ 1.    , -0.008 ],
            [ 1.    ,  0.0039]])




```python
Y = np.mat(R)
AB_hat = (X.T*X).I*(X.T*Y)  解析：这里是为了求解α和B对应的值。 见协方差PPT第十二页
ALPHA = AB_hat[0] 解析：这里取的是AB_hat的第一行，总之就是常数项的系数对应α  见协方差PPT第十二页
BETA = AB_hat[1] 解析：这里取的是AB_hat的第二行，总之就是市场超额收益率的系数对应B  见协方差PPT第十二页
RESD = Y - X*AB_hat  解析：RESD就是ε_t  见协方差PPT第十二页
covfactor = np.cov(mkt[1:])  解析：mkt是和收盘价一一对应的，所以这里用mkt[1:]。np.cov(mkt[1:])是为了求出因子 f 的样本方差-协方差矩阵 见协方差PPT第十二页倒数第二行
covresidual = np.diag(np.diag(np.cov(RESD, rowvar=False))) 解析：np.cov(RESD, rowvar=False)解析：一列为一个随机变量计算协方差矩阵，然后使用np.diag提取对角线元素为一个ndarray，再通过提取出来的对角线元素构造新矩阵，如下图所示
Cov_Factor = BETA.T*covfactor*BETA + covresidual见协方差PPT第十二页倒数第四行公式
Cov_Factor##方法3：因子模型估计法
```

![image-20230614164109417](E:\大三下study\大数据与金融计算\実験5\第五次实验 协方差矩阵优化\图片1.png)


    matrix([[0.00036161, 0.00028866, 0.00026249, 0.00022798, 0.00022049],
            [0.00028866, 0.00036965, 0.00027923, 0.00024251, 0.00023454],
            [0.00026249, 0.00027923, 0.00029853, 0.00022053, 0.00021329],
            [0.00022798, 0.00024251, 0.00022053, 0.00026741, 0.00018524],
            [0.00022049, 0.00023454, 0.00021329, 0.00018524, 0.0002925 ]])




```python
c = 0.5
Cov_Shrink = c*Cov_Sample + (1-c)*Cov_Factor
解析：这里要注意c是加反的。但因为c是0.5所以不影响
Cov_Shrink
```




    matrix([[0.00036161, 0.00030257, 0.00026619, 0.00022084, 0.00020533],
            [0.00030257, 0.00036965, 0.00028306, 0.00024205, 0.00023079],
            [0.00026619, 0.00028306, 0.00029853, 0.0002197 , 0.00020996],
            [0.00022084, 0.00024205, 0.0002197 , 0.00026741, 0.00020887],
            [0.00020533, 0.00023079, 0.00020996, 0.00020887, 0.0002925 ]])




```python
uhat = np.mean(R, axis=0) 解析：得到五个组合各自的超额收益率的均值 uhat为shape(5,)的ndarray
A = np.mat(np.concatenate([uhat[:, None], np.ones((len(uhat), 1))], axis=1)).T  解析：uhat[:, None]uhat自己和None进行组合得到5*1的ndarray。axis=1表明两者列与列组合在一起。.T取转置后2*5的矩阵
up = np.mean(uhat) 解析：获得五个组合的平均超额收益率的平均值，是一个float类型
b = np.mat(np.array([up, 1])[:, None]) 解析：np.array([up, 1])获得(2,)ndaaray。([up, 1])[:, None]获得2*1ndaaray.然后通过 np.mat获得2*1矩阵
omega_Shrink = Cov_Shrink.I*A.T*(A*Cov_Shrink.I*A.T).I*b 解析：见协方差ppt第4页，公式来自于solution
print(omega_Shrink)
omega_Sample = Cov_Sample.I*A.T*(A*Cov_Sample.I*A.T).I*b解析：见协方差ppt第4页，公式来自于solution
print()
print(omega_Sample)
```

    [[ 0.32532288]
     [-0.21248216]
     [ 0.38898507]
     [ 0.23881412]
     [ 0.25936009]]
    
    [[ 0.39904587]
     [-0.32861957]
     [ 0.38202395]
     [ 0.23869463]
     [ 0.30885513]]



```python

```


```python

```
