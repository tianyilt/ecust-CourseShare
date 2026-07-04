close all;
clear;

% 读取音频文件
addpath("D:\Documents\学习_大学\大三上\数字信号处理\Matlab\EX\final\scale_sample")

Frame_Num = 128; % 帧长
[audio, fs] = audioread('M1_i1.wav');
music = audio(:, 1) ./ max(abs(audio(:, 1))); % 取左声道, 归一化
[envelope, peaks, start_i] = get_start_index(audio, fs, Frame_Num);
start_index = start_i * Frame_Num;

% 绘制原波形
figure(1);
plot(music, 'b');
hold on;

% 绘制包络
plot(0:Frame_Num:Frame_Num * length(envelope) - 1, envelope, 'r');
hold on;

% 绘制顶点
plot(start_index, peaks, 'ko', 'MarkerFaceColor', 'k');
hold off;

test_note_i = start_index(1); % 测试第一个音符
test_note_len = (start_index(2) - start_index(1)); % 测试音符长度
test_N = [400 4000 test_note_len * 2/3 test_note_len];

figure(2);
len = length(test_N);

for i = 1:len
    N = test_N(i);
    index = test_note_i:test_note_i + N - 1;
    test_music = music(index);
    subplot(3, len, i);
    plot(test_music);
    title("音符后实际长度: "+N + "个点");

    % 矩形窗
    test_music_fft = fft(test_music, 44100);
    subplot(3, len, i + len);
    stem(abs(test_music_fft) / max(abs(test_music_fft)));
    title("矩形窗频谱");

    % 汉明窗
    test_music_fft = fft(test_music .* hamming(N), 44100);
    subplot(3, len, i + 2 * len);
    stem(abs(test_music_fft) / max(abs(test_music_fft)));
    title("汉明窗频谱");
end

plot_spec_fixedFrame(music, fs, 400, 2000);
title("固定帧长为400的谱图");
plot_spec_fixedFrame(music, fs, 4000, 2000);
title("固定帧长为4000的谱图");
plot_spec_noteLen(music, fs, start_index, 2000);
title("音符帧长的谱图");

% 将每个音程的长度做谱分析, 画出谱图, 并判断琴键
Amp_MS = []; F0 = 0.1; %观察的谱间隔暂定为0.1Hz
N = fs / F0; %FFT点数
% 1. 取音程段
for i = 1:length(start_index)

    if i < length(start_index)
        %若不是最后一段则取当前段与后一段的前2/3的信号
        X_temp = music(start_index(i):floor(start_index(i) + (start_index(i + 1) - start_index(i)) * 2/3));
    else
        %若是最后一段，则按照前一段的长度取（因为最后一段后面没有下一段的标记了）
        X_temp = music(start_index(i):floor(start_index(i) + (start_index(i) - start_index(i - 1)) * 2/3));
    end

    X_temp = X_temp .* hanning(length(X_temp)); % 2. 乘以窗函数（暂定汉宁窗）
    Amp_temp = fft(X_temp, N); % 3. 做FFT（N比X_temp的长度要长，相当于添零了）
    Amp_MS = [Amp_MS abs(Amp_temp)]; %保存本段音程的谱分析结果
end

% 用subplot画在一个图中, 用axis调整观察范围
figure;
for i = 1:length(start_index)
    subplot(3, 5, i);
    Amp_temp = Amp_MS(:, i);
    Amp_temp = Amp_temp / max(Amp_temp);
    f = (0:N - 1) * (fs / N);
    plot(f, Amp_temp);
    axis([0 2000 0 1]);
    title("音符" + i + "的频谱图");
end

