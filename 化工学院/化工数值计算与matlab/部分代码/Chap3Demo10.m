function Chap3Demo10
opt=optimset('TolFun',1e-10);
x0=[1 1];
[x1,err1,flag1]=fsolve(@Eqs10,x0)
[x2,err2,flag2]=fsolve(@Eqs10,x0,opt)

function f=Eqs10(x)
f1=10*x(1)+3*x(2)^2-3;
f2=x(1)^2-exp(x(2))-2;
f=[f1;f2];
