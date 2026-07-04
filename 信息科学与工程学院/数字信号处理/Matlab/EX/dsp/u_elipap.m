function [b,a] = u_elipap(N,Rp,As,Omegac);

% Unnormalized Elliptic Analog Lowpass Filter Prototype

% -----------------------------------------------------

% [b,a] = u_elipap(N,Rp,As,Omegac);

%      b = numerator polynomial coefficients

%      a = denominator polynomial coefficients

%      N = Order of the Elliptic Filter

%     Rp = Passband Ripple in dB; Rp > 0

%     As = Stopband Attebuation in dB; As > 0

% Omegac = Cutoff frequency in radians/sec

%

[z,p,k] = ellipap(N,Rp,As);

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