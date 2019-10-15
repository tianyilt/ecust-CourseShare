G={[1 0;0 1],[0 1;-1 0],[-1 0;0 -1],[0 -1;1 0],[1 0;0 -1],[-1 0;0 1],[0 -1;-1 0],...
    [0 1;1 0]};
A=['a','b','c','d','e','f','g','h'];
for i=1:8
    for j=1:8
        for k=1:8
            if cell2mat(G(i))*cell2mat(G(j))==cell2mat(G(k))
                fprintf('%s ',A(k));
            end
        end
    end
    fprintf('\n');
end