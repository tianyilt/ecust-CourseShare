function plot_spec_fixedFrame(music, Fs, plot_frame_len, freq_range)
    % 绘制固定帧长的谱图
    %  参数: music, Fs, plot_frame_len=400, freq_range=2000
    test_Num = plot_frame_len; %画谱图的临时帧长（非前面计算包络的帧长Frame_Num）
    F0 = 1; %观察谱间隔暂定1 Hz
    frame_N = floor(length(music) / test_Num); %帧数
    frame_t = (0:frame_N - 1) * test_Num / Fs; %谱图横坐标单位调为时间(s)
    fft_N = Fs / F0; %每一帧FFT的点数，暂设为44100点
    frame_f = (0:floor((fft_N - 1))) * F0; %谱图纵坐标单位为Hz
    frame_A = zeros(fft_N, frame_N); % frame_A记录某一帧的某一频率处的值，后面用颜色显示

    for i = 1:frame_N - 1
        test_music = music((i - 1) * test_Num + 1:i * test_Num); %每一帧400点
        %每一帧400点，均乘400点哈明窗后，做44100点FFT
        frame_A(:, i) = abs(fft(test_music .* hamming(test_Num), fft_N));
    end

    figure;
    imagesc(frame_t, frame_f, frame_A);
    axis xy; % axis xy ：笛卡尔轴模式，原点在左下角，y轴是竖直的，由底至顶标数，x轴是水平的，从左往右标数
    M_T = ceil(length(music) / Fs); %音乐总的时间
    axis([0 M_T 0 freq_range]);
end
