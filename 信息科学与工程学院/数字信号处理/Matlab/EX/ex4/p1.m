close all;
clear;

wp1 = 0.3; wp2 = 0.7; ap = 0.5;
ws1 = 0.4; ws2 = 0.6; as = 50;

% 设计FIR滤波器, 数字带阻滤波器
% 通过窗函数设计带阻滤波器

% 1. 计算滤波器阶数
delta_w = abs(min(wp1 - ws1, ws2 - wp2));
N = ceil(6.6 / delta_w);

figure(1);

% 2. 计算窗函数
h = fir1(N, [wp1, wp2], 'stop', blackman(N + 1));
[H, w] = freqz(h, 1, 512);
subplot(1, 2, 1);
plot(w / pi, 20 * log10(abs(H)));
title("Blackman窗函数设计带阻滤波器");
grid on;
hold on;
plot([wp1, wp1], [-100, 100], 'r--');
hold on;
plot([wp2, wp2], [-100, 100], 'r--');
hold on;
plot([ws1, ws1], [-100, 100], 'r-');
hold on;
plot([ws2, ws2], [-100, 100], 'r-');
hold off;
axis([0, 1, -100, 20]);

h = fir1(N, [wp1, wp2], 'stop', hamming(N + 1));
[H, w] = freqz(h, 1, 512);
subplot(1, 2, 2);
plot(w / pi, 20 * log10(abs(H)));
title("Hamming窗函数设计带阻滤波器");
grid on;
hold on;
plot([wp1, wp1], [-100, 100], 'r--');
hold on;
plot([wp2, wp2], [-100, 100], 'r--');
hold on;
plot([ws1, ws1], [-100, 100], 'r-');
hold on;
plot([ws2, ws2], [-100, 100], 'r-');
hold off;
axis([0, 1, -100, 20]);
