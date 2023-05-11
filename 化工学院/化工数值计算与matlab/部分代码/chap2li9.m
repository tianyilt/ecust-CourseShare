A=magic(4);
B=sum(A);
C=sum(A,2);
D=trace(A);
E=trace(rot90(A));
F=length(find(B==34));
G=length(find(C==34));
if F==4&&G==4&&D==34&&E==34
    disp('It is a magic matrix')
else
    disp('It is not a magic matrix')
end
