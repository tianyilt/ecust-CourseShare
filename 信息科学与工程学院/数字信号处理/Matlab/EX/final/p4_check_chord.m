close all;
clear;

addpath("D:\Documents\学习_大学\大三上\数字信号处理\Matlab\EX\final")
addpath("D:\Documents\学习_大学\大三上\数字信号处理\Matlab\EX\final\scale_sample")
addpath("D:\Documents\学习_大学\大三上\数字信号处理\Matlab\EX\final\music")

% step0: 设定参数
Frame_Num = 128; % 帧长
F0 = 0.1;

% step1: 读入音频
[x, Fs] = audioread('star_69.wav');
music = x(:, 1) ./ max(abs(x(:, 1))); % 取左声道, 归一化

% step2: 帧峰检测法, 获得包络
[envelope, peaks, start_index] = get_start_index(x, Fs, Frame_Num);
% start_index = start_i * Frame_Num;

% 画出音频和包络
figure;
plot(x);
hold on;
for i = 1:length(start_index)
    plot(start_index(i) * Frame_Num, peaks(i), 'ro');
    % 在旁边标号
    text(start_index(i) * Frame_Num, peaks(i), num2str(i));
end
hold on;
plot(1:Frame_Num:Frame_Num*length(envelope), envelope, 'g');
hold off;

% step3: 划分音符得到每个音符的幅度矩阵
Amp_MS = get_Amp_MS(x, Fs, Frame_Num, F0);
KeyEnergy_Ms = Amp_to_Key(Amp_MS, F0);


sample_index = 5;

test_N = round((start_index(sample_index + 1) - start_index(sample_index)+1)*Frame_Num*2/3);
start_i = start_index(sample_index) * Frame_Num;
test_x = start_i:start_i+test_N;
KeyEnergy_i = KeyEnergy_Ms(:, sample_index);
% 左侧补20个0
KeyEnergy_i = [zeros(20, 1); KeyEnergy_i];

figure;
subplot(4, 1, 1);
plot(test_x, x(test_x));
title("音符" + sample_index + "2/3个音程的波形");

test_fft = fft(x(test_x).*hamming(length(test_x)), Fs);
subplot(4, 1, 2);
stem(abs(test_fft)/max(abs(test_fft)));
title("哈明窗谱图")
axis([0 2000 0 1.2]);

subplot(2, 1, 2);
key_Index = 1:108;
plot(key_Index, KeyEnergy_i);
axis([40 90 0 1.2]);
title("对应琴键能量");

