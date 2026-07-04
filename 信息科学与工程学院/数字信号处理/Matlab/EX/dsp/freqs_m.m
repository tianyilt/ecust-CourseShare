function [db,mag,pha,w] = freqs_m(b,a,wmax);

% Computation of s-domain frequency response: Modified version

% ------------------------------------------------------------

% [db,mag,pha,w] = freqs_m(b,a,wmax);

%   db = Relative magnitude in db over [0 to wmax]

%  mag = Absolute magnitude over [0 to wmax]

%  pha = Phase response in radians over [0 to wmax]

%    w = array of 500 frequency samples between [0 to wmax]

%    b = Numerator polynomial coefficents of Ha(s)

%    a = Denominator polynomial coefficents of Ha(s)

% wmax = Maximum frequency in rad/sec over which response is desired

%

w = [0:1:500]*wmax/500;

H = freqs(b,a,w);

mag = abs(H);

db = 20*log10((mag+eps)/max(mag));

pha = angle(H);

