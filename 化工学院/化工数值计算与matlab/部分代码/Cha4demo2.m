function Cha4demo2
x=1:6;y=[16 18 21 17 15 12];
xi=0.5:0.1:6.5;
n=length(x);
v=zeros(size(xi));
for k=1:n
   w=ones(size(xi));
for j=[1:k-1 k+1:n]
 w=(xi-x(j))./(x(k)-x(j)).*w;
end
v=v+w*y(k);
end
plot(x,y,'o',xi,v,'-')
legend('interpolating points','interpolation results')
xlabel('x'),ylabel('y')
