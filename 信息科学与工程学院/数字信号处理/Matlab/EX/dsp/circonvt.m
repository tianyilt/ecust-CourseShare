function y = circonvt(x1,x2,N)

% N-point circular convolution between x1 and x2: (time-domain)

% -------------------------------------------------------------

% [y] = circonvt(x1,x2,N)

%  y = output sequence containing the circular convolution

% x1 = input sequence of length N1 <= N

% x2 = input sequence of length N2 <= N

%  N = size of circular buffer

%  Method: y(n) = sum (x1(m)*x2((n-m) mod N))



% Check for length of x1

if length(x1) > N

        error('N must be >= the length of x1')

end



% Check for length of x2

if length(x2) > N

        error('N must be >= the length of x2')

end



x1=[x1 zeros(1,N-length(x1))];

x2=[x2 zeros(1,N-length(x2))];



m = [0:1:N-1];

x2 = x2(mod(-m,N)+1);

H = zeros(N,N);



for n = 1:1:N

	H(n,:) = cirshftt(x2,n-1,N);

end



y = x1*H';

