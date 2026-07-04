function [b,a] = afd_elip(Wp,Ws,Rp,As);

% Analog Lowpass Filter Design: Elliptic

% --------------------------------------

% [b,a] = afd_elip(Wp,Ws,Rp,As);

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

k = Wp/Ws;

k1 = ep/sqrt(A*A-1);

capk = ellipke([k.^2 1-k.^2]); % Version 4.0 code

capk1 = ellipke([(k1 .^2) 1-(k1 .^2)]); % Version 4.0 code

N = ceil(capk(1)*capk1(2)/(capk(2)*capk1(1)));

fprintf('\n*** Elliptic Filter Order = %2.0f \n',N)

[b,a]=u_elipap(N,Rp,As,OmegaC);