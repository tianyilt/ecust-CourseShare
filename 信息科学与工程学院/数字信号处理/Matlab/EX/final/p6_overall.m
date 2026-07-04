close all;
clear;

addpath("D:\Documents\学习_大学\大三上\数字信号处理\Matlab\EX\final")
addpath("D:\Documents\学习_大学\大三上\数字信号处理\Matlab\EX\final\scale_sample")
addpath("D:\Documents\学习_大学\大三上\数字信号处理\Matlab\EX\final\music")

% iptsetpref('ImshowBorder','tight');
set(0, 'DefaultFigureMenu', 'none');
format compact;

% step0: 设定参数
json_file = "D:\Documents\学习_大学\大三上\数字信号处理\Matlab\EX\final\param_setting.json";
json_str = fileread(json_file);
json_obj = jsondecode(json_str);

Frame_Num = json_obj.Frame_Num;
F0 = json_obj.F0;
song_file = json_obj.song_file;
tempo = json_obj.tempo;
ideal_beat_t = json_obj.ideal_beat_t;
threshold = json_obj.threshold;
plot_size = json_obj.plot_size;
output_dir = json_obj.output_dir;

% Frame_Num = 256; % 帧长
% F0 = 0.1; % 采样频率
% song_file = "star_69.wav"; % 音频文件
% tempo = 69; % 理想节奏
% ideal_beat_t = [1 1 1 1 1 1 2 1 1 1 1 1 1 2 1 1 1 1 1 1 2 1 1 1 1 1 1 2 1 1 1 1 1 1 2 1 1 1 1 1 1]; % 理想时长
% threshold = [59 108] - 20; % 检测阈值
% plot_size = [6 8]; % 画图大小
% output_file = "D:\Documents\学习_大学\大三上\数字信号处理\Matlab\EX\final\output\"+song_file + ".json";

% step1: 读入音频
[x, Fs] = audioread(song_file);
music = x(:, 1) ./ max(abs(x(:, 1))); % 取左声道, 归一化

% step2: 帧峰检测法, 获得包络
[envelope, peaks, start_index] = get_start_index(x, Fs, Frame_Num);
% start_index = start_i * Frame_Num;

% 画出音频和包络
figure("Name", "音频和包络");
set(gcf,'outerposition',get(0,'screensize'));
plot(x);
hold on;

for i = 1:length(start_index)
    plot(start_index(i) * Frame_Num, peaks(i), 'ro');
    % 在旁边标号
    text(start_index(i) * Frame_Num, peaks(i), num2str(i));
end

hold on;
plot(1:Frame_Num:Frame_Num * length(envelope), envelope, 'g');
hold off;

% step3: 划分音符得到每个音符的幅度矩阵
Amp_MS = get_Amp_MS(x, Fs, Frame_Num, F0);
KeyEnergy_Ms = Amp_to_Key(Amp_MS, F0);

% 画出每个音符的琴键能量矩阵
figure("Name", "琴键能量矩阵");
set(gcf,'outerposition',get(0,'screensize'));

for i = 1:length(start_index)
    subplot(plot_size(1), plot_size(2), i);
    KeyEnergy_i = KeyEnergy_Ms(:, i);
    key_Index = 1:88;
    plot(key_Index, KeyEnergy_i);
    axis([1 88 0 1]);
    title("第" + i + "个音符");
end

% 瀑布流图(根据音符划分)
figure("Name", "瀑布流图");
set(gcf,'outerposition',get(0,'screensize'));
imagesc(1:length(start_index), 21:108, KeyEnergy_Ms);
axis xy; axis([0.5 length(start_index) + 0.5 21 108]);

% step4: 识别音符对应的键号
[Key_Rec, Key_code, Key_index, Key_count] = get_note_key(start_index, KeyEnergy_Ms, threshold);

% 瀑布图, 修正后
figure("Name", "识别后的瀑布图");
set(gcf,'outerposition',get(0,'screensize'));
imagesc(1:length(start_index), 21:108, Key_Rec);
axis xy; axis([0.5 length(start_index) + 0.5 21 108]);

% step5: 判断节奏
real_beat_t = zeros(1, length(start_index) - 1);

if (size(ideal_beat_t, 1) ~= 1)
    ideal_beat_t = ideal_beat_t';
end

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

figure("Name", "节奏评价");
set(gcf,'outerposition',get(0,'screensize'));

if (length(start_index) == length(ideal_beat_t))
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

else

    subplot(3, 1, 1);
    plot(1:length(ideal_beat_t), ideal_beat_t, 'rx');
    title("理想节奏");

    subplot(3, 1, 2);
    plot(1:length(real_beat_t), real_beat_t, 'bo');
    title("实际节奏");

    subplot(3, 1, 3);
    msg = "理想节奏长度与实际节奏长度不一致";
    text(0.5, 0.5, msg, 'FontSize', 20, 'HorizontalAlignment', 'center');
    axis off;
end

% step7: 列表整理出识别结果, 保存输出
key_list = Key_code + 20;
dur_list = real_beat_t;

disp("识别结果:");
fprintf("序号 \t 键号 \t 时长\n");

for i = 1:length(key_list) - 1
    fprintf("%d \t %d \t %.2f\n", i, key_list(i), dur_list(i));
end

% 保存输出为json
if ~exist(output_dir, 'dir')
    mkdir(output_dir);
end

output_file = fullfile(output_dir, "result.json");
disp("输出保存至" + output_file);
fid = fopen(output_file, 'w');
obj = struct("name", song_file, "tempo", tempo, "key_list", key_list, "dur_list", dur_list);
json_str = jsonencode(obj);
fprintf(fid, json_str);
fclose(fid);
disp("输出保存完毕");

% 保存所有图片到output_dir, 名称为标题
disp("准备保存所有图片到" + output_dir);
figs = findobj('Type', 'figure');

for i = 1:length(figs)
    fig = figs(i);
    fig_name = fig.Name;
    fig_file = fullfile(output_dir, fig_name + ".png");
    saveas(fig, fig_file);
end

disp("图片保存完毕");
