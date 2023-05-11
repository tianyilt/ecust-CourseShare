function Cha6demo8
CA0=0.36;T0=315;
tao=73.1;
opt1=odeset('OutputFcn','odephas2');
[t,y]=ode15s(@CSTR,[CA0,T0],[0 20*tao],opt1,tao);
figure
title('Solved by default settings')
plotyy(t,y(:,1),t,y(:,2))
opt2=odeset('OutputFcn','odephas2','RelTol',sqrt(eps),'AbsTol',sqrt(eps));
figure
[t2,y2]=ode15s(@CSTR,[CA0,T0],[0 20*tao],opt2,tao);
title('Solved by adjusted setting')
figure
plotyy(t2,y2(:,1),t2,y2(:,2))
function dy=CSTR(t,y,tao)
Tf=298;Ta=298;Tm=298;
Cp=4.0;CAf=2.0;km=0.004;E=1.5e4;rhou=1e3;
deltaH=-2.2e5;K=340;
k=km*exp(-E*(1/y(2)-1/Tm));
dC=(CAf-y(1))/tao-k*y(1);
dT=K/(rhou*Cp)*(Ta-y(2))+(Tf-y(2))/tao-deltaH/(rhou*Cp)*k*y(1);
dy=[dC;dT];
