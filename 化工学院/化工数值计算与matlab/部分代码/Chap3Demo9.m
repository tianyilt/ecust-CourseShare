function Chap3Demo9
x0 = [0.05 0.2 0.01];
x = fsolve(@EquiC3,x0);
CAC = x(3)/sum(x)

function f = EquiC3(x)
f1 = x(1)-0.064*(1-x(1)-x(2)-x(3));
f2 = x(2)*(x(2)+x(3))-0.076*(1-x(1)-x(2)-x(3))*(1+x(2)+x(3));
f3 = x(3)*(x(2)+x(3))-0.00012*(1-x(1)-x(2)-x(3))*(1+x(2)+x(3));
f = [f1 f2 f3];
