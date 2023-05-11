function Chap3Demo8
x0=[1 1 1];
x=fsolve(@fun,x0)

function y=fun(x)
y(1)=sin(x(1))+x(2)^2+log(x(3))-7;
y(2)=3*x(1)+2^x(2)-x(3)^3+1;
y(3)=x(1)+x(2)+x(3)-5;
