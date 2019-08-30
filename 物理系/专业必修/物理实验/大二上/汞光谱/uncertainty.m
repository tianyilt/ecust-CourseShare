function [equal_x,U] = uncertainty(x,delta_yi)
%x,待求实验数据，delta_yi仪器误差
P = 0.683;
tp = [1.84,1.32,1.2,1.14,1.11,1.09,1.08,1.07,1.06];
N = length(x);
equal_x = mean(x);
S_mean_x = std(x)/(N-1);
%A类分量
if N>9
    uncertainty_A = S_mean_x;
else
    uncertainty_A = S_mean_x*tp(N-1);
end
%B类分量
uncertainty_B = P*delta_yi;
U = sqrt(uncertainty_A.^2+uncertainty_B.^2);
fprintf('x=%f +- %f\n',equal_x,U)
