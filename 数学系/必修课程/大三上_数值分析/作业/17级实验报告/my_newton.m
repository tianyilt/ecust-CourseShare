function N = my_newton(x,y)
%NEWTON 此处显示有关此函数的摘要
%   此处显示详细说明
n=length(x);
d=zeros(n,n);
d(:,1)=y';
for j=2:n
    d(j:n,j)=(d(j:n,j-1)-d(j-1:n-1,j-1))./(x(j:n)-x(1:n-j+1))';
end
N=[zeros(1,n-1) y(1)];
for i=1:(n-1)
    N=N+d(i+1,i+1)*[zeros(1,n-i-1) poly(x(1:i))];
end

