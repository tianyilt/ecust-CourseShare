fp = 40; fst = 30; fs = 100;
rp = 0.5; rs = 40;
wp = 2 * fp / fs; ws = 2 * fst / fs;
[N, wn] = buttord(wp, ws, rp, rs);
[b, a] = butter(N, wn, 'high');
[H, w] = freqz(b, a);
plot(w * fs / (2 * pi), abs(H)); grid;
