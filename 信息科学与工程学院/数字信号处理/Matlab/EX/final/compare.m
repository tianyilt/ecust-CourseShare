% close all;
clear;

addpath("D:\Documents\学习_大学\大三上\数字信号处理\Matlab\EX\final")
addpath("D:\Documents\学习_大学\大三上\数字信号处理\Matlab\EX\final\scale_sample")

% step0: 设定参数
Frame_Num = 256; % 帧长
F0 = 0.1;

wavs = ["L1_i1.wav", "M1_i2.wav", "H1_i2.wav"];
T = length(wavs);

% 峰值检测
for t = 1:T
    % step1: 读入音频
    [x, Fs] = audioread(wavs(t));
    music = x(:, 1) ./ max(abs(x(:, 1))); % 取左声道, 归一化

    % step2: 帧峰检测法, 获得包络
    [envelope, peaks, start_index] = get_start_index(x, Fs, Frame_Num);
    % start_index = start_i * Frame_Num;

    figure(1);
    subplot(T, 1, t);
    plot(x);
    hold on;

    for i = 1:length(start_index)
        plot(start_index(i) * Frame_Num, peaks(i), 'ro');
        % 在旁边标号
        text(start_index(i) * Frame_Num, peaks(i), num2str(i));
    end

    hold on;
    plot(1:Frame_Num:Frame_Num * length(envelope), envelope, 'b');
    hold off;
    axis([0 length(x) -0.8 1.2]);
end

% 音符识别
for t = 1:length(wavs)
    % step1: 读入音频
    [x, Fs] = audioread(wavs(t));
    music = x(:, 1) ./ max(abs(x(:, 1))); % 取左声道, 归一化

    Amp_MS = get_Amp_MS(x, Fs, Frame_Num, F0);
    KeyEnergy_Ms = Amp_to_Key(Amp_MS, F0);

    % 用subplot画在一个图中, 用axis调整观察范围
    
    figure(t + 3);
    for i = 1:length(start_index)
        subplot(5, 3, i);
        KeyEnergy_i = KeyEnergy_Ms(:, i);
        key_Index = 1:88;
        plot(key_Index, KeyEnergy_i);
        hold on;
        axis([1 88 0 1]);
        title("第" + i + "个音符");

        [~, max_index] = max(KeyEnergy_i);
        % 在max_index 和 +12 +19处画线
        plot([max_index, max_index], [0, 1], 'r');
        hold on;
        plot([max_index + 12, max_index + 12], [0, 1], 'r');
        hold on;
        plot([max_index + 19, max_index + 19], [0, 1], 'r');
        hold off;

    end

    % 瀑布流图
    figure(2);
    subplot(T, 2, t * 2 - 1);
    imagesc(1:length(start_index), 21:108, KeyEnergy_Ms);
    axis xy; axis([0.5 (length(start_index) + 0.5) 21 108]);
    title(wavs(t)+ " 瀑布图");

    % 识别音符对应的键号
    [Key_Rec, Key_code, Key_index, Key_count] = get_note_key(start_index, KeyEnergy_Ms);

    % 直观展示识别结果
    figure(2);
    subplot(T, 2, t * 2);
    imagesc(1:length(start_index), 21:108, Key_Rec);
    axis xy; axis([0.5 (length(start_index) + 0.5) 21 108]);
    title(wavs(t)+ " 识别结果");
end
