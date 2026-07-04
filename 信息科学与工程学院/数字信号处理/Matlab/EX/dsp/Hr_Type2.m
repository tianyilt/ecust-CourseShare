function [Hr,w,b,L] = Hr_Type2(h);

% Computes Amplitude response of Type-2 LP FIR filter

% ---------------------------------------------------

% [Hr,w,b,L] = Hr_Type2(h)

% Hr = Amplitude Response

%  w = frequencies between [0 pi] over which Hr is computed

%  b = Type-2 LP filter coefficients

%  L = Order of Hr

%  h = Type-2 LP impulse response

% 

 M = length(h);

 L = M/2;

 b = 2*[h(L:-1:1)];

 n = [1:1:L]; n = n-0.5;

 w = [0:1:500]'*pi/500;

Hr = cos(w*n)*b';