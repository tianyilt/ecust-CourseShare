function plot_spec_noteLen(music, Fs, start_index, freq_range)
    % 将音程作为帧长，绘制音符的频谱图
    %  参数: music, Fs, start_index, freq_range=2000

    frame_t = start_index / Fs; %谱图横坐标单位调为时间(s)
    F0 = 1; %观察谱间隔暂定1 Hz
    frame_N = length(start_index); %帧数
    fft_N = Fs / F0; %每一帧FFT的点数，暂设为44100点
    frame_f = (0:floor((fft_N - 1))) * F0; %谱图纵坐标单位为Hz
    frame_A = zeros(fft_N, frame_N); % frame_A记录某一帧的某一频率处的值，后面用颜色显示

    for i = 2:frame_N
        test_music = music(start_index(i - 1):start_index(i)); %每一帧包含音程内所有点
        frame_A(:, i - 1) = abs(fft(test_music .* hamming(length(test_music)), fft_N));
    end

    % 对于最后一段音符
    test_music = music(start_index(frame_N):end); %一直到音乐结束
    frame_A(:, frame_N) = abs(fft(test_music .* hamming(length(test_music)), fft_N));

    figure;
    imagesc(frame_t, frame_f, frame_A);
    axis xy; % axis xy ：笛卡尔轴模式，原点在左下角，y轴是竖直的，由底至顶标数，x轴是水平的，从左往右标数
    M_T = ceil(length(music) / Fs); %音乐总的时间
    axis([0 M_T 0 freq_range]);
end
