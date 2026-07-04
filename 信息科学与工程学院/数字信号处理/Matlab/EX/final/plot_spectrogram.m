function plot_spectrogram(audio, fs, freq_range)

    % 设置参数
    window_size = 1024; % 窗口大小
    overlap = 512; % 重叠大小
    nfft = 1024; % FFT点数

    % 计算谱图
    [S, F, T] = spectrogram(audio, window_size, overlap, nfft, fs);

    % 转换为dB
    S_dB = 20 * log10(abs(S));

    % 绘制谱图
    figure;
    imagesc(T, F, S_dB);
    axis xy;
    colormap(jet);
    colorbar;
    xlabel('时间 (秒)');
    ylabel('频率 (Hz)');
    title('音阶音频的谱图');

    ylim(freq_range);
end
