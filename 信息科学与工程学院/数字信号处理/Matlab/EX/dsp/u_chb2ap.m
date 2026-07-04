function [b,a] = u_chb2ap(N,As,Omegac);

% Unnormalized Chebyshev-2 Analog Lowpass Filter Prototype

% --------------------------------------------------------

% [b,a] = u_chb2ap(N,As,Omegac);

%      b = numerator polynomial coefficients

%      a = denominator polynomial coefficients

%      N = Order of the Elliptic Filter

%     As = Stopband Ripple in dB; As > 0

% Omegac = Cutoff frequency in radians/sec

%

[z,p,k] = cheb2ap(N,As);

      a = real(poly(p));

    aNn = a(N+1);

      p = p*Omegac;

      a = real(poly(p));

    aNu = a(N+1);  

      b = real(poly(z));

      M = length(b);

    bNn = b(M);  

      z = z*Omegac;

      b = real(poly(z));

    bNu = b(M);

      k = k*(aNu*bNn)/(aNn*bNu);

     b0 = k;

      b = k*b;