function [b,a] = u_buttap(N,Omegac);

% Unnormalized Butterworth Analog Lowpass Filter Prototype

% --------------------------------------------------------

% [b,a] = u_buttap(N,Omegac);

%      b = numerator polynomial coefficients of Ha(s)

%      a = denominator polynomial coefficients of Ha(s)

%      N = Order of the Butterworth Filter

% Omegac = Cutoff frequency in radians/sec

%

[z,p,k] = buttap(N);

      p = p*Omegac;

      k = k*Omegac^N;

      B = real(poly(z));

      b0 = k;

      b = k*B;

      a = real(poly(p));