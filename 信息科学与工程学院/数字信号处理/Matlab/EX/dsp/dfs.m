function [Xk] = dfs(xn,N)

% Computes Discrete Fourier Series Coefficients

% ---------------------------------------------

% [Xk] = dfs(xn,N)

% Xk = DFS coeff. array over 0 <= k <= N-1

% xn = One period of periodic signal over 0 <= n <= N-1

%  N = Fundamental period of xn

%

n = [0:1:N-1];                       % row vector for n

k = [0:1:N-1];                       % row vecor for k

WN = exp(-j*2*pi/N);                 % Wn factor

nk = n'*k;                           % creates a N by N matrix of nk values

WNnk = WN .^ nk;                     % DFS matrix

Xk = xn * WNnk;                      % row vector for DFS coefficients

