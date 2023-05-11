function Chap3Demo3
x(1)=1;
epsilon=1e-6;
f=@(x) x^2+3.2*x-9;
df=@(x) 2*x+3.2;
k=1;
x(2)=x(1)-f(x(1))/df(x(1));
while abs(x(k+1)-x(k))>epsilon
      x(k+2)=x(k+1)-f(x(k+1))/df(x(k+1));
      k=k+1;
end
disp('The solution Newton''s Method is')
disp(x(k))
disp('The number of calculation is:')
disp(k)
