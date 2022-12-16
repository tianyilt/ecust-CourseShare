clear all;
w=exp(2*pi/3*i);
w2=w.^2;
G={[1 0;0 1],[w 0;0 w2],[w2 0;0 w],[0 1;1 0],[0 w2;w 0],[0 w;w2 0]};
A=['a','b','c','d','e','f','g','h'];

for i0=1:6
    for j=1:6
        for k=1:6
            if cell2mat(G(i0))*cell2mat(G(j))==cell2mat(G(k))
                fprintf('%s ',A(k));
            elseif round(real(cell2mat(G(i0))*cell2mat(G(j))))==round(real(cell2mat(G(k))))
                fprintf('%s ',A(k));
            end
        end
    end
    fprintf('\n');
end