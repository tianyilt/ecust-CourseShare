 // bo4-2.cpp 串采用堆分配存储结构(由c4-2.h定义)的基本操作(12个)。包括算法4.4

 #define DestroyString ClearString // DestroyString()与ClearString()作用相同

 void InitString(HString &S)
 { // 初始化(产生空串)字符串S。新增
   S.length=0;
   S.ch=NULL;
 }

 void ClearString(HString &S)
 { // 将S清为空串。在教科书第77页
   free(S.ch); // 释放S.ch所指空间
   InitString(S); // 初始化串S
 }

 void StrAssign(HString &T,char* chars)
 { // 生成一个其值等于串常量chars的串T。在教科书第76页
   int i,j;
   if(T.ch) // T指向某存储单元
     free(T.ch); // 释放T原有存储空间
   i=strlen(chars); // 求chars的长度i
   if(!i) // chars的长度为0
     InitString(T); // 生成空串
   else // chars的长度不为0
   { T.ch=(char*)malloc(i*sizeof(char)); // 分配串存储空间
     if(!T.ch) // 分配串存储空间失败
       exit(OVERFLOW);
     for(j=0;j<i;j++) // 分配串存储空间成功后，复制串chars[]到串T
       T.ch[j]=chars[j];
     T.length=i; // 更新串T的长度
   }
 }

 void StrCopy(HString &T,HString S)
 { // 初始条件：串S存在。操作结果：由串S复制得串T
   int i;
   if(T.ch) // 串T不空
     free(T.ch); // 释放串T原有存储空间
   T.ch=(char*)malloc(S.length*sizeof(char)); // 分配串存储空间
   if(!T.ch) // 分配串存储空间失败
     exit(OVERFLOW);
   for(i=0;i<S.length;i++) // 从第1个字符到最后一个字符
     T.ch[i]=S.ch[i]; // 逐一复制字符
   T.length=S.length; // 复制串长
 }

 Status StrEmpty(HString S)
 { // 初始条件：串S存在。操作结果：若串S为空，则返回TRUE；否则返回FALSE
   if(S.length==0&&S.ch==NULL) // 空串标志
     return TRUE;
   else
     return FALSE;
 }

 int StrCompare(HString S,HString T)
 { // 若串S>串T，则返回值>0；若S=T，则返回值=0；若S<T，则返回值<0。在教科书第77页
   int i;
   for(i=0;i<S.length&&i<T.length;++i) // 在有效范围内
     if(S.ch[i]!=T.ch[i]) // 逐一比较字符
       return S.ch[i]-T.ch[i]; // 不相等，则返回2字符ASCII码之差
   return S.length-T.length; // 在有效范围内，字符相等，但长度不等，返回长度之差
 }

 int StrLength(HString S)
 { // 返回串S的元素个数，称为串的长度。在教科书第77页
   return S.length;
 }

 void Concat(HString &T,HString S1,HString S2)
 { // 用串T返回由串S1和串S2连接而成的新串。在教科书第77页
   int i;
   if(T.ch) // 串T不空
     free(T.ch); // 释放串T原有存储空间
   T.length=S1.length+S2.length; // 串T的长度=串S1的长度+串S2的长度
   T.ch=(char*)malloc(T.length*sizeof(char)); // 分配串T的存储空间
   if(!T.ch) // 分配串存储空间失败
     exit(OVERFLOW);
   for(i=0;i<S1.length;i++) // 将串S1的字符逐一复制给串T
     T.ch[i]=S1.ch[i];
   for(i=0;i<S2.length;i++) // 将串S2的字符逐一复制给串T(接在串S1的字符之后)
     T.ch[S1.length+i]=S2.ch[i];
 }

 Status SubString(HString &Sub,HString S,int pos,int len)
 { // 用Sub返回串S的第pos个字符起长度为len的子串。
   // 其中，1≤pos≤StrLength(S)且0≤len≤StrLength(S)-pos+1。在教科书第77页
   int i;
   if(pos<1||pos>S.length||len<0||len>S.length-pos+1) // pos和len的值超出范围
     return ERROR; // 无法用Sub返回子串
   if(Sub.ch) // 串Sub不空
     free(Sub.ch); // 释放串Sub原有存储空间
   if(!len) // 空子串
     InitString(Sub); // 初始化串Sub
   else // 完整子串
   { Sub.ch=(char*)malloc(len*sizeof(char)); // 分配串Sub的存储空间
     if(!Sub.ch) // 分配串存储空间失败
       exit(OVERFLOW);
     for(i=0;i<=len-1;i++) // 将串S第pos个字符起长度为len的子串的字符逐一复制给串Sub
       Sub.ch[i]=S.ch[pos-1+i];
     Sub.length=len; // 串Sub的长度
   }
   return OK;
 }

 Status StrInsert(HString &S,int pos,HString T) // 算法4.4
 { // 1≤pos≤StrLength(S)+1。在串S的第pos个字符之前插入串T
   int i;
   if(pos<1||pos>S.length+1) // pos不合法
     return ERROR;
   if(T.length) // T非空
   { S.ch=(char*)realloc(S.ch,(S.length+T.length)*sizeof(char)); // 重分S存储空间
     if(!S.ch) // 重新分配串S的存储空间失败
       exit(OVERFLOW);
     for(i=S.length-1;i>=pos-1;--i) // 为插入T而腾出位置
       S.ch[i+T.length]=S.ch[i];
     for(i=0;i<T.length;i++) // 插入T
       S.ch[pos-1+i]=T.ch[i];
     S.length+=T.length; // 更新串S的长度
   }
   return OK;
 }

 Status StrDelete(HString &S,int pos,int len)
 { // 从串S中删除第pos个字符起长度为len的子串
   int i;
   if(S.length<pos+len-1) // pos和len的值超出范围
     return ERROR;
   for(i=pos-1;i<=S.length-len;i++) // 将待删除子串之后的字符逐一前移
     S.ch[i]=S.ch[i+len];
   S.length-=len; // 更新串S的长度
   S.ch=(char*)realloc(S.ch,S.length*sizeof(char)); // 重新分配串S的存储空间(减少)
   return OK;
 }

 void StrPrint(HString S)
 { // 输出字符串S。新增
   int i;
   for(i=0;i<S.length;i++)
     printf("%c",S.ch[i]);
   printf("\n");
 }
