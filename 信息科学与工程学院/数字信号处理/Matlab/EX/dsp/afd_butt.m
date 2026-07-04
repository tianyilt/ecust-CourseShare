function [b,a] = afd_butt(Wp,Ws,Rp,As);

% Analog Lowpass Filter Design: Butterworth

% -----------------------------------------

% [b,a] = afd_butt(Wp,Ws,Rp,As);

%  b = Numerator coefficients of Ha(s)

%  a = Denominator coefficients of Ha(s)

% Wp = Passband edge frequency in rad/sec; Wp > 0

% Ws = Stopband edge frequency in rad/sec; Ws > Wp > 0

% Rp = Passband ripple in +dB; (Rp > 0)

% As = Stopband attenuation in +dB; (As > 0)

%

if Wp <= 0

        error('Passband edge must be larger than 0')

end

if Ws <= Wp

        error('Stopband edge must be larger than Passband edge')

end

if (Rp <= 0) | (As < 0)

        error('PB ripple and/or SB attenuation ust be larger than 0')

end



N = ceil((log10((10^(Rp/10)-1)/(10^(As/10)-1)))/(2*log10(Wp/Ws)));

fprintf('\n*** Butterworth Filter Order = %2.0f \n',N)

OmegaC = Wp/((10^(Rp/10)-1)^(1/(2*N)));

[b,a]=u_buttap(N,OmegaC);



