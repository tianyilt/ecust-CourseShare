close all;
clear;

addpath('D:\Documents\学习_大学\大三上\数字信号处理\Matlab\EX\dsp');

wp1 = 0.3; wp2 = 0.7; ap = 0.5;
ws1 = 0.4; ws2 = 0.6; as = 50;

% 频率采样法

% 1. 计算滤波器阶数
M = 61; alpha = (M - 1) / 2;
k = 0:M - 1; wk = 2 * pi * k / M;

token1 = 0.109;
token2 = 0.594;

Hrs = [ones(1, 10), token2, token1, zeros(1, 7), token1, token2, ones(1, 20), token2, token1, zeros(1, 7), token1, token2, ones(1, 9)];
Hdr = [1 1 0 0 1 1]; wdl = [0, wp1, ws1, ws2, wp2, 1];


k1 = 0:floor((M - 1) / 2);
k2 = floor((M - 1) / 2)+1:M - 1;
angH = [-alpha * 2 * pi * k1 / M, alpha * 2 * pi * (M - k2) / M];

size(k1)
size(k2)
size(angH)
size(Hrs)

H = Hrs .* exp(1j * angH);
h = real(ifft(H, M));
[Ha, w] = freqz(h, 1);
[Hr, ww, b, L] = Hr_Type1(h);

subplot(2, 2, 1); plot(wk(1:31) / pi, Hrs(1:31), 'o', wdl, Hdr);
axis([0, 1, -0.1, 1.1]); title("频率样本：M=20")
xlabel("频率(单位:Pi)"); ylabel("Hr(k)"); grid on;
subplot(2, 2, 2); stem(k, h); axis([-1, M, -0.24, 0.72]);
title("脉冲响应"); xlabel('n'); ylabel("h(n)"); grid on;
subplot(2, 2, 3); plot(ww / pi, Hr, wk(1:31) / pi, Hrs(1:31), 'o');
axis([0, 1, -0.2, 1.2]); title("振幅响应");
xlabel("频率(单位:Pi)"); ylabel("Hr(w)"); grid on;
subplot(2, 2, 4); plot(w / pi, 20 * log10(abs(Ha)));
axis([0, 1, -80, 10]); grid on;
title("幅度响应"); xlabel("频率(单位:Pi)"); ylabel("分贝");
