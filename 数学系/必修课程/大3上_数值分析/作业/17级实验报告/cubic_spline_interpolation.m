function s = cubic_spline_interpolation( x,y,b )
n=length(x)-1;
%========================计算一阶均差==============================
difference_coeff=[];%存一阶均差
for i=1:1:n
    difference_coeff=[difference_coeff (y(i)-y(i+1))/(x(i)-x(i+1))];
end
%========================计算h值==================================
hs=[];%存放h
for i=1:1:n
    hs=[hs x(i+1)-x(i)];
end
%========================计算λ值=================================
lambdas=[1];%这里的λ1是书上的λ0
for i=2:1:n
    lambdas=[lambdas hs(i)/(hs(i-1)+hs(i))];
end
%========================计算μ值=================================
mus=[];%存μ
for i=2:1:n
    mus=[mus hs(i-1)/(hs(i-1)+hs(i))];
end
mus=[mus 1];%μn 是1
%========================计算d值=================================
d=[(6/hs(1))*(difference_coeff(1)-b(1))];%用来存放参数d,d0从边界条件得出
for i=2:1:n
    d=[d 6*(difference_coeff(i)-difference_coeff(i-1))/(hs(i)+hs(i-1))];
end
d=[d 6*(b(2)-difference_coeff(n))/hs(n)];%dn从边界条件得出
%========================计算系数矩阵=============================
twos=2*ones(1,n+1);
tmp_0=diag(twos,0);
tmp_1=diag(lambdas,1);
tmp_2=diag(mus,-1);
coeff_matrix=tmp_0+tmp_1+tmp_2;
Ms=inv(coeff_matrix)*d';%得到M值,Ms(n+1,1)
%========================计算出最后的s值==========================
s=[];%用于最后的输出
syms x_loop;
for i=1:1:n
    tmp_func=Ms(i)*(x(i+1)-x_loop)^3/(6*hs(i))+Ms(i+1)*(x_loop-x(i))^3/(6*hs(i))+(y(i)-(Ms(i)*hs(i)^2)/6)*(x(i+1)-x_loop)/hs(i)+(y(i+1)-(1/6)*Ms(i+1)*hs(i)^2)*(x_loop-x(i))/hs(i);
    poly_coeff=sym2poly(tmp_func);
    s=[s;poly_coeff];
end
