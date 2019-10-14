%% 清屏
clc,clear;
%% 数据录入
t0683=[0 1.84 1.32 1.2 1.14 1.11 1.09 1.08 1.07 1.06]';
%标尺读数xi 单位cm
F=10:1.5:26.5;
F=F';%12个F等差，从10开始
x_increase=[2.1 2.4 2.5 2.8 3.1 3.4 3.7 3.9 4.2 4.5 4.75 5]';
x_decrease=[2.3 2.5 2.8 2.99 3.4 3.7 3.95 4.2 4.45 4.7 4.9 5]';
delta_xyi=0.05;
D=89.7*2;
%镜尺cm
delta_Dyi=0.05;
delta_Lyi=0.05;
%钢丝长度cm
L1=46.7;
L2=7.3;
L=abs(L2-L1);
%钢丝直径mm
chuzhi=-0.01;
delta_dyi=0.004;
d_chushi=[5.789 5.792 5.792 5.792 5.791 5.795]';%没有减去初值的原始数据
%光杠杆cm
b=8.5;
delta_byi=0.002;
%拉力kg
delta_Fyi=0.02
%% 逐差法求伸长量
%计算出来的U不确定度记得自行根据首位有效数字调节
x0=mean([x_increase x_decrease],2);
[xn,delta_x,s_deltax]=ComputeZhuCha(x0);
xn
delta_x
s_deltax
U_deltax=ComputeU(s_deltax,size(xn,1),t0683,delta_xyi)
%% 镜尺距
U_D=ComputeU(0,2,t0683,delta_Dyi)
%% 钢丝长度
U_L=ComputeU(0,2,t0683,delta_Lyi)
%% 钢丝直径
d=mean(d_chushi)-chuzhi
U_d=ComputeU(std(d),size(d_chushi,1),t0683,delta_dyi)
%% 光杠杆常数
U_b=ComputeU(0,2,t0683,delta_byi)
%% 钢丝所受拉力
fuzai_F=9.8*size(F,1)/2*(F(2)-F(1))
U_F=ComputeU(0,2,t0683,9.8*delta_Fyi)
%% 杨氏模量计算
Y=(8*fuzai_F*0.0001*L*D)/(pi*d^2*10^(-10)*b*delta_x)
E_Y=((U_L/L)^2+(U_D/D)^2+(2*U_d/d)^2+(U_b/b)^2+(U_deltax/delta_x)^2)^0.5
U_Y=E_Y*Y



%% 先调出fitting工具箱，然后X代入F Y代入x0
Y_linearfitting=(8*0.0001*L*D)/(pi*d^2*10^(-8)*b*0.001763/9.8)%注意！！！ 把拟合的斜率代入/9.8之前