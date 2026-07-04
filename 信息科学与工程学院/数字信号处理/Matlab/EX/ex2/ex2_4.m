%#ok<*GVMIS>
close all
clear

addpath('D:\Documents\学习_大学\大三上\数字信号处理\Matlab\EX\wav');

global index
global keyset
global valueset
index = 0;
keyset = {220, 246.94, 261.63, 293.66, 329.63, 349.23, 392};
valueset = {'la', 'ci', 'do', 're', 'mi', 'fa', 'so'};

global myMap
myMap = containers.Map(keyset, valueset);

process('test1.wav');
process('test2.wav');
process('test3.wav');
process('test4.wav');

function detected_notes = find_closestKey(aaa)
    global keyset
    global valueset

    detected_notes = {};

    for k = 1:length(aaa)
        x = aaa(k);
        index = 1;
        delta = min([abs(x - keyset{1}) abs(x - keyset{1}*2)]);

        for i = 2:length(keyset)

            if (min([abs(x - keyset{i}) abs(x - keyset{i}*2)]) < delta)
                index = i;
                delta = min([abs(x - keyset{i}) abs(x - keyset{i}*2)]);
            end

        end
        % 在detected_notes中添加对应的音符
        detected_notes{end + 1} = valueset{index};
    end

end

function drawfreq(y, fs, filename)
    global index
    global myMap
    N = length(y);
    f = (0:N - 1) * (fs / N);
    Y = fft(y);
    N = length(f(f < 800));
    f = f(1:N);
    Y = abs(Y(1:N));

    % 限制在识别的频率范围内
    % f = f(f > 200 & f < 800);
    % Y = Y(f > 200 & f < 800);

    figure(1);
    subplot(4, 3, index * 3 - 1);
    plot(f, Y);
    title(['频谱图 - ' filename]); xlabel('频率 (Hz)'); ylabel('幅度');

    [peaky, peakx] = findpeaks(Y);

    filter_ = peaky > 0.3 * max(Y);
    peakx_filtered = peakx(filter_);
    peaky_filtered = peaky(filter_);
    peakx_filtered = f(peakx_filtered);

    closestKey = find_closestKey(peakx_filtered);
    % 不改变顺序, 去重
    closestKey = unique(closestKey, 'stable');
    

    figure(1);
    subplot(4, 3, index * 3);
    % 绘制文字
    msg = ['检测到的音符: ' closestKey];
    text(0.5, 0.5, msg, 'FontSize', 20, 'HorizontalAlignment', 'center');
    % 影藏坐标轴
    axis off;

    % disp(peakx_filtered);
    % disp(peaky_filtered);

    % for i = 1:length(peakx_filtered)
    %     detected_notes = fin_closestKey(peakx_filtered(i));
    %     disp(myMap(detected_notes));

    % end

end

function process(file)
    global index
    index = index + 1;
    [x, fs] = audioread(file);
    figure(1);
    subplot(4, 3, index * 3 - 2);
    plot(x);
    title(['test' int2str(index)]);
    [~, name, ~] = fileparts(file);
    drawfreq(x, fs, name);
end
