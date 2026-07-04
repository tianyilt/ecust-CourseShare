close all;
clear;

n = 0:199;
a = [1 1 1];
b = [1 0.9 0.81];
[z, p, k] = tf2zp(a, b);
subplot(2, 2, 1); zplane(z, p); title('z and p');
[Fh, w] = freqz(b, a);
[Gd, w] = grpdelay(b, a);
subplot(2, 2, 2); plot(w / pi, abs(Fh)); title('|H(w)|');
subplot(2, 2, 3); plot(w / pi, angle(Fh)); title('ang|H(w)|');
subplot(2, 2, 4); plot(w / pi, Gd); title('grd|H(w)|')
