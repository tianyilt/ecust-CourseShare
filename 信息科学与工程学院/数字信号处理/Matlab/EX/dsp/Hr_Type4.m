function [Hr,w,d,L] = Hr_Type4(h);

% Computes Amplitude response of Type-4 LP FIR filter

% ---------------------------------------------------

% [Hr,w,d,L] = Hr_Type4(h)

% Hr = Amplitude Response

%  w = frequencies between [0 pi] over which Hr is computed

%  d = Type-4 LP filter coefficients

%  L = Order of d

%  h = Type-4 LP impulse response

% 

 M = length(h);

 L = M/2;

 d = 2*[h(L:-1:1)];

 n = [1:1:L]; n = n-0.5;

 w = [0:1:500]'*pi/500;

Hr = sin(w*n)*d';



