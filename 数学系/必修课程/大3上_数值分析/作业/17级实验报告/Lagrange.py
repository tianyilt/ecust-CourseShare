import numpy as np
import matplotlib.pyplot as plt
def lagrange_out(x,y,xin):#定义拉格朗日插值拟合的函数
    print(x,y)
    n = len(x)
    out=0.0
    for i in range(n):
        tmp=y[i]
        for j in range(n):
            if not i==j:
                tmp*=np.poly1d([1.0,-x[j]])(xin)/(x[i]-x[j])#构造基函数
        out+=tmp
return out

def plot_curve(x:np.ndarray):#定义绘制函数图像的函数
    y=np.sin(x)
    t=np.arange(-5,5,0.001)
    s=np.sin(t);
    r=lagrange_out(x,y,t)
    print(r)
    plt.plot(t,s,c='blue',marker='1',linestyle=':',label='原函数')
    plt.plot(t,r,c='green',marker='.',linestyle='-.',label='拟合函数')
    plt.scatter(x,y,c='purple',marker='x',s=100)
    plt.legend(['f(x)=sin(x)','Lagrange fit','points'])
    plt.show()
plot_curve(np.arange(-5,5,1))
plot_curve(np.arange(-5,5,0.5))
plot_curve(np.arange(-5,5,0.2))


