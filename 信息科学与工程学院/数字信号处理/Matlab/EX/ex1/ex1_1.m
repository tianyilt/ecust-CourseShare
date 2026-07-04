clc;
clear;
close all;

K = 0.9; n = 0:30;
c = -0.2 * pi * 1i;

xn = power((K * exp(c)), n);

subplot(4, 1, 1); stem(n, real(xn));
grid on; title('Real Part');
subplot(4, 1, 2); stem(n, imag(xn));
grid on; title('Imaginary Part');
subplot(4, 1, 3); stem(n, abs(xn));
grid on; title('Amplitude Part');
subplot(4, 1, 4); stem(n, atan2(imag(xn), real(xn)));
grid on; title('Phase Part');
