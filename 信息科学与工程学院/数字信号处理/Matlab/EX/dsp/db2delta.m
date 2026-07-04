function [d1,d2] = db2delta(Rp,As)

% Conversion from Relative dB specs to Absolute delta specs.

% ----------------------------------------------------------

% [d1,d2] = db2delta(Rp,As)

% d1 = Passband tolerance

% d2 = Stopband tolerance

% Rp = Passband ripple

% As = Stopband attenuation

%

K = 10^(Rp/20);

d1 = (K-1)/(K+1);

d2 = (1+d1)*(10^(-As/20));

