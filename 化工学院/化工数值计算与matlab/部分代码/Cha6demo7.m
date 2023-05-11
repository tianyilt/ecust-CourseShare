function Cha6demo7
figure
ode23s(@fun,[0,100],[0;1])
figure,
ode45(@fun,[0,100],[0;1])
function f=fun(x,y)
dy1dx = 0.04*(1-y(1))-(1-y(2)).*y(1)+0.0001*(1-y(2)).^2; 
dy2dx = -1e4*dy1dx + 3000*(1-y(2)).^2;
f = [dy1dx; dy2dx];
