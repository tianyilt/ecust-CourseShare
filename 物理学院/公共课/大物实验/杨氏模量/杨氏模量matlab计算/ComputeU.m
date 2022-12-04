function [U] = ComputeU(S,n,t0683,delta_yi)
%COMPUTEU 此处显示有关此函数的摘要S标准差 n次数 t0683 delta_yi仪器误差 得到不确定度U
%   此处显示详细说明
U=((t0683(n-1)*S/sqrt(n))^2+(0.618*delta_yi)^2)^0.5;

end

