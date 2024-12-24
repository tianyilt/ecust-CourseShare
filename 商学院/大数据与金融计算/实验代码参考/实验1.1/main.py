import numpy
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from scipy.io import loadmat
from scipy.stats import norm,kstest
import powerlaw

plt.rcParams.update({"font.family": "STIXGeneral",
                      "font.size": 20,
                      "mathtext.fontset": "cm"})##更新参数

def retrun_on_teporal():
    matdata = loadmat('SSEC_min.mat')
    p_min = matdata['p']
    p_min = p_min[:, 0]
    mark=-1
    marklist=[]
    for i in p_min:
        mark+=1
        if i==0:
            marklist.append(mark)
    p_min=np.delete(p_min,marklist)
    r_min1 = np.log(p_min[1:]) - np.log(p_min[:-1])
    r_min5 = np.log(p_min[5:]) - np.log(p_min[:-5])
    r_min10 = np.log(p_min[10:]) - np.log(p_min[:-10])
    r_min30 = np.log(p_min[30:]) - np.log(p_min[:-30])
    r_min60 = np.log(p_min[60:]) - np.log(p_min[:-60])
    r_min120 = np.log(p_min[120:]) - np.log(p_min[:-120])
    r_min240 = np.log(p_min[240:]) - np.log(p_min[:-240])
    r_min1=r_min1[(r_min1 >= -0.2) & (r_min1 <= 0.2)]
    r_min5 = r_min5[(r_min5 >= -0.2) & (r_min5 <= 0.2)]
    r_min10 = r_min10[(r_min10 >= -0.2) & (r_min10 <= 0.2)]
    r_min30 = r_min30[(r_min30 >= -0.2) & (r_min30 <= 0.2)]
    r_min60 = r_min60[(r_min60 >= -0.2) & (r_min60 <= 0.2)]
    r_min120 = r_min120[(r_min120 >= -0.2) & (r_min120 <= 0.2)]
    r_min240 = r_min240[(r_min240 >= -0.2) & (r_min240 <= 0.2)]
    plt.plot(r_min1,color='r')
    plt.show()
    plt.plot(r_min5,color='g')
    plt.show()
    plt.plot(r_min10,color='b')
    plt.show()
    plt.plot(r_min30,color='y')
    plt.show()
    plt.plot(r_min60,color='k')
    plt.show()
    plt.plot(r_min120, color='m')
    plt.show()
    plt.plot(r_min240, color='c')
    plt.show()
    return r_min1,r_min5,r_min10,r_min30,r_min60,r_min120,r_min240

def PDF(data_sample,num_bin=301):
    mark=0
    x_emp_list=[]
    y_emp_list=[]
    for j in data_sample:
        mark+=1
        bin = np.linspace(np.min(j), np.max(j), num_bin)
        x_emp = np.zeros(len(bin) - 1)
        y_emp = np.zeros(len(bin) - 1)
        for i in range(len(bin) - 1):
            x_emp[i] = bin[i] / 2 + bin[i + 1] / 2
            y_emp[i] = np.sum((j >= bin[i]) & (j < bin[i + 1])) / len(j) / (bin[i + 1] - bin[i])
        ind = y_emp > 0
        x_emp = x_emp[ind]
        y_emp = y_emp[ind]
        x_emp_list.append(x_emp)
        y_emp_list.append(y_emp)
        if mark==1:
            plt.semilogy(x_emp, y_emp, 'o-r')
        elif mark==2:
            plt.semilogy(x_emp, y_emp, 'o-g')
        elif mark==3:
            plt.semilogy(x_emp, y_emp, 'o-b')
        elif mark==4:
            plt.semilogy(x_emp, y_emp, 'o-y')
        elif mark==5:
            plt.semilogy(x_emp, y_emp, 'o-k')
        elif mark==6:
            plt.semilogy(x_emp, y_emp, 'o-m')
        elif mark==7:
            plt.semilogy(x_emp, y_emp, 'o-c')
    plt.show()
    return x_emp_list,y_emp_list

