function [b,a] = pfe2rfz(R,P,C)

% Rational function from Partial Fraction Expansions in z-Domain

% --------------------------------------------------------------

% [b,a] = pfe2rfz(R,P,C)

%  b = numerator polynomial coefficients [b0,b1,...,bM] of rational function,

%  a = denominator polynomial coefficients [a0,a1,...,aN] of rational function,

%  R = row vector containing residues evaluated at poles in p vector,

%  p = row vector containing poles of the rational (roots of a),

%  C = (M-N) length (or null) vector containing poly coeffcients.

%

R = R'; p = p';

[b1,a1]=residue(R,P,[]);

b1=fliplr(b1); a1=fliplr(a1);

[r,p,k]=residue(b1,a1);

[b,a]=residue(r,p,fliplr(C));

b=fliplr(b); a=fliplr(a);

b=real(b); a=real(a);

b=b/a(1); a=a/a(1);

