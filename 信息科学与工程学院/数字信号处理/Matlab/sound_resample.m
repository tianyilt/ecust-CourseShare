rootPath = 'D:\Documents\学习_大学\大三上\数字信号处理\Matlab';
addpath(fullfile(rootPath, 'utils'));
addpath(fullfile(rootPath, 'assets'));

[x1, fs1] = audioread('test.wav');
[x2, fs2] = audioread('test2.wav');

minLen = min(length(x1), length(x2));
x1 = x1(1:minLen);
x2 = x2(1:minLen);

x = x1+x2;

figure(311); plot(x1); title('Original Signal 1'); grid on;
figure(312); plot(x2); title('Original Signal 2'); grid on;
figure(313); plot(x); title('Added Signal'); grid on;

audiowrite(fullfile(rootPath, 'output', 'added_1.wav'), x, fs1);
audiowrite(fullfile(rootPath, 'output', 'added_2.wav'), x, fs2);
