function [y, ny] = seqshift(x, nx, k)
    % y(n) = x(n - k)
    % ---------------
    % [y, ny] = seqshift(x, nx, k)
    % y = shifted sequence over ny
    % ny = sample points over ny
    % x = sequence over nx
    % nx = sample points over nx
    % k = shift value

    ny = nx + k;
    y = x;
end
