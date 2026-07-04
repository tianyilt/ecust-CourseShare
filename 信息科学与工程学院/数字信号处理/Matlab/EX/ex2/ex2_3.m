close all
clear

n = [0:200];

% 1, 2
mydraw(0:100, [0.3125], [1 -0.8 0.64], [1, zeros(1, 100)]);
% 3
mydraw(0:200, [0.3125], [1 -0.8 0.64], 5 + 3 .* cos(pi / 3 .* n));
% 4
mydraw(0:200, [1 -1], [1 -0.8 0.64], 5 + 3 .* cos(pi / 3 .* n));

function mydraw(n, b, a, x)
    y = filter(b, a, x);
    figure;
    subplot(2, 2, 1); plot(n, y); title('y');
    [z, p, k] = tf2zp(b, a);
    subplot(2, 2, 2); zplane(b, a); title('z and p');
    [Fh, w] = freqz(b, a);
    subplot(2, 2, 3); plot(w / pi, abs(Fh)); title('|H(w)|');
    subplot(2, 2, 4); plot(w / pi, angle(Fh)); title('ang|H(w)|');
end