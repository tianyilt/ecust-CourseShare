x_4 = [3, 2, 1, 2];
X_4 = fft(x_4, 4);
x_5 = [3, 2, 1, 2, 0];
X_5 = fft(x_5, 5);
figure;
subplot(2, 2, 1); stem(0:3, abs(X_4), 'filled'); title('4 点 DFT 频谱');
xlabel('k');
ylabel('幅度');
grid on;

subplot(2, 2, 2); stem(0:3, angle(X_4), 'filled'); title('4 点 DFT 相位');
xlabel('k');
ylabel('相位');
grid on;

subplot(2, 2, 3); stem(0:4, abs(X_5), 'filled'); title('5 点 DFT 频谱');
xlabel('k');
ylabel('幅度');
grid on;

subplot(2, 2, 4); stem(0:4, angle(X_5), 'filled'); title('5 点 DFT 相位');
xlabel('k');
ylabel('相位');
grid on;