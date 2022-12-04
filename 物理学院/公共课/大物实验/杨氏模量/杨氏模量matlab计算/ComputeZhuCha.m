function [Y,X1,S] = ComputeZhuCha(X)
%COMPUTEZHUCHA 此处显示有关此函数的摘要
%   X1为平均值 S为标准差 X为输入的n*1的向量    
n=size(X);%n要为偶数
Y1=X(1:n/2);
Y2=X((n/2)+1:n);
Y=(Y2-Y1);
S=std(Y);
X1=mean(Y);


end

