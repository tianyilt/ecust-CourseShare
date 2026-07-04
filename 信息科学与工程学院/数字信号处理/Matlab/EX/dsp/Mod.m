function m = Mod(n,N)

% Computes m = (n mod N) index

% ----------------------------

% m = mod(n,N)

m = rem(n,N);

m = m+N;

m = rem(m,N);

