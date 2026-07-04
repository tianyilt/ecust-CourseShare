function [b,a] = afd_chb1(Wp,Ws,Rp,As);

% Analog Lowpass Filter Design: Chebyshev-1

% -----------------------------------------

% [b,a] = afd_chb1(Wp,Ws,Rp,As);

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



ep = sqrt(10^(Rp/10)-1);

A = 10^(As/20);

OmegaC = Wp;

OmegaR = Ws/Wp;

g = sqrt(A*A-1)/ep;

N = ceil(log10(g+sqrt(g*g-1))/log10(OmegaR+sqrt(OmegaR*OmegaR-1)));

fprintf('\n*** Chebyshev-1 Filter Order = %2.0f \n',N)

[b,a]=u_chb1ap(N,Rp,OmegaC);



