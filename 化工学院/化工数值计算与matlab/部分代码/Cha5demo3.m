function Cha5demo3
t=[0 20 40  60 120  180 300];
CA=[10  8   6   5   3   2   1];
plot(t,CA,'r*'),hold on
pp=csaps(t,CA); 
fnplt(pp)
title('Concentration vs time')
dp=fnder(pp); 
dCAdt=-fnval(dp,t); 
y=log(dCAdt);x=log(CA);
p=polyfit(x,y,1);
beta0=[exp(p(2)),p(1)];
beta=nlinfit(CA,dCAdt,@rate,beta0)
figure
plot(t,dCAdt,'o',t,rate(beta,CA),'*',t,rate(beta0,CA),'p')
title('Reation rate vs time')
function r=rate(beta,C)
r=beta(1)*C.^beta(2);
