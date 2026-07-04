rootPath = 'D:\Documents\学习_大学\大三上\数字信号处理\Matlab\EX';
addpath(fullfile(rootPath, 'wav'));
addpath(fullfile(rootPath, 'ex1'));

clc;
clear;
close all;

[x, fs] = audioread('good.wav');

decay = 0.3; delay = 5000;
b = [1 zeros(1, delay-1) decay]; a=1;
y = filter(b, a, x);

figure;
subplot(2,1,1);
plot(x);title('Original signal');
subplot(2,1,2);
plot(y);title('Reverbed signal');
xlabel('Samples');
ylabel('Amplitude');

audiowrite('D:\Documents\学习_大学\大三上\数字信号处理\Matlab\EX\ex1\good_reverbed.wav', y, fs);