function ZuiJiaPingFangPoly(f, lb, up)
%f表示输入式子如
syms x;
rou=1;
n=4;%正交基个数
%正交基φ
fai=cell(n,1);
fai{1}=1;
fai{2}=x;
A=zeros(n);%法方程左边的矩阵
b=sym(zeros(1,n)');%法方程右边列向量
for i=1:n
    b(i)=int(rou*f*fai{i},x,lb,up);
    for j=1:n
        A(i,j)=int(rou*fai{i}*fai{j},x,lb,up);
    end
end
disp("法方程左边的矩阵")
disp(A)
disp("法方程右边列向量")
disp(b)%输出结果会略写,请点击下面图标显示全部结果,比如b2是37/12,不点只会显示37/1
disp("多项式系数,分别是1和x的系数")
disp(A^(-1)*b)%第二问的解,分别是正交基从前往后的系数
disp("化简后的结果")
simplify(A^(-1)*b)
fprintf('显示小数\n')
vpa(A^(-1)*b)
end
