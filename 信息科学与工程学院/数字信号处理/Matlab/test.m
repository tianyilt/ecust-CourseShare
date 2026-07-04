xn = [1 -1 1 -1];
N = 4;
Xk = fft(xn, N);
Yk = (real(Xk)) .* (real(Xk));
yn = ifft(Yk, N);

% disp(yn);


valueset = {'la-', 'ci-', 'do', 're', 'mi', 'fa', 'so'};
for i = 1:length(valueset)
    disp(valueset{i});
end

max(xn, yn)