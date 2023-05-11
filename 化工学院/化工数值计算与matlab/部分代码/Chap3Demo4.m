function Chap3Demo4
x(1)=1;
x(2)=2;
epsilon=1e-6;
f=@(x) x^2+3.2*x-9;
k=1;
while abs(x(k+1)-x(k))>epsilon
    s=(f(x(k+1))-f(x(k)))/(x(k+1)-x(k));  
    x(k+2)=x(k+1)-f(x(k+1))/s;
    k=k+1;
end
disp('The solution with Secant Method is')
disp(x(k))
disp('The number of calculation is:')
disp(k)
