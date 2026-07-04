function [C,B,A] = dir2fs(h)

% Direct form to Frequency Sampling form conversion

% -------------------------------------------------

% [C,B,A] = dir2fs(h)

% C = Row vector containing gains for parallel sections

% B = Matrix containing numerator coefficients arranged in rows

% A = Matrix containing denominator coefficients arranged in rows

% h = impulse response vector of an FIR filter

%

M = length(h);

H = fft(h,M);

magH = abs(H); phaH = angle(H)';

% check even or odd M

if (M == 2*floor(M/2))

      L = M/2-1;   % M is even

     A1 = [1,-1,0;1,1,0];

     C1 = [real(H(1)),real(H(L+2))];

else

      L = (M-1)/2; % M is odd

     A1 = [1,-1,0];

     C1 = [real(H(1))];

end

k = [1:L]';

% initialize B and A arrays

B = zeros(L,2); A = ones(L,3);

% compute denominator coefficients

A(1:L,2) = -2*cos(2*pi*k/M); A = [A;A1];

% compute numerator coefficients

B(1:L,1) = cos(phaH(2:L+1));

B(1:L,2) = -cos(phaH(2:L+1)-(2*pi*k/M));

% compute gain coefficients

C = [2*magH(2:L+1),C1]';

