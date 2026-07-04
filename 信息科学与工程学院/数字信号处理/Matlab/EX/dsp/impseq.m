function [x,n] = impseq(n0,n1,n2)

% Generates x(n) = delta(n-n0); n1 <= n,n0 <= n2

% ----------------------------------------------

% [x,n] = impseq(n0,n1,n2)

%

if ((n0 < n1) | (n0 > n2) | (n1 > n2))

	error('arguments must satisfy n1 <= n0 <= n2')

end

n = [n1:n2];

%x = [zeros(1,(n0-n1)), 1, zeros(1,(n2-n0))];

x = [(n-n0) == 0];

