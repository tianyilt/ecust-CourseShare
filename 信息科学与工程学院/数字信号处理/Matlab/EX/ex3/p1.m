fp1 = 0.3;      fp2 = 0.7;
fs1 = 0.2;      fs2 = 0.8;
rp = 0.5; rs = 50;
w1 = [fp1 fp2];
w2 = [fs1 fs2];

% 巴特沃斯

[N, wn] = buttord(w1, w2, rp, rs);
[b, a] = butter(N, wn);
[H, w] = freqz(b, a);

figure;
subplot(2,2,1);
plot(w * fs / (2 * pi), abs(H)); grid;
title("巴特沃斯");
axis([0 50 0 1.2]);

% 切比雪夫I型

[N, wn] = cheb1ord(w1, w2, rp, rs);
[b, a] = cheby1(N, rp, wn);
[H, w] = freqz(b, a);

subplot(2,2,2);
plot(w * fs / (2 * pi), abs(H)); grid;
title("切比雪夫I型");

axis([0 50 0 1.2]);
% 切比雪夫II型

[N, wn] = cheb2ord(w1, w2, rp, rs);
[b, a] = cheby2(N, rs, wn);
[H, w] = freqz(b, a);

subplot(2,2,3);
plot(w * fs / (2 * pi), abs(H)); grid;
title("切比雪夫II型");

axis([0 50 0 1.2]);
% 椭圆型

[N, wn] = ellipord(w1, w2, rp, rs);
[b, a] = ellip(N, rp, rs, wn);
[H, w] = freqz(b, a);

subplot(2,2,4);
plot(w * fs / (2 * pi), abs(H)); grid;
title("椭圆型");
axis([0 50 0 1.2]);