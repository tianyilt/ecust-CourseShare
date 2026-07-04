rootPath = 'D:\Documents\学习_大学\大三上\数字信号处理\Matlab';
addpath(fullfile(rootPath, 'utils'));
addpath(fullfile(rootPath, 'assets'));

[x, fs] = audioread('test.wav');
% 失真效果器
% 参数
gain = 2.8;
threshold = 0.4;

y = max(min(gain * x, threshold), -threshold);
figure(1); plot(x); title('Original Signal'); grid on;
figure(2); plot(y); title('Distorted Signal'); grid on;

audiowrite(fullfile(rootPath, 'output', 'distorted.wav'), y, fs);
