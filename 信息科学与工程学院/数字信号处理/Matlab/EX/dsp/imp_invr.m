function [b,a] = imp_invr(c,d,T)

% Impulse Invariance Transformation from Analog to Digital Filter

% ---------------------------------------------------------------

% [b,a] = imp_invr(c,d,T)

%  b = Numerator polynomial in z^(-1) of the digital filter

%  a = Denominator polynomial in z^(-1) of the digital filter

%  c = Numerator polynomial in s of the analog filter

%  d = Denominator polynomial in s of the analog filter

%  T = Sampling (transformation) parameter

%

[R,p,k] = residue(c,d);

p = exp(p*T);

[b,a] = residuez(R,p,k);

b = real(b);

a = real(a);