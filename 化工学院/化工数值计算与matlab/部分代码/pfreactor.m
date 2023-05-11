function pfreactor
%绝热活塞流反应器中甲苯脱甲基反应转化率计算
global cpA cpB cpC cpD dcpA dcpB dcpC dcpD 
%输入热容关联式系数
cpA = [-24.355 27.143 -33.917 19.251];
cpB = [0.5124 9.273e-3 0.4743 5.212e-2];
cpC = [-2.765e-4 -1.38e-5 -3.017e-4 1.197e-5];
cpD = [4.911e-8 7.645e-9 7.13e-8 -1.131e-8];
%计算反应产物和反应物的热容系数差
dcpA = cpA(3)+cpA(4)-cpA(1)-cpA(2);
dcpB = cpB(3)+cpB(4)-cpB(1)-cpB(2);
dcpC = cpC(3)+cpC(4)-cpC(1)-cpC(2);
dcpD = cpD(3)+cpD(4)-cpD(1)-cpD(2);
%初始条件
T0 = 800;
ct0 = 1.0/(0.082*T0);
f1 = ct0/2.15;
f2 = f1*1.15;
f0 = [f1,f2,0,0,T0]';
l0 = 0;	l1 = 10*(1+eps);
[l,f] = ode45(@pfr,[l0 l1],f0);
%标绘沿反应器的组分浓度分布
plot(l,f(:,1),l,f(:,2),l,f(:,3))
xlabel('length(dm)')
ylabel('concentration(mol/liter)')
legend('toluene','hydrogen','benzene & methane')
figure
%标绘沿反应器的温度分布
plot(l,f(:,5))
xlabel('length(dm)')
ylabel('Temperature(K)')
% 转化率
mu = 1 - f(end,1)/f(1,1)

function yp = pfr(l,f)
%反应器质量和能量衡算方程
global cpA cpB cpC cpD dcpA dcpB dcpC dcpD 
As = pi*0.5^2/4;
qv = 3000*22.4*f(5)/(273*3600);
u = qv/As;
sumf = 0;
for i = 1:4
    sumf = sumf+f(i);
end
for i = 1:4
    x(i) = f(i)/sumf;
end
cp = cpmix(f(5),x);									%计算反应混合物热容
cp = cp*273/(22.4*f(5));
rheat = heatr(f(5));									%计算反应热效应
k = 3.5e9*exp(-50900/(8.314*f(5)))/3600;
ra = k*f(1)*f(2)^0.5;
yp(1) = -ra/u;
yp(2) = -ra/u;
yp(3) = ra/u;
yp(4) = ra/u;
yp(5) = -rheat*ra/cp/u;
yp  =  yp';

function cp = cpmix(T,x)
%计算反应混合物热容
global cpA cpB cpC cpD dcpA dcpB dcpC dcpD
cp  =  sum((cpA+cpB*T+cpC*T^2+cpD*T^3).*x);

function dheat = heatr(T)
%计算反应热效应
global cpA cpB cpC cpD dcpA dcpB dcpC dcpD
hf = [5.003e4 0 8.298e4 -7.486e4];
hr298 = hf(3)+hf(4)-hf(1)-hf(2);
dhr = quad(@deltah,298,T);
dheat = hr298+dhr;

function y = deltah(T)
%计算反应物和产物热容差
global cpA cpB cpC cpD dcpA dcpB dcpC dcpD
y = dcpA+dcpB*T+dcpC*T.^2+dcpD*T.^3;