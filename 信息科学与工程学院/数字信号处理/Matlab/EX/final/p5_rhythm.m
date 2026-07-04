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

threshold = [59 108] - 20;
% step4: 识别音符对应的键号
[Key_Rec, Key_code, Key_index, Key_count] = get_note_key(start_index, KeyEnergy_Ms, threshold);

% 瀑布图, 修正后
% figure;
% imagesc(1:length(start_index), 21:108, Key_Rec);
% axis xy; axis([0.5 length(start_index)+0.5 21 108]);

% disp(Key_code+20);

% step5: 判断节奏
tempo = 69;
ideal_beat_t = [1 1 1 1 1 1 2 1 1 1 1 1 1 2 1 1 1 1 1 1 2 1 1 1 1 1 1 2 1 1 1 1 1 1 2 1 1 1 1 1 1];
real_beat_t = zeros(1, length(start_index) - 1);

c_fast = 0;
c_slow = 0;
c_perfect = 0;
c_good = 0;
c_miss = 0;
avg_error = 0;

for i = 1:length(start_index) - 1
    real_beat_t(i) = (start_index(i + 1) - start_index(i)) * Frame_Num / Fs / 60 * tempo;
    error = abs(real_beat_t(i) - ideal_beat_t(i));
    avg_error = avg_error + error;

    if real_beat_t(i) > ideal_beat_t(i)
        c_slow = c_slow + 1;
    else
        c_fast = c_fast + 1;
    end

    if error < 0.1
        c_perfect = c_perfect + 1;
    elseif error < 0.2
        c_good = c_good + 1;
    else
        c_miss = c_miss + 1;
    end

end

avg_error = avg_error / (length(start_index) - 1);

figure;
subplot(3, 1, 1);
plot(1:length(start_index) - 1, real_beat_t, 'rx');
hold on;
plot(1:length(start_index) - 1, ideal_beat_t, 'bo');
hold off;
axis([1 length(start_index) - 1 0 2.2]);

subplot(3, 1, 2);
plot(1:length(start_index) - 1, ideal_beat_t - real_beat_t, 'bx-');
axis([1 length(start_index) - 1 -1 1]);

subplot(3, 2, 5);
msg = "节奏准确率: " + ((1 - avg_error) * 100) + "%";
text(0.5, 0.5, msg, 'FontSize', 20, 'HorizontalAlignment', 'center');
axis off;

subplot(6, 4, 19);
msg = newline + "Fast: " + c_fast;
text(0.5, 0.5, msg, 'FontSize', 20, 'HorizontalAlignment', 'center');
axis off;

subplot(6, 4, 20);
msg = newline + "Slow: " + c_slow;
text(0.5, 0.5, msg, 'FontSize', 20, 'HorizontalAlignment', 'center');
axis off;

subplot(6, 4, 23);
msg = newline + "Perfect: " + c_perfect;
text(0.5, 0.5, msg, 'FontSize', 20, 'HorizontalAlignment', 'center');
axis off;

subplot(6, 4, 24);
msg = newline + "Good: " + c_good;
text(0.5, 0.5, msg, 'FontSize', 20, 'HorizontalAlignment', 'center');
axis off;

real_beat_t = get_rhythm(start_index, Frame_Num, Fs, 69, 1);
disp(real_beat_t);
