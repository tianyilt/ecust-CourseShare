 // func4-1.cpp 与存储结构无关的两个基本操作
 int Index(String S,String T,int pos) // 算法4.1
 { // T为非空串。若主串S中第pos个字符之后存在与T相等的子串，
   // 则返回第一个这样的子串在S中的位置；否则返回0
   int n,m,i;
   String sub;
   InitString(sub); // 新增
   if(pos>0)
   { n=StrLength(S); // 主串S的长度
     m=StrLength(T); // 模式串T的长度
     i=pos;
     while(i<=n-m+1) // i从串S的pos到倒数第m个
     { SubString(sub,S,i,m); // 子串sub是从主串S的第i个字符起，长度为m的子串
       if(StrCompare(sub,T)!=0) // 子串sub不等于模式串T
         ++i; // 继续向后比较
       else // 子串sub等于模式串T
         return i; // 返回模式串T的第1个字符在主串S中的位置
     }
   }
   return 0; // 主串S中不存在与模式T相等的子串
 }

 Status Replace(String &S,String T,String V)
 { // 初始条件：串S、T和V存在，串T是非空串
   // 操作结果：用串V替换主串S中出现的所有与串T相等的不重叠的子串
   int i=1; // 从串S的第一个字符起查找串T
   Status k;
   if(StrEmpty(T)) // T是空串
     return ERROR;
   while(i)
   { i=Index(S,T,i); // 结果i为从上一个i之后找到的子串T的位置
     if(i) // 串S中存在串T
     { StrDelete(S,i,StrLength(T)); // 删除串T
       k=StrInsert(S,i,V); // 在原串T的位置插入串V
       if(!k) // 不能完全插入(定长顺序存储结构有可能发生这种情况)
         return ERROR;
       i+=StrLength(V); // 在插入的串V后面继续查找串T
     }
   };
   return OK;
 }
