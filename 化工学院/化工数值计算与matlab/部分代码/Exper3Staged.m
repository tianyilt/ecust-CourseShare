function Exper3Staged
x0=zeros(1,20);
opt=optimset('MaxFunEvals',1e4,'MaxIter',1e3);
[x,fval,exit]=fsolve(@Staged,x0,opt);
plot(1:10,x(1:10),'o',1:10,x(11:20),'s')
legend('Raffinate','Extract')
ylabel('Anilin flow rate [kmol/h]')
xlabel('Stage number')
function y=Staged(x)
y=zeros(20,1);
LinA=5;LinW=100;VinT=10;
L=[LinA,x(1:10)];
V=[x(11:20),0];
FV=ones(10,1)*VinT;FV(7)=FV(7)+13;
F=zeros(10,1);F(7)=0.003;
for i=2:11
   y(i-1)=L(i-1)+V(i)+F(i-1)-L(i)-V(i-1);
   Xi=L(i)/(L(i)+LinW);
   Yi=V(i-1)/(FV(i-1)+V(i-1)+VinT+F(i-1));
   y(i-1+10)=Yi-Xi*(9+20*Xi);
end

