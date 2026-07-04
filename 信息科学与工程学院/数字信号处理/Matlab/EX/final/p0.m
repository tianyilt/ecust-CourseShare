close all;
clear;

addpath("D:\Documents\学习_大学\大三上\数字信号处理\Matlab\EX\final")
addpath("D:\Documents\学习_大学\大三上\数字信号处理\Matlab\EX\final\scale_sample")

% step0: 设定参数
Frame_Num = 256; % 帧长
F0 = 0.1;

% step1: 读入音频
[x, Fs] = audioread('M1_i1.wav');
music = x(:, 1) ./ max(abs(x(:, 1))); % 取左声道, 归一化

% step2: 帧峰检测法, 获得包络
[envelope, peaks, start_index] = get_start_index(x, Fs, Frame_Num);
% start_index = start_i * Frame_Num;

% figure;
% plot(x);
% hold on;
% for i = 1:length(start_index)
%     plot(start_index(i) * Frame_Num, peaks(i), 'ro');
%     % 在旁边标号
%     text(start_index(i) * Frame_Num, peaks(i), num2str(i));
% end
% hold on;
% plot(1:Frame_Num:Frame_Num*length(envelope), envelope, 'g');
% hold off;

% step3: 划分音符得到每个音符的幅度矩阵
Amp_MS = get_Amp_MS(x, Fs, Frame_Num, F0);
KeyEnergy_Ms = Amp_to_Key(Amp_MS, F0);

figure;
for i = 1:length(start_index)
    subplot(3, 5, i);
    Amp_temp = Amp_MS(:, i);
    Amp_temp = Amp_temp / max(Amp_temp);
    plot(Amp_temp);
    axis([0 10000 0 1]);
    title("音符" + i + "的频谱图");
end

% 用subplot画在一个图中, 用axis调整观察范围
figure;
for i = 1:length(start_index)
    subplot(3, 5, i);
    KeyEnergy_i = KeyEnergy_Ms(:, i);
    key_Index = 1:88;
    plot(key_Index, KeyEnergy_i);
    axis([1 88 0 1]);
    title("第" + i + "个音符琴键能量");
end

[Key_Rec, Key_code, Key_index, Key_count] = get_note_key(start_index, KeyEnergy_Ms);

figure;
for i = 1:Key_count
    subplot(3, 5, i);
    Key_i = Key_Rec(:, i);
    stem(Key_i);
    axis([0 88 0 1]);
    title("第" + i + "个音识别结果");
end



% % 瀑布流图
% figure;
% imagesc(1:length(start_index), 21:108, KeyEnergy_Ms);
% axis xy; axis([0 length(start_index) 21 108]);

% real_beat_t = get_rhythm(start_index, Frame_Num, Fs, 69, 1);
% disp(real_beat_t);


% plot_spec_fixedFrame(music, Fs, Frame_Num*20, 2000);