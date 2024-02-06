%==================================================================
clear
clc
format short
syms t
%------------------------------------------------------------------
x = (0:0.001:0.08);
% define the variables
alpha = 0.89*10^(-6); %热扩散率
time = 7200; %时间
T0 = 20; %初温
TW = 1450; %末温
% calculate Eata
Eata = x/2/sqrt(a*time); %无量纲参数
% calculate erf
for n = 1:length(Eata)
    y = 2/sqrt(pi)*exp(-t^2);
    f = int(y,t,0,Eata(n)); %积分
    erf(n) = f;
end
% calculate temperature
T = vpa(TW+erf*(T0-TW));
% extract the results
display(['x =',num2str(x)]);
fprintf('T = %3.2f\n',double(T))
%-------------------------------------------------------------------
% draw the picture
plot(T,x,'linewidth',2);
%set(gca,'YDIR','reserve')
hold on
plot(T,x,'o','Markersize',6);
xlabel('{\itT}/K','Fontname','Times New Roman','fontsize',11)
ylabel('{\itx}/m','Fontname','Times New Roman','fontsize',11)
set(gca,'Fontname','Times New Roman','FontSize',11);
%===================================================================