clc;
clear;
close all;

xn = ones(1, 100) * 5;
hn = ones(1, 5) / 5;


N = length(xn) + length(hn) - 1;
Xk = fft(xn, N);
Hk = fft(hn, N);
Yk = Xk .* Hk;
yn = ifft(Yk);

yn_real = real(yn);
yn_imag = imag(yn);

figure;
subplot(2, 2, 1); stem(xn); title('x[n]'); xlabel('n'); ylabel('幅度');
subplot(2, 2, 2); stem(hn); title('h[n]'); xlabel('n'); ylabel('幅度');
subplot(2, 2, 3); stem(yn_real); title('y[n]实部'); xlabel('n'); ylabel('Re(y[n])');
subplot(2, 2, 4); stem(yn_imag); title('y[n]虚部'); xlabel('n'); ylabel('Im(y[n])');
