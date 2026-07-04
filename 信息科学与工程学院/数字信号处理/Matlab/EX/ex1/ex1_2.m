clc;
clear;
close all;

n = 0:100;
wn = (rand(1, length(n)) - 0.5) * 10;

xn = 10 * cos(0.08 * pi * n) + wn;
x = [xn zeros(1, 10)];
b1 = ones(1, 11) / 11; a1 = 1;
yn = filter(b1, a1, x);

% figure('Name', 'Question 1');
subplot(5, 1, 1); plot(n, xn, 'r', 'linewidth', 2);
title('Input signal x(n)');
subplot(5, 1, 2); plot(0:110, yn, 'b', 'linewidth', 2);
title('Output signal y(n)');

b2 = [1, -2, 1]; a2 = 1;
vn = filter(b2, a2, xn);

% figure('Name', 'Question 2');
subplot(5, 1, 3); plot(n, vn, 'g', 'linewidth', 2);
title('Difference signal v(n)');

cn = xcorr(vn, wn);

% figure('Name', 'Question 3');
subplot(5, 1, 4); plot(-100:100, cn, 'b', 'linewidth', 2);
title('Correlation sequence c(n)');

wn_ = (rand(1, length(n)) - 0.5) * 10;
cn_ = xcorr(vn, wn_);

% figure('Name', 'Question 4');
subplot(5, 1, 5); plot(-100:100, cn_, 'b', 'linewidth', 2);
title('Another correlation sequence c_(n)');
