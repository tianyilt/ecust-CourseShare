clear;
close all;

Hs = tf(1, [1 1]);
figure;
subplot(1, 2, 1);
bode(Hs); grid;

T = 0.02;
b = T;
a = [1 -exp(-T)];
H = tf(b, a, T);
subplot(1, 2, 2);
bode(H); grid;

fs = 1 / T;
% 5秒2和5秒0
xn = [2 * ones(1, 5 * fs), zeros(1, 5 * fs)];
figure;
subplot(2, 2, 1);
stem(xn); grid;
axis([-1 * fs 12 * fs -1 3]); grid;
title("采样频率为"+fs + "Hz的xn信号");

% 画出系统的幅频响应
subplot(2, 2, 2);
bode(H); grid;
title("系统的幅频响应");

% 画出系统输出yn
yn = filter(b, a, xn);
subplot(2, 1, 2);
stem(yn); grid;
title("系统输出yn");
