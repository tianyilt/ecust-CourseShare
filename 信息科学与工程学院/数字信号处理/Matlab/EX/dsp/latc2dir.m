function [b] = latc2dir(K)

% All-Zero Lattice form to FIR Direct form Conversion

% ---------------------------------------------------

% [b] = latc2dir(K)

%  b = FIR direct form coefficients (impulse response)

%  K = Lattice filter coefficients (reflection coefficients)

%

M = length(K);

J = 1; A = 1;

for m=2:1:M

	A = [A,0]+conv([0,K(m)],J);

	J = fliplr(A);

end

b=A*K(1);

