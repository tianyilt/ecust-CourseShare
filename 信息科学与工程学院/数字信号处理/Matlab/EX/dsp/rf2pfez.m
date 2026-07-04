function [R,p,C] = rf2pfez(b,a);

% Partial Fraction Expansion from rational function in z-Domain

% -------------------------------------------------------------

% [R,p,C] = rf2pfez(b,a)

%  R = row vector containing residues evaluated at poles in p vector,

%  p = row vector containing poles of the rational (roots of a),

%  C = (M-N) length (or null) vector containing poly coeffcients,

%  b = numerator polynomial coefficients [b0,b1,...,bM] of rational function,

%  a = denominator polynomial coefficients [a0,a1,...,aN] of rational function.

%

b = b/a(1); a = a/a(1);

b = fliplr(b); a = fliplr(a);

[R,p,C] = residue(b,a);

C = fliplr(C);

[b1,a1] = residue(R,p,[]);

b1 = fliplr(b1); a1 = fliplr(a1);

[R,p,k] = residue(b1,a1);

R = R'; p = p';