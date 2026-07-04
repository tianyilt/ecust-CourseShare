function [y, n] = seqfold(x, n)
    % y(n) = x(-n)
    % ---------------
    % [y, n] = seqfold(x, n)
    % y = folded sequence over n
    % n = sample points over n
    % x = sequence over n
    % n = sample points over n

    y = fliplr(x);
    n = -fliplr(n);
end
