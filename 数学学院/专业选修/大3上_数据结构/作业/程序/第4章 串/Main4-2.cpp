 // main4-2.cpp 检验bo4-2.cpp的主程序
 #include"c1.h"
 #include"c4-2.h" // 串的堆分配存储结构
 #include"bo4-2.cpp" // 串采用堆分配存储结构的基本操作(12个)
 typedef HString String; // 定义抽象数据类型String为HString类型
 #include"func4-1.cpp" // 与存储结构无关的两个基本操作
 void main()
 {
   int i;
   char c,*p="God bye!",*q="God luck!";
   HString t,s,r;
   InitString(t); // HString类型必须初始化
   InitString(s);
   InitString(r);
   StrAssign(t,p); // 将字符串p的内容转成HString类型，赋给t
   printf("串t为");
   StrPrint(t); // 输出串t
   printf("串长为%d，串空否？%d(1:空 0:否)\n",StrLength(t),StrEmpty(t));
   StrAssign(s,q); // 将字符串q的内容转成HString类型，赋给s
   printf("串s为");
   StrPrint(s); // 输出串s
   i=StrCompare(s,t); // 比较串s和串t的大小
   if(i<0)
     c='<';
   else if(i==0)
     c='=';
   else
     c='>';
   printf("串s%c串t\n",c);
   Concat(r,t,s); // 连接串t和串s，得到串r
   printf("串t连接串s产生的串r为");
   StrPrint(r); // 输出串r
   StrAssign(s,"oo"); // 将字符串"oo"转成HString类型，赋给s
   printf("串s为");
   StrPrint(s); // 输出串s
   StrAssign(t,"o"); // 将字符串"o"转成HString类型，赋给t
   printf("串t为");
   StrPrint(t); // 输出串t
   Replace(r,t,s); // 将串r中和串t相同的子串用串s代替
   printf("把串r中和串t相同的子串用串s代替后，串r为");
   StrPrint(r); // 输出串r
   ClearString(s); // 清空串s
   printf("串s清空后，串长为%d，空否？%d(1:空 0:否)\n",StrLength(s),StrEmpty(s));
   SubString(s,r,6,4); // 生成的串s为从串r的第6个字符起的4个字符
   printf("串s为从串r的第6个字符起的4个字符，长度为%d，串s为",s.length);
   StrPrint(s); // 输出串s
   StrCopy(t,r); // 由串r复制得串t
   printf("由串r复制得串t，串t为");
   StrPrint(t); // 输出串t
   StrInsert(t,6,s); // 在串t的第6个字符前插入串s
   printf("在串t的第6个字符前插入串s后，串t为");
   StrPrint(t); // 输出串t
   StrDelete(t,1,5); // 从串t的第1个字符起删除5个字符
   printf("从串t的第1个字符起删除5个字符后，串t为");
   StrPrint(t); // 输出串t
   printf("%d是从串t的第1个字符起，和串s相同的第1个子串的位置\n",Index(t,s,1));
   printf("%d是从串t的第2个字符起，和串s相同的第1个子串的位置\n",Index(t,s,2));
   DestroyString(t); // 销毁操作同清空
 }
