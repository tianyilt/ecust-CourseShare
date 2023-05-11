% 首先输入离散数据
x = linspace(0,2*pi,21);
y = sin(x);

% 指定求导点0,2,4,6
xx = 0:0.1:2*pi;
dx = 0:2:6;

% 对离散数据采用polyfit函数进行拟合，并通过polyder求导函数，
% 然后通过polyval计算导数值
pp1 = polyfit(x,y,3);
ppv1 = polyval(pp1,xx);
dp1 = polyder(pp1);
dpv1 = polyval(dp1,dx);

% 对离散数据采用csaps函数进行插值，并通过fner求导函数，
% 然后通过fnval计算导数值
pp2 = csaps(x,y);
ppv2 = fnval(pp2,xx);
dp2 = fnder(pp2);
dpv2 = fnval(dp2,dx);

% 拟合效果画图对比
plot(x,y,'ok',xx,ppv1,'b:',xx,ppv2,'r:')
legend('原始数据','多项式拟合','样条插值')

% 微分计算结果对比
figure
plot(dx,dpv1,'b*',dx,dpv2,'ro')
legend('多项式拟合求导','样条插值求导')
