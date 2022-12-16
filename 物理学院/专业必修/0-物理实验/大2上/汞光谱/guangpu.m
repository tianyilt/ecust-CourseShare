angle_green=[9.441666667
9.429166667
9.445833333
9.45
9.445833333
9.45];
angle_iyellow=[9.979166667
9.983333333
9.9625];
angle_oyellow=[10.02083333
10.02083333
10.00833333];
angle_purple=[7.529166667
7.5375
7.516666667];
delta_yi=0.03333;
[A_g,U_g]=uncertainty(angle_green,delta_yi);
[A_i,U_i]=uncertainty(angle_iyellow,delta_yi);
[A_o,U_o]=uncertainty(angle_oyellow,delta_yi);
[A_p,U_p]=uncertainty(angle_purple,delta_yi);
%绿光波长
L_g=546.1;
%光栅常数
d=L_g/sind(A_g);
%其他光的波长
L_i=L_g*sind(A_i)/sind(A_g);
L_o=L_g*sind(A_o)/sind(A_g);
L_p=L_g*sind(A_p)/sind(A_g);
d
L_i
L_o
L_p
fprintf('标准值577.0,579.1,435.8')
d_i=(577-L_i)/577*100
d_o=(579.1-L_o)/579.1*100
d_p=(435.8-L_p)/435.8*100
d_d=L_g/sind(A_g)^2*cosd(A_g)*U_g





