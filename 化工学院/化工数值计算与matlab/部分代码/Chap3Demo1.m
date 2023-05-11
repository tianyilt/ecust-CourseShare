function Chap3Demo1
a=1;
b=2;
epsilon=1e-6;
f=@(x) x^2+3.2*x-9;
step = 0.1;
k=1;
x = a + step;
while abs(f(x))>epsilon
    if f(a)*f(x)>0
       a = a + step;
       x = a + step;
    elseif f(a)*f(x)<0
       step = step/10;
       x = a + step;
    end
   k=k+1;
end
disp('The solution with Scanning Method is')
disp(x)
disp('The number of calculation is:')
disp(k)
