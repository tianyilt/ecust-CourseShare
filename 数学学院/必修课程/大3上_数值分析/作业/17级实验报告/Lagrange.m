function p=Lagrange(X,Y)
Len_y=length(Y);
Len_x=length(X);
if Len_y~=Len_x
    errorlog('gg');
else
    syms x;
    p=0;
    for i=1:Len_y
        q=1;
        for j=1:Len_x
            if j~=i
                q=q*(x-X(j))/(X(i)-X(j));
            end
        end
        p=p+q*Y(i);
    end
    
    simplify(p);
    sprintf('长成这幅鬼样子: ')
    p=collect(p);
    p=vpa(p,6)
    
end
end
