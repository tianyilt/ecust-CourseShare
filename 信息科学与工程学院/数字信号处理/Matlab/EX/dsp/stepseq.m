function [x,n] = stepseq(n0,n1,n2)

% Generates x(n) = u(n-n0); n1 <= n,n0 <= n2

% ------------------------------------------

% [x,n] = stepseq(n0,n1,n2)

%

if ((n0 < n1) | (n0 > n2) | (n1 > n2))

	error('arguments must satisfy n1 <= n0 <= n2')

end

n = [n1:n2];

%x = [zeros(1,(n0-n1)), ones(1,(n2-n0+1))];

x = [(n-n0) >= 0];

