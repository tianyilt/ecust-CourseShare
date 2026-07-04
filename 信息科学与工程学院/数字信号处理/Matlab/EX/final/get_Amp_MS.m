function Amp_MS = get_Amp_MS(audio, fs, Frame_Num, F0)
    % 读取音频文件
    addpath("D:\Documents\学习_大学\大三上\数字信号处理\Matlab\EX\final\scale_sample")

    music = audio(:, 1) ./ max(abs(audio(:, 1))); % 取左声道, 归一化
    [~, ~, start_i] = get_start_index(audio, fs, Frame_Num);
    start_index = start_i * Frame_Num;

    % 将每个音程的长度做谱分析, 画出谱图, 并判断琴键
    Amp_MS = [];
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
        Amp_MS = [Amp_MS abs(Amp_temp)]; %#ok<*AGROW> %保存本段音程的谱分析结果
    end

end
