function [Key_Rec, Key_code, Key_index, Key_count] = get_note_key(start_index, KeyEnergy_Ms, threshold)
    % get_note_key - 根据琴键能量矩阵识别音符对应的键号
    % threshold 用于限制检测琴键值的范围, (a, b], 不包含左端点, 包含右端点
    %
    % Key_Rec 用于绘制瀑布图的矩阵
    % Key_code 音符对应的键号数组, 下标在1-88之间
    % Key_index 音符的起始位置, 与start_index相同
    % Key_count 音符数量

    if nargin < 3
        threshold = [0 88];
    end
    if length(threshold) == 1
        threshold = [threshold 88];
    end

    sensitivity = 0.05;

    % 根据琴键能量矩阵设计策略识别音符对应的键号
    Key_Rec = zeros(1, 108);
    Key_code = [];
    Key_index = [];

    for i = 1:length(start_index)
        KeyEnergy_i = KeyEnergy_Ms(:, i);
        KeyEnergy_i = KeyEnergy_i((threshold(1)+1):(threshold(2)));
        % 找出能量最大的键号
        [~, max_index] = max(KeyEnergy_i);
        % 找出KeyEnergy_i中比threshold大的第一个的键号
        left_index = find(KeyEnergy_i > sensitivity, 1, 'first');

        % disp("KeyEnergy_i的长度为: " + length(KeyEnergy_i));

        % 对于低音区, 容易出现left_index != max_index的情况
        % 需要额外检查判断
        if any(left_index == max_index) || any(left_index == threshold(1))
            % 添加一个音符
            temp = zeros(1, 108);
            temp(max_index+threshold(1)) = 1;
            Key_Rec = [Key_Rec; temp]; %#ok<AGROW>
            Key_code = [Key_code; max_index+threshold(1)]; %#ok<AGROW>
            Key_index = [Key_index; start_index(i)]; %#ok<AGROW>
        else
            % 追加判断
            % 取出所有大于threshold的键号
            keys = find(KeyEnergy_i > sensitivity);
            % disp("第" + i + "个音符, 可能的键号有: " + keys);
            % 逐个获取可能性, 选择最可能的键号
            max_prob = 0;
            max_key = 0;

            for j = 1:length(keys)
                key = keys(j);
                prob = check_note_validation(KeyEnergy_i, key);

                if prob > max_prob
                    max_prob = prob;
                    max_key = key;
                end

            end
            % disp("第" + i + "个音符, 最可能的键号为: " + max_key);
            % 添加一个音符
            temp = zeros(1, 108);
            temp(max_key+threshold(1)) = 1;
            Key_Rec = [Key_Rec; temp]; %#ok<AGROW>
            Key_code = [Key_code; max_key+threshold(1)]; %#ok<AGROW>
            Key_index = [Key_index; start_index(i)]; %#ok<AGROW>
        end

    end

    Key_Rec = Key_Rec(2:end, :);
    Key_count = size(Key_Rec, 1);
    % 转置Key_Rec, 使得每一列代表一个音符
    Key_Rec = Key_Rec';

end
