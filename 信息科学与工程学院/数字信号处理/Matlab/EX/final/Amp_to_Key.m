function KeyEnergy_Ms = Amp_to_Key(Amp_MS, F0)
    % 返回的Key下标在1-88之间
    PianoKey_F = xlsread('Piano_Key_F.xlsx'); %#ok<XLSRD>

    [~, len] = size(Amp_MS);

    for i = 1:len
        Amp_MS(:, i) = Amp_MS(:, i) / max(Amp_MS(:, i));
        % 将音频幅度矩阵映射到按键矩阵中
        for j = 2:88
            f_down = (PianoKey_F(j - 1, 1) + PianoKey_F(j, 1)) / 2;
            f_up = (PianoKey_F(j, 1) + PianoKey_F(j + 1, 1)) / 2;

            KeyEnergy_Ms(j, i) = mean(Amp_MS(floor(f_down / F0):ceil(f_up / F0), i)); %#ok<AGROW>
        end

        % 归一化
        KeyEnergy_Ms(:, i) = KeyEnergy_Ms(:, i) / max(KeyEnergy_Ms(:, i));

    end

end
