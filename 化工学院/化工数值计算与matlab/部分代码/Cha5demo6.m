function Cha5demo6
clear all;
xi=[0.178 0.275 0.372 0.456 0.650 0.844];
yi=[0.243 0.382 0.518 0.616 0.795 0.931];
plot(xi,yi,'*'),hold on
sp=pchip(xi,yi);
xplot=linspace(xi(1),xi(end),100);
yplot=ppval(sp,xplot);
plot(xplot,yplot,'-');
N=quad(@func1,0.4,0.9,[],[],sp); 
N=ceil(N) 
function f=func1(x,sp)
y=ppval(sp,x);
f=1./(y-x-(0.9-y)./5);
