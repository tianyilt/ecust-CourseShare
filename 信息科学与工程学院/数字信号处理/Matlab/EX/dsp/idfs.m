function [xn] = idfs(Xk,N)

% Computes Inverse Discrete Fourier Series

% ----------------------------------------

% [xn] = idfs(Xk,N)

% xn = One period of periodic signal over 0 <= n <= N-1

% Xk = DFS coeff. array over 0 <= k <= N-1

%  N = Fundamental period of Xk

%

n = [0:1:N-1];                       % row vector for n

k = [0:1:N-1];                       % row vecor for k

WN = exp(-j*2*pi/N);                 % Wn factor

nk = n'*k;                           % creates a N by N matrix of nk values

WNnk = WN .^ (-nk);                  % IDFS matrix

xn = (Xk * WNnk)/N;                  % row vector for IDFS values

