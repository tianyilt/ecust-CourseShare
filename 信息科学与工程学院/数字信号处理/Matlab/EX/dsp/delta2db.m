function [Rp,As] = delta2db(delta1,delta2)

% Conversion from Absolute delta specs to Relative dB specs

% ---------------------------------------------------------

% [Rp,As] = delta2db(delta1,delta2)

% Rp = Passband ripple

% As = Stopband attenuation

% d1 = Passband tolerance

% d2 = Stopband tolerance

%

Rp = -20*log10((1-delta1)/(1+delta1));

As = -20*log10(delta2/(1+delta1));

