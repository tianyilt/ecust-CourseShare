function xiti1002
tic
t=[25 100 150 200 250 300 350 400 450 500];
Q=quad(@myfun,t(1),t(end))
toc
function q=myfun(t,sp)
t=[25 100 150 200 250 300 350 400 450 500]; 
Cp=[40.5 45.6 48.3 51.4 55.3 56.4 58.9  60.1 63.2 64.9];
sp=spline(t,Cp);
q=ppval(sp,t);    %q=fnval(sp,t)
