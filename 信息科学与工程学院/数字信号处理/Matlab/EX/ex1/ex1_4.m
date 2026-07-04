rootPath = 'D:\Documents\学习_大学\大三上\数字信号处理\Matlab\EX';
addpath(fullfile(rootPath, 'wav'));
addpath(fullfile(rootPath, 'ex1'));

clc;
clear;
close all;

[x1, fs1] = audioread('canon.wav');

y1_2 = x1(1:2:end);
y1_4 = x1(1:4:end);
y1_8 = x1(1:8:end);

figure;
subplot(4,1,1);
plot(x1);title('Original signal');
subplot(4,1,2);
plot(y1_2);title('Downsampled signal (1/2)');
subplot(4,1,3);
plot(y1_4);title('Downsampled signal (1/4)');
subplot(4,1,4);
plot(y1_8);title('Downsampled signal (1/8)');

audiowrite('D:\Documents\学习_大学\大三上\数字信号处理\Matlab\EX\ex1\ex1_4_canon_2.wav', y1_2, floor(fs1/2));
audiowrite('D:\Documents\学习_大学\大三上\数字信号处理\Matlab\EX\ex1\ex1_4_canon_4.wav', y1_4, floor(fs1/4));
audiowrite('D:\Documents\学习_大学\大三上\数字信号处理\Matlab\EX\ex1\ex1_4_canon_8.wav', y1_8, floor(fs1/8));


[x2, fs2] = audioread('dsp.wav');

y2_2 = x2(1:2:end);
y2_4 = x2(1:4:end);
y2_8 = x2(1:8:end);

figure;
subplot(4,1,1);
plot(x2);title('Original signal');
subplot(4,1,2);
plot(y2_2);title('Downsampled signal (1/2)');
subplot(4,1,3);
plot(y2_4);title('Downsampled signal (1/4)');
subplot(4,1,4);
plot(y2_8);title('Downsampled signal (1/8)');

audiowrite('D:\Documents\学习_大学\大三上\数字信号处理\Matlab\EX\ex1\ex1_4_dsp_2.wav', y2_2, floor(fs2/2));
audiowrite('D:\Documents\学习_大学\大三上\数字信号处理\Matlab\EX\ex1\ex1_4_dsp_4.wav', y2_4, floor(fs2/4));
audiowrite('D:\Documents\学习_大学\大三上\数字信号处理\Matlab\EX\ex1\ex1_4_dsp_8.wav', y2_8, floor(fs2/8));