def norm1(x_emp_list,y_emp_list,data_sample):
    mark=0
    for i in range(0,7):
        mark+=1
        mu_min, sigma_min = norm.fit(data_sample[i])
        x_fit_min = np.linspace(-0.1, 0.1, 300)
        y_fit_min = norm.pdf(x_fit_min, loc=mu_min, scale=sigma_min)
        if mark == 1:
            plt.loglog(x_emp_list[i], y_emp_list[i], 'or', lw=2, ms=7, mfc='k')
            plt.show()
            plt.semilogy(x_fit_min, y_fit_min, '-k')
            plt.semilogy(x_emp_list[i], y_emp_list[i], 'o-r')
            plt.text(-0.075, 0.035, 'minute1', fontsize=20)
        elif mark == 2:
            plt.loglog(x_emp_list[i], y_emp_list[i], 'og', lw=2, ms=7, mfc='k')
            plt.show()
            plt.semilogy(x_fit_min, y_fit_min, '-k')
            plt.semilogy(x_emp_list[i], y_emp_list[i], 'o-g')
            plt.text(-0.075, 0.035, 'minute5', fontsize=20)
        elif mark == 3:
            plt.loglog(x_emp_list[i], y_emp_list[i], 'ob', lw=2, ms=7, mfc='k')
            plt.show()
            plt.semilogy(x_fit_min, y_fit_min, '-k')
            plt.semilogy(x_emp_list[i], y_emp_list[i], 'o-b')
            plt.text(-0.075, 0.035, 'minute10', fontsize=20)
        elif mark == 4:
            plt.loglog(x_emp_list[i], y_emp_list[i], 'oy', lw=2, ms=7, mfc='k')
            plt.show()
            plt.semilogy(x_fit_min, y_fit_min, '-k')
            plt.semilogy(x_emp_list[i], y_emp_list[i], 'o-y')
            plt.text(-0.075, 0.035, 'minute30', fontsize=20)
        elif mark == 5:
            plt.loglog(x_emp_list[i], y_emp_list[i], 'ok', lw=2, ms=7, mfc='k')
            plt.show()
            plt.semilogy(x_fit_min, y_fit_min, '-k')
            plt.semilogy(x_emp_list[i], y_emp_list[i], 'o-k')
            plt.text(-0.075, 0.035, 'minute60', fontsize=20)
        elif mark == 6:
            plt.loglog(x_emp_list[i], y_emp_list[i], 'om', lw=2, ms=7, mfc='k')
            plt.show()
            plt.semilogy(x_fit_min, y_fit_min, '-k')
            plt.semilogy(x_emp_list[i], y_emp_list[i], 'o-m')
            plt.text(-0.075, 0.035, 'minute120', fontsize=20)
        elif mark == 7:
            plt.loglog(x_emp_list[i], y_emp_list[i], 'oc', lw=2, ms=7, mfc='k')
            plt.show()
            plt.semilogy(x_fit_min, y_fit_min, '-k')
            plt.semilogy(x_emp_list[i], y_emp_list[i], 'o-c')
            plt.text(-0.075, 0.035, 'minute240', fontsize=20)
        plt.xlim([-0.1, 0.1])
        plt.xticks([-0.1, -0.05, 0, 0.05, .1])
        plt.ylim([10. ** -4, 10 ** 3])
        plt.yticks(10. ** np.arange(-4, 4, 2))
        plt.xlabel(r'$r$', fontsize=20)
        plt.ylabel(r'$p(r)$', fontsize=20)
        plt.text(-0.045, 0.00025, 'minutefit', fontsize=20)
        plt.show()
def kstext(data_sample):
    dict={}
    for i in data_sample:
        ks_statistic, p_value = kstest(i,'norm')
        dict[ks_statistic]=p_value
    print(dict)
    return dict

def powerlaw1(data_sample):
    for i in data_sample:
        fit = powerlaw.Fit(i[::500])
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


if __name__ == '__main__':
    r_min1,r_min5,r_min10,r_min30,r_min60,r_min120,r_min240=retrun_on_teporal()
    data_sample=[r_min1,r_min5,r_min10,r_min30,r_min60,r_min120,r_min240]
    x_emp_list,y_emp_list=PDF(data_sample)
    norm1(x_emp_list,y_emp_list,data_sample)
    kstext(data_sample)
    powerlaw1(data_sample)














