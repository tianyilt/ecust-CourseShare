load data.txt
i1=degtorad(data(:,1));%»Î…‰∑¥…‰Ω«
i2=degtorad(data(:,2));%’€…‰Ω«
p1=data(:,3);%’€…‰
s1=data(:,4);
p2=data(:,5);%∑¥…‰
s2=data(:,6);
p=248;s=248;
fanshes=sqrt(s2./s);%∑¥…‰
fanshep=sqrt(p2./p);
zheshes=sqrt(s1./s);%’€…‰
zheshep=sqrt(p1./p);
yishi=-sin(i1-i2)./sin(i1+i2)
ershi=tan(i1-i2)./tan(i1+i2)
sanshi=-2.*sin(i2).*cos(i1)./sin(i1+i2)
sishi=2.*sin(i2).*cos(i1)./sin(i1+i2)./cos(i1-i2)