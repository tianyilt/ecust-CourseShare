fp = 2000; rp = 3;
fs = 1500; rs = 40;
Fs = 10000;
wp = 2 * fp / Fs;
ws = 2 * fs / Fs;

[N, wn] = buttord(wp, ws, rp, rs);
[b, a] = butter(N, wn, "high");
[H, w] = freqz(b, a);

figure;
subplot(2, 1, 1);
plot(w * Fs / (2 * pi), abs(H)); grid;
axis([0 5000 0 1.2]);
title("巴特沃斯高通滤波");

% 生成一个随机信号验证滤波效果

t = 0:1 / Fs:1;
x = sin(2 * pi * 1000 * t) + sin(2 * pi * 2000 * t) + 0.5 * randn(size(t));
y = filter(b, a, x);

X = fft(x);
Y = fft(y);
f = Fs * (0:length(X) - 1) / length(X);

subplot(4, 2, 5);
plot(t, x); grid;
title("原始信号");

subplot(4, 2, 6);
plot(f, abs(X)); grid;
title("原始信号频谱");

subplot(4, 2, 7);
plot(t, y); grid;
title("滤波后信号");

subplot(4, 2, 8);
plot(f, abs(Y)); grid;
title("滤波后信号频谱");
