function [K] = dir2latc(b)

% FIR Direct form to All-Zero Lattice form Conversion

% ---------------------------------------------------

% [K] = dir2latc(b)

%  K = Lattice filter coefficients (reflection coefficients)

%  b = FIR direct form coefficients (impulse response)

%

M = length(b);

K = zeros(1,M);

b1 = b(1);

if b1 == 0

	error('b(1) is equal to zero')

end

K(1) = b1; A = b/b1;

for m=M:-1:2

	K(m) = A(m);

	J = fliplr(A);

	A = (A-K(m)*J)/(1-K(m)*K(m));

	A = A(1:m-1);

end

