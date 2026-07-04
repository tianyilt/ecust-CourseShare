function [b0,B,A] = dir2cas(b,a);

% DIRECT-form to CASCADE-form conversion (cplxpair version)

% ---------------------------------------------------------

% [b0,B,A] = dir2cas(b,a)

% b0 = gain coefficient

%  B = K by 3 matrix of real coefficients containing bk's

%  A = K by 3 matrix of real coefficients containing ak's

%  b = numerator polynomial coefficients of DIRECT form

%  a = denominator polynomial coefficients of DIRECT form



% compute gain coefficient b0

b0 = b(1); b = b/b0;

a0 = a(1); a = a/a0;

b0 = b0/a0;

%

M=(length(b)); 
N=(length(a));

if N > M

   b = ([b,zeros(1,(N-M))]); 

elseif M > N

	a = [a,zeros(1,(M-N))]; N = M;

else

	NM = 0;

end

%

K = floor(N/2); B = zeros(K,3); A = zeros(K,3);

if K*2 == N;

	b = [b 0];

	a = [a 0];

end

%        

broots = cplxpair(roots(b));

aroots = cplxpair(roots(a));

for i=1:2:2*K

	Brow = broots(i:1:i+1,:);

	Brow = real(poly(Brow));

	B(fix((i+1)/2),:) = Brow;

	Arow = aroots(i:1:i+1,:);

	Arow = real(poly(Arow));

	A(fix((i+1)/2),:) = Arow;

end     

