%ÀíÂÛÖµ
figure
theta1=20;
theta2=linspace(0,360,361);
I=cosd(theta1).^2.*cosd(theta2).^2+sind(theta1).^2.*sind(theta2).^2;
I=I*0.6414;
theta2=deg2rad(theta2);
polar(theta2,I,'-r');
load data.txt
I2=data(:,4)';
hold on
theta3=linspace(0,350,36);
theta3=theta3-70;
theta3=deg2rad(theta3);
polar(theta3,I2,'.')

