function [b,a] = cas2dir(b0,B,A);

% CASCADE-to-DIRECT form conversion

% ---------------------------------

% [b,a] = cas2dir(b0,B,A)

%  b = numerator polynomial coefficients of DIRECT form

%  a = denominator polynomial coefficients of DIRECT form

% b0 = gain coefficient

%  B = K by 3 matrix of real coefficients containing bk's

%  A = K by 3 matrix of real coefficients containing ak's

%

[K,L] = size(B);

b = [1];

a = [1];

for i=1:1:K

	b=conv(b,B(i,:));

	a=conv(a,A(i,:));

end

b = b*b0;

