function Cha3demo8
opt=optimset('TolFun',1e-10);
x0=[1 1];
[x1,err1,flag1]=fsolve(@Eq8,x0)
[x2,err2,flag2]=fsolve(@Eq8,x0,opt)
function f=Eq8(x)
f1=10*x(1)+3*x(2)^2-3;
f2=x(1)^2-exp(x(2))-2;
f=[f1;f2];
