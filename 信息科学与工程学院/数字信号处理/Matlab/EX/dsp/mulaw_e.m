function [sq] = mulaw_e(yq,B,mu)

% mu-law expander

% ---------------

% [sq] = mulaw_e(yq,B,mu)

% sq = expanded quantized signal

% yq = quantized input in integers: 0 <=yq <= 2^B-1

%  B = bits/sample

% mu = compander parameter

%

swing = (2^B-1)/2;

yq = ((yq-swing)/swing);

if mu == 0

  sq = yq;

else

  sq = (((1+mu).^(abs(yq))-1)/mu).*sign(yq);

end

