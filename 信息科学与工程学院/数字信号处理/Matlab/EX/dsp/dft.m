function [Xk] = dft(xn,N)

% Computes Discrete Fourier Transform

% -----------------------------------

% [Xk] = dft(xn,N)

% Xk = DFT coeff. array over 0 <= k <= N-1

% xn = N-point finite-duration sequence

%  N = Length of DFT

%

n = [0:1:N-1];                       % row vector for n

k = [0:1:N-1];                       % row vecor for k

WN = exp(-j*2*pi/N);                 % Wn factor

nk = n'*k;                           % creates a N by N matrix of nk values

WNnk = WN .^ nk;                     % DFT matrix

Xk = xn * WNnk;                      % row vector for DFT coefficients

