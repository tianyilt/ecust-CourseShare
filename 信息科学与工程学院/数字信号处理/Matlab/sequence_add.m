addpath('D:\Documents\学习_大学\大三上\数字信号处理\Matlab\utils');

n1 = [-2:3];    x1 = [1 2 3 4 5 6];
n2 = [1:5];     x2 = [5 4 3 2 1];
[y, n] = seqmult(x1, n1, x2, n2);

subplot(311);   stem(n1, x1, 'linewidth', 2);
axis([min(n) max(n) 0 max(y)]); grid on;

subplot(312);   stem(n2, x2, 'linewidth', 2);
axis([min(n) max(n) 0 max(y)]); grid on;

subplot(313);   stem(n, y, 'linewidth', 2);
axis([min(n) max(n) 0 max(y)]); grid on;