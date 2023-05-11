function Chap3Demo2
a=1;
b=2;
epsilon=1e-6;
f=@(x) x^2+3.2*x-9;
k=0;
while abs(b-a)/2>epsilon
    x=(b+a)/2;
    if f(x)==0
        a=x;b=x;
    elseif f(a)*f(x)>0
        a=x;
    elseif f(a)*f(x)<0
        b=x;
    end
   k=k+1;
end
x = (b+a)/2;
disp('The solution with Dichotomy is')
disp(x)
disp('The number of calculation is:')
disp(k)
