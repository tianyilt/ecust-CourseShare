function [y,mean_y] = idm(x)
%逐差法，interative differential method，将
%x一分为二，前半部分与后半部分逐差，
%取绝对值后平均。
N = length(x);
x = sort(x);
% x_back = x(N/2+1:end);
% x_for = x(1:N/2);
% x_mean = mean(abs(x_back-x_for));
for i = 1:N-1
    y(i) = x(i+1)-x(i);
end
mean_y = mean(y);