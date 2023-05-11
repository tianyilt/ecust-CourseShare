A=[1 2 3; 4 5 6; 7 8 9];
B=[A+0.1 A+0.2; A+0.3 A+0.4]

pause()

B=A*2;
C=cat(2,A,B)
D=cat(1,A,B)

pause()

A=[1 2;3 4];
B = repmat(A, 2, 3)