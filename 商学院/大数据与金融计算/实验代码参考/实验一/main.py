import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from scipy.io import loadmat
from scipy.stats import norm
import powerlaw

####%matplotlib inline 不能在pycharm中使用

plt.rcParams.update({"font.family": "STIXGeneral",
                      "font.size": 20,
                      "mathtext.fontset": "cm"})##更新参数
ssec_daily = pd.read_csv('1LShowData_SSEC_daily.csv', encoding='GB2312', usecols=[6])##usecols：六号列，第七列
p_daily = ssec_daily['收盘'].values##p_daily类型是numpy.ndarray，这里就和列表一样

r_daily = np.log(p_daily[1:]) - np.log(p_daily[:-1])###获得对数收益率，[:-1]表示左闭右开****
matdata = loadmat('SSEC_min.mat')##是一个字典类型
p_min = matdata['p']##取出键值p对应的值，类型是numpy.ndarray包着的numpy.ndarray,是分钟数据
p_min = p_min[:,0]##保留了所有行和第一列，这里转换为了numpy.ndarray
r_min = np.log(p_min[1:]) - np.log(p_min[:-1])#return on min 对数收益率
r_min = r_min[(r_min >= -0.1) & (r_min <= 0.1)]#筛选出r_min数组中取值在-0.1到0.1之间的元素

def myfun_emp_pdf(data_sample, num_bin=31):
    bin = np.linspace(np.min(data_sample), np.max(data_sample), num_bin)##在指定的间隔内返回均匀间隔的数字.序列的起始值。序列的结束值。生成的样本数量。一共有num_bin-1个区间
    x_emp = np.zeros(len(bin)-1)##用于创建一个指定形状的全零数组。比bin的个数少1
    y_emp = np.zeros(len(bin)-1)##用于创建一个指定形状的全零数组。
    for i in range(len(bin)-1):##比bin的个数少1
        x_emp[i] = (bin[i] + bin[i+1])/2##bin中两个分隔数的均值
        y_emp[i] = np.sum( (data_sample >= bin[i]) & (data_sample < bin[i+1]) )  /len(data_sample)/(bin[i+1] - bin[i])##datasample中大于等于bin[i]且小于bin[i+1]的值相加
    return x_emp, y_emp






if __name__ == '__main__':
    x_emp_daily, y_emp_daily = myfun_emp_pdf(r_daily)
    x_emp_min, y_emp_min = myfun_emp_pdf(r_min, num_bin=301)
    ind = y_emp_min > 0
    x_emp_min = x_emp_min[ind]
    y_emp_min = y_emp_min[ind]
    mu_daily, sigma_daily = norm.fit(r_daily)
    mu_min, sigma_min = norm.fit(r_min)
    x_fit_daily = np.linspace(-0.1, 0.1, 300)
    y_fit_daily = norm.pdf(x_fit_daily, loc=mu_daily, scale=sigma_daily)
    x_fit_min = np.linspace(-0.1, 0.1, 300)
    y_fit_min = norm.pdf(x_fit_min, loc=mu_min, scale=sigma_min)
    #plt.semilogy(x_emp_daily, y_emp_daily, 'o-r')
    #plt.show()
    #plt.semilogy(x_fit_daily, y_fit_daily, '-m')
    #plt.show()
    #plt.semilogy(x_emp_min, y_emp_min, 's-b')
    plt.semilogy(x_fit_min, y_fit_min, '-k', lw=2, label=r'$r_m$ Norm Fits')
    plt.xlim([-0.1, 0.1])
    plt.xticks([-0.1, -0.05, 0, 0.05, .1])
    plt.show()
    #plt.loglog(x_emp_min, y_emp_min, 'or', lw=2, ms=7, mfc='k')
    #plt.show()

    plt.semilogy(x_emp_daily, y_emp_daily, 'o-r', lw=2, ms=7, mfc='k', label=r'$r_d$ Emp PDF')
    plt.semilogy(x_fit_daily, y_fit_daily, '-m', lw=2, label=r'$r_d$ Norm Fits')
    plt.semilogy(x_emp_min, y_emp_min, 's-b', lw=2, ms=7, mfc='k', label=r'$r_m$ Emp PDF')
    plt.semilogy(x_fit_min, y_fit_min, '-k', lw=2, label=r'$r_m$ Norm Fits')
    plt.xlim([-0.1, 0.1])
    plt.xticks([-0.1, -0.05, 0, 0.05, .1])
    plt.ylim([10. ** -4, 10 ** 3])
    plt.yticks(10. ** np.arange(-4, 4, 2))
    plt.xlabel(r'$r$', fontsize=20)
    plt.ylabel(r'$p(r)$', fontsize=20)
    plt.text(-0.075, 0.035, 'daily', fontsize=20)
    plt.text(-0.045, 0.00025, 'minute', fontsize=20)
    plt.legend(loc='upper right', fontsize=10)
    plt.show()
    print(type(r_daily))
    fit = powerlaw.Fit(r_daily)
    fig = fit.plot_pdf(color='b', linewidth=2)
    fit.power_law.plot_pdf(color='b', linestyle='--', ax=fig)
    fit.plot_ccdf(color='r', linewidth=2)
    fit.power_law.plot_ccdf(color='r', linestyle='--', ax=fig)
    print('alpha:', fit.alpha)
    print('xmin:', fit.xmin)
    R, p = fit.distribution_compare('power_law', 'lognormal')
    print('log-likelihood ratio test:', R)
    print('p-value:', p)
    plt.show()






