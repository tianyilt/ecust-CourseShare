 // algo4-1.cpp 实现算法4.6～4.8的程序
 #include"c1.h"
 #include"c4-1.h" // 串的定长顺序存储结构
 #include"bo4-1.cpp" // 定长顺序存储结构的基本操作(12个)

 void get_next(SString T,int next[])
 { // 求模式串T的next函数值并存入数组next。算法4.7
   int i=1,j=0;
   next[1]=0; // T的第1个字符与主串“失配”时，主串的下一字符与T的第1个字符比较
   while(i<T[0]) // 当T[0]>1时，next[2]=1
     if(j==0||T[i]==T[j]) // 初态或两字符相等
     { ++i; // 各+1继续向后比较
       ++j;
       next[i]=j; // 主串和T在第i个字符不匹配时，前j-1个字符是匹配的，只须与第j个字符比较
     }
     else // 两字符不等
       j=next[j]; // j减小到前面字符相等之处
 }

 void get_nextval(SString T,int nextval[])
 { // 求模式串T的next函数修正值并存入数组nextval。算法4.8
   int i=1,j=0;
   nextval[1]=0; // T的第1个字符与主串“失配”，主串的下一字符与T的第1个字符比较
   while(i<T[0])
     if(j==0||T[i]==T[j])
     { ++i;
       ++j;
       if(T[i]!=T[j]) // 此处与算法4.7不同
         nextval[i]=j;
       else
         nextval[i]=nextval[j];
     }
     else
       j=nextval[j]; // j减小到前面字符相等之处
 }

 int Index_KMP(SString S,SString T,int pos,int next[])
 { // 利用模式串T的next数组求T在主串S中第pos个字符之后的位置的KMP算法。
   // 其中，T非空，1≤pos≤StrLength(S)。算法4.6
   int i=pos,j=1; // 初始位置
   while(i<=S[0]&&j<=T[0]) // i和j分别都未超出主串S和模式串T的范围
     if(j==0||S[i]==T[j]) // 继续比较后继字符
     { ++i;
       ++j;
     }
     else // 模式串向右移动
       j=next[j];
   if(j>T[0]) // 匹配成功
     return i-T[0];
   else
     return 0;
 }

 void main()
 {
   int i,*p;
   SString s1,s2; // 以教科书算法4.8之上的数据为例
   StrAssign(s1,"aaabaaaab"); // 由"aaabaaaab"生成主串s1
   printf("主串为");
   StrPrint(s1); // 输出串s1
   StrAssign(s2,"aaaab"); // 由"aaaab"生成子串s2
   printf("子串为");
   StrPrint(s2); // 输出串s2
   p=(int*)malloc((StrLength(s2)+1)*sizeof(int)); // 生成s2的next数组，[0]不用
   get_next(s2,p); // 利用算法4.7，求得next数组，存于p中
   printf("子串的next数组为");
   for(i=1;i<=StrLength(s2);i++)
     printf("%d ",*(p+i));
   printf("\n");
   i=Index_KMP(s1,s2,1,p); // 利用算法4.6求得串s2在s1中首次匹配的位置i
   if(i)
     printf("主串和子串在第%d个字符处首次匹配\n",i);
   else
     printf("主串和子串匹配不成功\n");
   get_nextval(s2,p); // 利用算法4.8，求得nextval数组，存于p中
   printf("子串的nextval数组为");
   for(i=1;i<=StrLength(s2);i++)
     printf("%d ",*(p+i));
   printf("\n");
   printf("主串和子串在第%d个字符处首次匹配\n",Index_KMP(s1,s2,1,p));
 }
