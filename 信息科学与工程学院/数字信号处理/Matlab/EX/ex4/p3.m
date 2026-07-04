close all;
clear;

addpath('D:\Documents\学习_大学\大三上\数字信号处理\Matlab\EX\dsp');

wp1 = 0.3; wp2 = 0.7; ap = 0.5;
ws1 = 0.4; ws2 = 0.6; as = 50;

% 等波纹最佳逼近

f = [wp1, ws1, ws2, wp2];
m = [1, 0, 1];

dat1 = (10 ^ (ap / 20) - 1) / (10 ^ (ap / 20) + 1);
dat2 = 10 ^ (-as / 20);
rip = [dat1, dat2, dat1];

[M, fo, mo, wo] = remezord(f, m, rip);
hn2 = remez(M, fo, mo, wo);

% 打印
figure(1);
[H, w] = freqz(hn2, 1, 512);
% subplot(1, 2, 1);
plot(w / pi, 20 * log10(abs(H)));
title("等波纹最佳逼近设计带阻滤波器");
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
