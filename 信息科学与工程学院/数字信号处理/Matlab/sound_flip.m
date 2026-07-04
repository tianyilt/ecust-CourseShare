addpath('D:\Documents\学习_大学\大三上\数字信号处理\Matlab\utils');
addpath('D:\Documents\学习_大学\大三上\数字信号处理\Matlab\assets');

[x, fs] = audioread('test.wav');
y = flipud(x);
figure(1); plot(x); title('Original Signal'); grid on;
figure(2); plot(y); title('Flipped Signal'); grid on;

audiowrite('D:\Documents\学习_大学\大三上\数字信号处理\Matlab\assets\flipped.wav', y, fs);