function [b,a] = ladr2dir(K,C)

% Lattice/Ladder form to IIR Direct form Conversion

% -------------------------------------------------

% [b,a] = ladr2dir(K,C)

%  b = numerator polynomial coefficients

%  a = denominator polymonial coefficients

%  K = Lattice coefficients (reflection coefficients)

%  C = Ladder coefficients

%

N = length(K); M = length(C);

C = [C, zeros(1,N-M+1)];

J = 1; a = 1; A = zeros(N,N);

for m=1:1:N

     a = [a,0]+conv([0,K(m)],J);

     A(m,1:m) = -a(2:m+1);

     J = fliplr(a);

end

b(N+1) = C(N+1);

for m = N:-1:1

     A(m,1:m) = A(m,1:m)*C(m+1);

     b(m) = C(m) - sum(diag(A(m:N,1:N-m+1)));

end

