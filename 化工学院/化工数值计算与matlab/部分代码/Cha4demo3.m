function Cha4demo3
x=1:6;
y=[16 18 21 17 15 12];
xi=0.75:0.1:6.25;
y1=interp1(x,y,xi,'nearest');
y2=interp1(x,y,xi);
y3=interp1(x,y,xi,'pchip')
y4=interp1(x,y,xi,'spline')
subplot(2,2,1)
plot(x,y,'o',xi,y1,'-'),title('Nearest')
subplot(2,2,2)
plot(x,y,'o',xi,y2,'-'),title('Linear')
subplot(2,2,3)
plot(x,y,'o',xi,y3,'-'),title('Pchip')
subplot(2,2,4)
plot(x,y,'o',xi,y4,'-'),title('Spline')
