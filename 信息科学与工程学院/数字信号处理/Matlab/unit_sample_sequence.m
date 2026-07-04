addpath('D:\Documents\学习_大学\大三上\数字信号处理\Matlab\utils');
[x,n] = impseq(0, -10, 20);
stem(n, x); grid on;
xlabel('Time index n'); ylabel('Amplitude');
title('Unit Sample Sequence');
axis([-10 20 0 1.2]);
