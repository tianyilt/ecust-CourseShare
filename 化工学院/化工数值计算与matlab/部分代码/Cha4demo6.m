t=linspace(0,pi/2,4);
x=cos(t);y=sin(t);
xx=linspace(0,1,40);
plot(x,y,'s',xx,[pchip(x,y,xx);spline(x,y,xx)])
grid on, axis equal
legend('Orignal data','pchip','spline')
