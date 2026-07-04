fp1 = 10; fs1 = 9; fp2 = 20;
fs2 = 21;
fs = 100; rp = 0.5; rs = 50;
w1 = [2 * fp1 / fs 2 * fp2 / fs];
w2 = [2 * fs1 / fs 2 * fs2 / fs];
[N, wn] = ellipord(w1, w2, rp, rs);
[b, a] = ellip(N, rp, rs, wn);
[H, w] = freqz(b, a);
plot(w * fs / (2 * pi), abs(H)); grid;
