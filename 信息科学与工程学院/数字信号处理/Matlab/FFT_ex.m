clc;
clear;
close all;

xn = [1,4,2,8,5,7];
N = length(xn);
Xk = fft(xn, N);

figure;
subplot(4,2,1); stem(0:N-1, real(Xk), 'filled'); title('原序列实部'); xlabel('k'); ylabel('Re(X[k])');
subplot(4,2,2); stem(0:N-1, imag(Xk), 'filled'); title('原序列虚部'); xlabel('k'); ylabel('Im(X[k])');

% 交换Xk的实部和虚部
Xk = imag(Xk) + 1j * real(Xk);
subplot(4,2,3); stem(0:N-1, real(Xk), 'filled'); title('交换实部虚部后的实部'); xlabel('k'); ylabel('Re(X[k])');
subplot(4,2,4); stem(0:N-1, imag(Xk), 'filled'); title('交换实部虚部后的虚部'); xlabel('k'); ylabel('Im(X[k])');

yn = fft(Xk, N);
yn = imag(yn) + 1j * real(yn);
yn = yn / N;

subplot(4,2,5); stem(0:N-1, real(yn), 'filled'); title('yn的实部'); xlabel('n'); ylabel('Re(y[n])');
subplot(4,2,6); stem(0:N-1, imag(yn), 'filled'); title('yn的虚部'); xlabel('n'); ylabel('Im(y[n])');

subplot(4,2,7); stem(0:N-1, real(xn), 'filled'); title('xn的实部'); xlabel('n'); ylabel('Re(x[n])');
subplot(4,2,8); stem(0:N-1, imag(xn), 'filled'); title('xn的虚部'); xlabel('n'); ylabel('Im(x[n])'); 