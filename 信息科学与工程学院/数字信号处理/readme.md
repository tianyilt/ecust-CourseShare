# 数字信号处理（3 学分）

名曰线上线下结合，实际上作业多，线上自学耗时长，小测多，压力是很大的。实验也是时间短任务多。

实验不保证代码能够正常执行，特别是最后的大作业。。事实上，本次实验代码几乎全部在 [octave](https://absx.pages.dev/coding/octave.html) 上执行。

实验报告使用 typst 生成，源码详见[此处](https://github.com/lxl66566/my-college-files/tree/main/信息科学与工程学院/数字信号处理)。本人不对合法性与正确性作出任何保证。

## 2023 考试

这门课考的还算中规中矩。

小题 5 分 \* 8 题，大题 15 分 \* 4 题。

一些小题：

- 求稳定和因果
- 傅立叶变换，已知 $H(j\omega)=(1-e^{-j\omega})(1-e^{-2j\omega})$，求 $h(n)$，判断是否线性相位，如果是则求群延迟
- 上采样，低通滤波，下采样，求增益和截止频率。（唯一一题考第八章的）
- 给出条件和几个零点，求所有剩下的零点，并求出最小阶数和群延迟
- （重叠保留法）长序列求 FFT 次数和复乘次数，经典必考题。参数大概是 10s, 1kHz, 100 点 h(n) 和 512 点 FFT。复乘次数是整个系统的总次数（包括 IFFT）。

15 分大题：

- 一阶：设计一个陷波器，滤去某一频率的信号，需要写参数。
- IIR：给 $H(s)=\frac{1}{s+a}$，分别使用脉冲响应不变法和双线性变换法设计，如果 $H(s)=\frac{s}{s+a}$，还能否用双线性变换法，说明理由。
  - 没有考模拟滤波器设计（巴特沃斯）
- FIR：考了频域采样法。$H_d(e^{j\omega})=\begin{cases}1 & 0.48\pi\leq\omega\leq\pi \\ 0 & \omega<0.4\pi\end{cases}$，设计高通滤波器，在过渡带不采样和过渡带采样一个点（0.3904）的条件下，分别求 $H(k)$ 和 $\theta(k)$，并对比。
  - 没有考窗函数设计法。
- 最后是一个经典的采样 - 滤波 - 恢复问题。采样和恢复的周期是不同的，每个步骤都要画频谱图。~~我记得信号与系统也考过差不多的题目~~

## 线下作业答案

按照章节排序。

```
http://cs.e.ecust.edu.cn/download/e6ca15b56d2cf6abf3cfc5fd2e8f6748
http://cs.e.ecust.edu.cn/download/dc008ad8fc74878546b45a2871c23346
http://cs.e.ecust.edu.cn/download/17ff12a4cc31129538bbbdc944d9ced6
http://cs.e.ecust.edu.cn/download/cd67c0cccf58e1ae3429e2ab34e9431b
http://cs.e.ecust.edu.cn/download/e7503fb9defe1c39f5862b5d730ff63a
```

## [笔记](https://absx.pages.dev/farraginous/learning/dsp2.html)
