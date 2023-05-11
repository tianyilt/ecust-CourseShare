function Cha6demo6    
CA10=0.4; CA20=0.2; CA30=0.1;
stoptime=10;
[t,y]=ode45(@CSTR,[0 stoptime],[CA10 CA20 CA30]);
plot(t,y(:,1),'k--',t,y(:,2),'b:',t,y(:,3),'r-')
legend('CA_1','CA_2','CA_3')
xlabel('Time (min)')
ylabel('Concentration')
 % ------------------------------------------------------
function dCdt=CSTR(t,y)
CA0=1.8; 
k=0.5; tau=2; 
CA1=y(1);
CA2=y(2);
CA3=y(3);
dCA1dt=(CA0-CA1)/tau-k*CA1;
dCA2dt=(CA1-CA2)/tau-k*CA2;
dCA3dt=(CA2-CA3)/tau-k*CA3;
dCdt = [dCA1dt; dCA2dt; dCA3dt];
