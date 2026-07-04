function [C,B,A] = sdir2cas(b,a);

% DIRECT-form to CASCADE-form conversion in s-plane

% -------------------------------------------------

% [C,B,A] = sdir2cas(b,a)

%  C = gain coefficient

%  B = K by 3 matrix of real coefficients containing bk's

%  A = K by 3 matrix of real coefficients containing ak's

%  b = numerator polynomial coefficients of DIRECT form

%  a = denominator polynomial coefficients of DIRECT form

%

Na = length(a)-1; Nb = length(b)-1;



% compute gain coefficient C

b0 = b(1); b = b/b0;

a0 = a(1); a = a/a0;

 C = b0/a0;

%

% Denominator second-order sections:

p= cplxpair(roots(a)); K = floor(Na/2);

if K*2 == Na     % Computation when Na is even

   A = zeros(K,3);

   for n=1:2:Na

       Arow = p(n:1:n+1,:);

       Arow = poly(Arow);

       A(fix((n+1)/2),:) = real(Arow);

   end



elseif Na == 1   % Computation when Na = 1

       A = [0 real(poly(p))];



else             % Computation when Na is odd and > 1

   A = zeros(K+1,3);

   for n=1:2:2*K

       Arow = p(n:1:n+1,:);

       Arow = poly(Arow);

       A(fix((n+1)/2),:) = real(Arow);

       end

       A(K+1,:) = [0 real(poly(p(Na)))];

end



% Numerator second-order sections:

z = cplxpair(roots(b)); K = floor(Nb/2);

if Nb == 0           % Computation when Nb = 0

   B = [0 0 poly(z)];



elseif K*2 == Nb     % Computation when Nb is even

   B = zeros(K,3);

   for n=1:2:Nb

       Brow = z(n:1:n+1,:);

       Brow = poly(Brow);

       B(fix((n+1)/2),:) = real(Brow);

   end



elseif Nb == 1       % Computation when Nb = 1

       B = [0 real(poly(z))];



else                 % Computation when Nb is odd and > 1

   B = zeros(K+1,3);

   for n=1:2:2*K

       Brow = z(n:1:n+1,:);

       Brow = poly(Brow);

       B(fix((n+1)/2),:) = real(Brow);

   end

   B(K+1,:) = [0 real(poly(z(Nb)))];

end





