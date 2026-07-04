% PWSK_DSP TOOLBOX

% Matlab functions to accompany the companian book

%     Digital Signal Processing using Matlab

%             by Proakis and Ingle

%             Publisher: PWS-Kent

%             Copyright 1995

% Version 1.00

%

% Discrete Signals and Systems

%       conv_m          - Modified linear convolution routine

%       conv_tp         - Linaer convolution using Toeplitz matrix

%       evenodd         - Real signal decomposition into even and odd parts

%       impseq          - Generates x(n) = delta(n-n0); n1 <= n,n0 <= n2

%       sigadd          - signal addition operation

%       sigfold         - signal folding operation

%       sigmult         - signal multiplication operation

%       sigshift        - signal shifting operation

%       stepseq         - Generates x(n) = u(n-n0); n1 <= n,n0 <= n2

%

% Discrete-Time Fourier Transform

%

% The z-Transform

%       pfe2rfz         - Rational function from Partial Fraction Expansions in z-Domain

%       rf2pfez         - Partial Fraction Expansion from rational function in z-Domain

%

% Discrete Fourier Transform

%       circevod        - real signal decomposition into circular-even and circular-odd parts

%       circonvt        - circular convolution in the time-domain

%       cirshftt        - Circular shift in the time-domain

%       dfs             - Computes Discrete Fourier Series Coefficients

%       dft             - Computes Discrete Fourier Transform

%       hsolpsav        - High-speed Overlap-Save method of block convolutions using FFT

%       idfs            - Computes Inverse Discrete Fourier Series

%       idft            - Computes Inverse Discrete Transform

%       mod             - Computes m = n mod N = ((n))

%       ovrlpsav        - Overlap-Save method of block convolution

%

% Digital Filter Structures

%       cas2dir         - CASCADE-to-DIRECT form conversion

%       casfiltr        - CASCADE form realization of IIR and FIR filters

%       cplxcomp        - Compares two complex pairs

%       dir2cas         - DIRECT-form to CASCADE-form conversion

%       dir2fs          - Direct form to Frequency Sampling form conversion

%       dir2ladr        - IIR Direct form to pole-zero Lattice/Ladder form Conversion

%       dir2latc        - FIR Direct form to All-Zero Lattice form Conversion

%       dir2par         - DIRECT-form to PARALLEL-form conversion

%       ladr2dir        - Lattice/Ladder form to IIR Direct form Conversion

%       ladrfilt        - LATTICE/LADDER form realization of IIR filters

%       latc2dir        - All-Zero Lattice form to FIR Direct form Conversion

%       latcfilt        - LATTICE form realization of FIR filters

%       par2dir         - PARALLEL-to-DIRECT form conversion

%       parfiltr        - PARALLEL form realization of IIR filters

%

% FIR Filter Design

%       blackman        - Blackman window function

%       freqz_m         - Modified version of freqz routine

%       Hr_Type1        - Computes Amplitude response of Type-1 LP FIR filter

%       Hr_Type2        - Computes Amplitude response of Type-2 LP FIR filter

%       Hr_Type3        - Computes Amplitude response of Type-3 LP FIR filter

%       Hr_Type4        - Computes Amplitude response of Type-4 LP FIR filter

%       ideal_lp        - Ideal LowPass filter impulse response computation

%

% IIR Filter Design

%       afd_butt        - Analog Lowpass Filter Design: Butterworth

%       afd_chb1        - Analog Lowpass Filter Design: Chebyshev-1

%       afd_chb2        - Analog Lowpass Filter Design: Chebyshev-2

%       afd_elip        - Analog Lowpass Filter Design: Elliptic

%       cheb1hpf        - IIR Highpass filter design using Chebyshev-1 prototype

%       freqs_m         - Modified version of freqs routine

%       imp_invr        - Impulse Invariance Transformation from Analog to Digital Filter

%       sdir2cas        - DIRECT-form to CASCADE-form conversion in s-plane

%       u_buttap        - Unnormalized Butterworth Analog Lowpass Filter Prototype

%       u_chb1ap        - Unnormalized Chebyshev-1 Analog Lowpass Filter Prototype

%       u_chb2ap        - Unnormalized Chebyshev-2 Analog Lowpass Filter Prototype

%       u_elipap        - Unnormalized Elliptic Analog Lowpass Filter Prototype

%       zmapping        - Frequency-band transformation in the z-domain

%

% Adaptive Filtering

%       lms             - LMS Algorithm for Coefficient Adjustment

%

% Digital Communications

%       mulaw_c         - mu-law compressor

%       mulaw_e         - mu-law expander

%       quantize        - Quantize signal to B bits

%

% Miscellaneous

%	contents	- contents file (you are reading it)

%       db2delta        - Conversion from Relative dB specs to Absolute delta specs.

%       delta2db        - Conversion from Absolute delta specs to Relative dB specs

