function [y] = mulaw_c(s,mu)

% mu-law compressor

% -----------------

% [y] = mulaw_c(s,mu)

%  y = compressed output signal

%  s = zero-mean nomalized signal between -1 and 1

% mu = parameter mu

%

if mu == 0 

   y = s;

else

   y = (log(1+mu*abs(s))/(log(1+mu))).*sign(s);

end