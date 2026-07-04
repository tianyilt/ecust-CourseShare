function real_beat_t = get_rhythm(start_index, Frame_Num, Fs, tempo, min_div)
    % 获取节奏
    % min_div: 最小刻度, 如果不填写, 返回实际浮点数

    normalize_flag = 0;
    if nargin == 5
        normalize_flag = 1;
    end

    real_beat_t = zeros(1, length(start_index) - 1);

    for i = 1:length(start_index) - 1
        real_beat_t(i) = (start_index(i + 1) - start_index(i)) * Frame_Num / Fs / 60 * tempo;
        if normalize_flag == 1
            real_beat_t(i) = round(real_beat_t(i) / min_div) * min_div;
        end
    end

end
