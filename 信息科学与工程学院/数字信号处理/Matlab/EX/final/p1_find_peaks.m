% 目标: 读入音频, 找出包络, 确定峰值位置
addpath("D:\Documents\学习_大学\大三上\数字信号处理\Matlab\EX\final\scale_sample")

% step1: 读入音频
[x, Fs] = audioread('M1_i1.wav');
music = x(:, 1) ./ max(abs(x(:, 1))); % 取左声道, 归一化
Frame_Num = 128; % 帧长

% 绘制原波形
figure;
xlabel('采样点');
ylabel('幅度');
plot(music, 'b');
hold on;

% step2: 帧峰检测法, 获得包络
envelope1 = [];

for i = 1:floor(length(music) / Frame_Num) - 1 % i是以Frame_Num个点分帧后的帧号
    temp = music((i - 1) * Frame_Num +1:i * Frame_Num); %每Frame_Num点是一个临时帧
    envelope1 = [envelope1 max(temp) - min(temp)]; %取出当前帧的峰峰值作为该帧的帧峰值
end

% 在同一个坐标轴上绘制包络
plot(1:Frame_Num:Frame_Num * length(envelope1), envelope1, 'r');
hold on;

% step3: 疯狂滤波平滑
envelope2 = envelope1;
envelope2 = medfilt1(envelope2, 5); % 中值滤波medfilt1
% envelope2 = smooth(envelope2, 5); % 平滑smooth
envelope2 = conv(envelope2, ones(1, 11) / 11, 'same'); % 11点平均滤波
envelope2 = conv(envelope2, ones(1, 21) / 21, 'same'); % 21点平均滤波
envelope2 = envelope2 ./ max(envelope2); % 归一化

% 在同一个坐标轴上绘制原波形和包络
plot(1:Frame_Num:Frame_Num * length(envelope2), envelope2, 'g');
hold off;

% step4: 寻找峰值
[peaks05, locs05] = findpeaks(envelope2, 'MinPeakHeight', 0.5); % 阈值0.5
[peaks04, locs04] = findpeaks(envelope2, 'MinPeakHeight', 0.4); % 阈值0.4
[peaks03, locs03] = findpeaks(envelope2, 'MinPeakHeight', 0.3); % 阈值0.3
[peaks02, locs02] = findpeaks(envelope2, 'MinPeakHeight', 0.2); % 阈值0.2

% 比较几种阈值下的峰值
figure;
subplot(2, 2, 1);
plot(1:Frame_Num:Frame_Num * length(envelope2), envelope2, 'b');
hold on;
plot(locs05 * Frame_Num, peaks05, 'ko', 'MarkerFaceColor', 'k');
title('阈值0.5');
hold off;

subplot(2, 2, 2);
plot(1:Frame_Num:Frame_Num * length(envelope2), envelope2, 'b');
hold on;
plot(locs04 * Frame_Num, peaks04, 'ko', 'MarkerFaceColor', 'k');
title('阈值0.4');
hold off;

subplot(2, 2, 3);
plot(1:Frame_Num:Frame_Num * length(envelope2), envelope2, 'b');
hold on;
plot(locs03 * Frame_Num, peaks03, 'ko', 'MarkerFaceColor', 'k');
title('阈值0.3');
hold off;

subplot(2, 2, 4);
plot(1:Frame_Num:Frame_Num * length(envelope2), envelope2, 'b');
hold on;
plot(locs02 * Frame_Num, peaks02, 'ko', 'MarkerFaceColor', 'k');
title('阈值0.2');
hold off;
