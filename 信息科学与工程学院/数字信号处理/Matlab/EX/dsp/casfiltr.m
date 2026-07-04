function y = casfiltr(b0,B,A,x);

% CASCADE form realization of IIR and FIR filters

% -----------------------------------------------

% y = casfiltr(b0,B,A,x);

%  y = output sequence

% b0 = gain coefficient of CASCADE form

%  B = K by 3 matrix of real coefficients containing bk's

%  A = K by 3 matrix of real coefficients containing ak's

%  x = input sequence

%

[K,L] = size(B);

N = length(x);

w = zeros(K+1,N);

w(1,:) = x;

for i = 1:1:K

        w(i+1,:) = filter(B(i,:),A(i,:),w(i,:));

end

y = b0*w(K+1,:);



