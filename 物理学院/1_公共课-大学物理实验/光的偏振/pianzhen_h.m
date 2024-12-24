close all
figure
theta=linspace(0,360,37);
theta=theta;
theta=deg2rad(theta);
load data_h.txt
I1=[data_h(:,1)' data_h(1,1)];
I2=[data_h(:,2)' data_h(1,2)];
%polar(theta,I1,'-r');
polar(theta,I2,'b-');