 // main4-1.cpp 检验bo4-1.cpp的主程序
 #include"c1.h"
 #include"c4-1.h" // 串的定长顺序存储结构
 #include"bo4-1.cpp" // 定长顺序存储结构的基本操作(12个)
 typedef SString String; // 定义抽象数据类型String为SString类型
 #include"func4-1.cpp" // 与存储结构无关的两个基本操作

 void main()
 {
   int i,j;
   Status k;
   char s,c[MAX_STR_LEN+1]; // c中包括串结束符
   SString t,s1,s2;
   printf("请输入串s1：");
   gets(c); // 由键盘输入字符串给c
   k=StrAssign(s1,c); // 将字符串c转为SString类型，存入s1
   if(!k) // 本例由于c的长度所限，串长超过MAX_STR_LEN的现象不会发生
   { printf("串长超过MAX_STR_LEN(=%d)\n",MAX_STR_LEN);
     exit(OVERFLOW);
   }
   printf("串长为%d，串空否？%d(1:是 0:否)\n",StrLength(s1),StrEmpty(s1));
   StrCopy(s2,s1); // 复制串s1生成串s2
   printf("复制s1生成的串为");
   StrPrint(s2); // 输出串s2
   printf("请输入串s2：");
   gets(c); // 由键盘输入字符串给c
   StrAssign(s2,c); // 将字符串c转为SString类型，存入s1。可不要返回值
   i=StrCompare(s1,s2); // 比较串s1和串s2
   if(i<0)
     s='<';
   else if(i==0)
     s='=';
   else
     s='>';
   printf("串s1%c串s2\n",s);
   k=Concat(t,s1,s2); // 由串s1连接串s2生成串t
   printf("串s1连接串s2得到的串t为");
   StrPrint(t); // 输出串t
   if(k==FALSE)
     printf("串t有截断\n");
   ClearString(s1); // 清空串s1
   printf("清为空串后，串s1为");
   StrPrint(s1); // 输出串s1
   printf("串长为%d，串空否？%d(1:是 0:否)\n",StrLength(s1),StrEmpty(s1));
   printf("求串t的子串，请输入子串的起始位置,子串长度：");
   scanf("%d,%d",&i,&j);
   k=SubString(s2,t,i,j); // 串s2为串t的第i个字符起，长度为j的子串
   if(k) // 串s2存在
   { printf("子串s2为");
     StrPrint(s2); // 输出串s2
   }
   printf("从串t的第pos个字符起，删除len个字符，请输入pos,len：");
   scanf("%d,%d",&i,&j);
   StrDelete(t,i,j); // 将串t的第i个字符起的j个字符删除
   printf("删除后的串t为");
   StrPrint(t); // 输出串t
   i=StrLength(s2)/2; // i为串s2长度的一半取整
   StrInsert(s2,i,t); // 在串s2的第i个字符之前插入串t
   printf("在串s2的第%d个字符之前插入串t后，串s2为",i);
   StrPrint(s2); // 输出串s2
   i=Index1(s2,t,1); // 从串s2的第1个字符起查找串t
   printf("s2的第%d个字符起和t第一次匹配\n",i);
   i=Index(s2,t,1); // 从串s2的第1个字符起查找串t(另一种方法)
   printf("s2的第%d个字符起和t第一次匹配\n",i);
   SubString(t,s2,1,1); // 串t为串s2的第1个字符
   printf("串t为");
   StrPrint(t); // 输出串t
   Concat(s1,t,t); // 串s1为2个串t
   printf("串s1为");
   StrPrint(s1); // 输出串s1
   k=Replace(s2,t,s1); // 将串s2中的所有不重叠的串t，用串s1替换
   if(k) // 替换成功
   { printf("用串s1取代串s2中和串t相同的不重叠的串后，串s2为");
     StrPrint(s2); // 输出串s2
   }
   DestroyString(s2); // 销毁操作与清空操作作用相同
 }
