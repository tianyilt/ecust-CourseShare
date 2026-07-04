close all;
clear;

addpath("D:\Documents\学习_大学\大三上\数字信号处理\Matlab\EX\final\scale_sample")

% step0: 设定参数
Frame_Num = 64; % 帧长
F0 = 0.1;
fig_size = [5 8];

% step1: 读入音频
[x, Fs] = audioread('L1_i1.wav');

% step2: 帧峰检测法, 获得包络
[~, start_index] = get_start_index(x, Fs, Frame_Num, 0.3);

% step3: 划分音符得到每个音符的幅度矩阵
Amp_MS = get_Amp_MS(x, Fs, Frame_Num, 0.1);
KeyEnergy_Ms = Amp_to_Key(Amp_MS, F0);

% 用subplot画在一个图中, 用axis调整观察范围
figure;

for i = 1:length(start_index)
    subplot(fig_size(1), fig_size(2), i);
    KeyEnergy_i = KeyEnergy_Ms(:, i);
    key_Index = 1:88;
    plot(key_Index, KeyEnergy_i);
    axis([1 88 0 1]);
    title("第" + i + "个音符");
end

% 瀑布流图
figure;
imagesc(1:length(start_index), 21:108, KeyEnergy_Ms);
axis xy; axis([0 length(start_index) 21 108]);

% 根据琴键能量矩阵设计策略识别音符对应的键号
Key_Rec = zeros(1, 108);

for i = 1:length(start_index)
    KeyEnergy_i = KeyEnergy_Ms(:, i);
    % 找出能量最大的键号
    [~, max_index] = max(KeyEnergy_i);
    fprintf("第%d个音符, 最强音: %d\n", i, max_index);

    if (check_note_validation(KeyEnergy_i) == true)
        % 添加一个音符
        temp = zeros(1, 108);
        temp(max_index) = 1;
        Key_Rec = [Key_Rec; temp]; %#ok<AGROW>
    end
end

Key_Rec = Key_Rec(2:end, :);
Key_count = size(Key_Rec, 1);
% 转置Key_Rec, 使得每一列代表一个音符
Key_Rec = Key_Rec';


% 用subplot画在一个图中, 用stem画出
figure;
for i = 1:Key_count
    subplot(fig_size(1), fig_size(2), i);
    KeyEnergy_i = Key_Rec(:, i);
    key_Index = 1:108;
    stem(key_Index, KeyEnergy_i);
    title("第" + i + "个音符");
end

% 瀑布流图
figure;
imagesc(1:length(start_index), 21:108, Key_Rec);
axis xy; axis([0 length(start_index) 21 108]);
