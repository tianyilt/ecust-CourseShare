function [envelope, peaks, start_index] = get_start_index(x, ~, Frame_Num, threshold)
    %获取包络, 峰值, 起始点
    %   参数: x, fs, Frame_Num=128, threshold=0.3
    if (nargin == 2)
        Frame_Num = 256;
    end

    if (nargin == 3)
        threshold = 0.3;
    end

    music = x ./ max(abs(x)); % 归一化

    % step2: 帧峰检测法, 获得包络
    envelope = [];

    for i = 1:floor(length(music) / Frame_Num) - 1 % i是以Frame_Num个点分帧后的帧号
        temp = music((i - 1) * Frame_Num +1:i * Frame_Num); %每Frame_Num点是一个临时帧
        envelope = [envelope max(temp) - min(temp)]; %取出当前帧的峰峰值作为该帧的帧峰值
    end

    % step3: 疯狂滤波平滑
    envelope = medfilt1(envelope, 5); % 中值滤波medfilt1
    envelope = conv(envelope, ones(1, 5) / 5, 'same'); % 5点平均滤波
    envelope = conv(envelope, ones(1, 12) / 12, 'same'); % 12点平均滤波
    envelope = conv(envelope, ones(1, 15) / 15, 'same'); % 15点平均滤波
    envelope = envelope ./ max(envelope); % 归一化

    % [peaks , start_index] = findpeaks(envelope, 'MinPeakHeight', threshold); % 阈值0.3
    [peaks, start_index] = findpeaks( ...
        envelope, ...
        'widthreference', 'halfheight', ...
        'MinPeakHeight', threshold, ...
        'MinPeakProminence', 0.2 ...
    );
end
