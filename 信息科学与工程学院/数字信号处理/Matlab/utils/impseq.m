function [x, n] = impseq(np, ns, nf)
    % Generates x(n) = delta(n-np); ns <= n <= nf
    % -------------------------------------------
    % [x, n] = impseq(np, ns, nf)
    % x = generated sequence over ns <= n <= nf
    % n = sample points over ns <= n <= nf
    % np = position of impulse
    % ns = starting index of n
    % nf = ending index of n

    if ((np < ns) || (np > nf) || (ns > nf))
        error('arguments must satisfy ns <= np <= nf');
    end

    n = [ns:nf];
    x = [(n - np) == 0];
