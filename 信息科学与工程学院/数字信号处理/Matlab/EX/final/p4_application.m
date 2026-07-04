close all;
clear;

addpath("D:\Documents\学习_大学\大三上\数字信号处理\Matlab\EX\final")
addpath("D:\Documents\学习_大学\大三上\数字信号处理\Matlab\EX\final\scale_sample")
addpath("D:\Documents\学习_大学\大三上\数字信号处理\Matlab\EX\final\music")

% step0: 设定参数
Frame_Num = 256; % 帧长
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

% 画出每个音符的琴键能量矩阵
figure;
for i = 1:length(start_index)
    subplot(6, 8, i);
    KeyEnergy_i = KeyEnergy_Ms(:, i);
    key_Index = 1:88;
    plot(key_Index, KeyEnergy_i);
    axis([1 88 0 1]);
    title("第" + i + "个音符");
end

% 瀑布流图(根据音符划分)
figure;
imagesc(1:length(start_index), 21:108, KeyEnergy_Ms);
axis xy; axis([0 length(start_index) 21 108]);

threshold = 59-20;
% step4: 识别音符对应的键号
[Key_Rec, Key_code, Key_index, Key_count] = get_note_key(start_index, KeyEnergy_Ms, threshold);

% 瀑布图, 修正后
figure;
imagesc(1:length(start_index), 21:108, Key_Rec);
axis xy; axis([0.5 length(start_index)+0.5 21 108]);

disp(Key_code+20);