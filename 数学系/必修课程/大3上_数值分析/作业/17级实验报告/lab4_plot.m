clc;clear;
%n=10;%numbers of interval
n=20;
x=[-1:2/n:1];%interpolation data
y=[];%interpolation data
for i=1:1:length(x)
    y=[y 1/(1+25*x(i)^2)];
end
N=my_newton(x,y);
t=linspace(-1,1,1001);%plotting data
Y_Newton=polyval(N,t);
H=plot(t,Y_Newton,'r-');%newton
hold on;
H1=plot(x,y,'k*');
b=[0.0740,-0.0740];
spline_matrix=cubic_spline_interplotion(x',y',b);
for i=1:1:n%loop to plot the spline func
    tmp_t=linspace(x(i),x(i+1),1001);
    H2=plot(tmp_t,polyval(spline_matrix(i,:),tmp_t),'b-.');
end
legend([H,H1,H2],{'Newton fit','points','spline fit'});