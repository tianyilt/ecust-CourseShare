function [yq] = quantize(y,B)

% Quantize signal to B bits

% -------------------------

% [yq] = quantize(y,B)

%    yq = quantized signal in integers: 0 <= yq <= 2^B-1

%     y = input signal

%     B = bits/sample

%

swing = (2^B-1)/2;

yq = round(y*swing+swing);