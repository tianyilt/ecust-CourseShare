function hd = ideal_lp(wc,M);

% Ideal LowPass filter computation

% --------------------------------

% [hd] = ideal_lp(wc,M)

%  hd = ideal impulse response between 0 to M-1

%  wc = cutoff frequency in radians

%   M = length of the ideal filter

%

alpha = (M-1)/2;

n = [0:1:(M-1)];

m = n - alpha + eps;

hd = sin(wc*m) ./ (pi*m);



