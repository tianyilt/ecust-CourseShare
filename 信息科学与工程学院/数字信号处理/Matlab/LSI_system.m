b = sqrt(181) / 100;
a = [1, .9 * sqrt(2), .81];

% 求出系统函数H(e^jw), 并画出幅度相位特性曲线
N = 512;
[H, w] = my_freqz(b, a, N);
% figure;
% subplot(2, 1, 1);
% plot(w, abs(H));
% title('Magnitude Response');
% subplot(2, 1, 2);
% plot(w, angle(H));
% title('Phase Response');

% % 求出H(z)的零极点分布图
% figure;
% my_zplane(b, a);
% % 单位圆
% hold on;
% plot(cos(0:0.01:2 * pi), sin(0:0.01:2 * pi), 'k--');
% hold off;

% 计算w=3pi/4时的幅度
% H_3pi_4 = polyval(b, exp(-1j * 3 * pi / 4)) / polyval(a, exp(-1j * 3 * pi / 4));
% disp(abs(1/H_3pi_4));
% disp(num2str(abs(1/H_3pi_4)));

n = 0:100;
xn = 20*cos(3/4*pi*n);
yn = filter(b, a, xn);

% 折线图
figure;
subplot(2, 1, 1);
stem(n, xn);
title('x[n] = 20cos(3/4*pi*n)');
subplot(2, 1, 2);
stem(n, yn);
title('y[n] = H(x[n])');


function [H, w] = my_freqz(b, a, N)
    w = (0:N - 1) * 2 * pi / N;
    H = polyval(b, exp(-1j * w)) ./ polyval(a, exp(-1j * w));
end

function my_zplane(b, a)
    z = roots(b);
    p = roots(a);
    
    plot(real(z), imag(z), 'o');
    hold on;
    plot(real(p), imag(p), 'x');
    hold off;
    
    xlabel('Real');
    ylabel('Imaginary');
    title('Pole-Zero Plot');
    grid on;
end