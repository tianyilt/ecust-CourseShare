import numpy as np
import requests
import re
import pandas as pd

def xlsxget():
    urlsa = ['https://www.chinabond.com.cn/cb/cn/zzsj/zzjgcp/cpxz/qxxz/zzgzqx/list_1.shtml',
             'https://www.chinabond.com.cn/cb/cn/zzsj/zzjgcp/cpxz/qxxz/zzgzqx/list_2.shtml']
    headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/112.0.0.0 Safari/537.36'}
    count = -1
    for urla in urlsa:
        res = requests.get(urla, headers=headers)
        res.encoding = res.apparent_encoding
        texta = res.text
        pattern_a = re.compile('<a title=".*?年中债国债收益率曲线标准期限信息" href="(.*?)".*?target="_blank">.*?</a>',
                               re.S)
        before = 'https://www.chinabond.com.cn/'
        urlsb = re.findall('''<a title='.*?年中债国债收益率曲线标准期限信息' href="(.*?)".*?target="_blank">.*?</a>''',
                           texta, re.S)
        finallist = []
        for i in range(len(urlsb)):
            urlsb[i] = before + urlsb[i]
        for i in urlsb:
            res1 = requests.get(i, headers=headers)
            res1.encoding = res1.apparent_encoding
            textb = res1.text
            pattern_b = re.compile('<a href="(.*?)".*?trimString', re.S)
            xlsx = re.findall(pattern_b, textb)
            xlsx = xlsx[0]
            xlsx = 'https://www.chinabond.com.cn/' + xlsx
            finallist.append(xlsx)  ##两个列表合并？
        for i in finallist:
            count += 1
            resc = requests.get(i, headers=headers)
            textc = resc.content
            with open(str(count) + '.xlsx', mode='wb') as fobj:
                fobj.write(textc)
                print('ok')
def append():
    finalxlsx=pd.read_excel('1.xlsx',usecols=[0,1,3])
    finalxlsx.columns=['date','year','ytm']
    finalxlsx['date']=pd.to_datetime(finalxlsx['date'],format='%Y-%m-%d')
    for i in range(2,13):
        xlsx=pd.read_excel(str(i)+'.xlsx',usecols=[0,1,3])
        xlsx.columns=['date','year','ytm']
        xlsx['date']=pd.to_datetime(xlsx['date'],format='%Y-%m-%d')
        finalxlsx=pd.concat([finalxlsx,xlsx],ignore_index=True)
    finalxlsx=finalxlsx[finalxlsx['year']=='10y']
    finalxlsx=finalxlsx.sort_values(by='date',axis=0,ascending = True)
    finalxlsx=finalxlsx.reset_index()
    finalxlsx.to_excel('十年期国债ytm.xlsx')

def todailyreturn():
    xlsx=pd.read_excel('十年期国债ytm.xlsx',usecols=[0,2])
    xlsx.columns=['date','ytm']
    xlsx['date']=pd.to_datetime(xlsx['date'],format('%Y-%m-%d'))
    xlsx['dailyreturn']=np.log(xlsx['ytm'])-np.log(xlsx['ytm']).shift(periods=1)
    xlsx.dropna(inplace=True)
    xlsx.to_excel('十年期国债dailyreturn.xlsx',index=False)

def append1():
    xlsx2010=pd.read_excel('2010.xlsx',usecols=[0,2,3,4])
    xlsx2011_2015=pd.read_excel('2011-2015.xlsx',usecols=[0,2,3,4])
    xlsx2016_2020=pd.read_excel('2016-2020.xlsx',usecols=[0,2,3,4])
    xlsx2021=pd.read_excel('2021.xlsx',usecols=[0,2,3,4])
    xlsxlist=[xlsx2010,xlsx2011_2015,xlsx2016_2020,xlsx2021]
    dict={}
    for i in range(len(xlsxlist)):
        xlsxlist[i].columns=['code','date','return','mkt']
        for j in xlsxlist[i]['code'].unique():
            dict[j]=dict.get(j,0)+1
    codelist=[]
    for i in dict.keys():
        if dict[i]==4:
            codelist.append(i)
    final=''
    for i in codelist:
        final=final+' '+str(i)
    print(final)


