function w_black = Blackman(M);

%  M-point Blackman window

%  -----------------------

% w_black = Blackman(M);

%

M1 = M-1;

m = [0:1:M1];

w_black = abs(0.42 - 0.5*cos(2*pi*m'/(M1)) + 0.08*cos(4*pi*m'/(M1)));



