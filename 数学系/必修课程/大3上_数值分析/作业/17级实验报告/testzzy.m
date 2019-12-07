n=10;
%n=20;
x=linspace(-1,1,100001);
y=1./(1+25.*x.*x);
c=(-1)*(50.*x)./((25.*x.*x)+1)./((25.*x.*x)+1);
b=[c(1),c(end)];
figure,subplot(1,3,1),plot(x,y,'g'),grid off,axis normal,title('f(x)');
x=linspace(-1,1,n+1);
y=1./(1+25.*x.*x);
s=cubic_spline_interpolation(x,y,b);
hold on;
for i=1:n
   p=polyval(s(i,:),linspace(x(i),x(i+1),10));
   subplot(1,3,2),plot(linspace(x(i),x(i+1),10),p,'b'),grid off,axis normal,title('三次插值');
   hold on;
end
hold on;
N=my_newton(x,y);
x=linspace(-1,1,1001);
q=polyval(N,x);
hold on,subplot(1,3,3),plot(x,q,'r'),grid off,axis normal,title('多项式插值');