def mkt():
    data=pd.read_excel('股票数据.xlsx')
    rf=pd.read_excel('rf.xlsx')
    data.columns=['code','date','return','mkt']
    rf.columns=['date','rf']
    data['date']=pd.to_datetime(data['date'],format('%Y-%m-%d'))
    rf['date']=pd.to_datetime(rf['date'],format('%Y-%m-%d'))
    newdata=pd.merge(left=data,right=rf,on='date',how='inner')
    newdata['mkt-rf']=newdata['mkt']-newdata['rf']
    newdata.dropna(inplace=True)##这里删除了一些数据，说明本来就存在某些数据的地方是NA。
    newdata.to_excel('股票日度数据.xlsx')

# def codemkt_add_tenyears():
#     codemkt=pd.read_excel('股票日度数据.xlsx',usecols=[0,1,2,5])
#     tenyears=pd.read_excel('十年期国债dailyreturn.xlsx',usecols=[0,2])
#     codemkt.columns=['code','date','return','mkt']
#     tenyears.columns=['date','dailyreturn']
#     codemkt['date']=pd.to_datetime(codemkt['date'],format('%Y-%m-%d'))
#     tenyears['date']=pd.to_datetime(tenyears['date'],format('%Y-%m-%d'))
#     newdata=pd.merge(left=codemkt,right=tenyears,how='inner',on='date')
#     newdata.dropna(inplace=True)
#     newdata.to_excel('汇总.xlsx')

def codemkt_add_tenyears_shin():
    codemkt=pd.read_excel('汇总.xlsx',usecols=[0,1,2,3])
    tenyears=pd.read_excel('十年国债.xlsx',usecols=[1,2])
    codemkt.columns=['code','date','code_return','mkt']
    tenyears.columns=['date','ten_return']
    codemkt['date']=pd.to_datetime(codemkt['date'])
    tenyears['date']=pd.to_datetime(tenyears['date'])
    newdata=pd.merge(left=codemkt,right=tenyears,on='date',how='inner')
    newdata.to_excel('汇总1.xlsx')

def ff5():##处理原始的ff五因子数据
    ff5=pd.read_excel('fivefactor_daily.xlsx',usecols=[0,1,2,3,4,5,6])
    ff5.columns=['date','mkt_rf','smb','hml','umd','rmw','cma']
    ff5['date']=pd.to_datetime(ff5['date'],format('%Y-%m-%d'))
    ff5['year']=ff5['date'].dt.year
    ff5=ff5[ff5['year']<=2021]
    ff5=ff5[ff5['year']>=2010]
    ff5=ff5.iloc[:,:-1]
    ff5['date']=ff5['date'].apply(lambda x:x.strftime('%Y-%m-%d'))
    ff5.to_excel('ff5.xlsx')

def ff5_code_ten():
    ff5=pd.read_excel('ff5.xlsx')
    code_ten=pd.read_excel('汇总1.xlsx',usecols=[0,1,2,4])
    ff5.columns=['date','mkt_rf','smb','hml','umd','rmw','cma']
    code_ten.columns=['code','date','code_return','ten_return']
    ff5['date']=pd.to_datetime(ff5['date'])
    code_ten['date']=pd.to_datetime(code_ten['date'])
    final=pd.merge(left=ff5,right=code_ten,on='date',how='inner')
    final.to_excel('汇总2.xlsx')


def test():
    df1 = pd.DataFrame({'a': [1, 2], 'b': [5, 6]})
    df2 = pd.DataFrame({'a': [2, 1, 0], 'y': [6, 7, 8]})
    df3 = pd.merge(left=df1,right=df2,how='inner',on='a')
    print(df3)

if __name__ == '__main__':
    ff5_code_ten()










