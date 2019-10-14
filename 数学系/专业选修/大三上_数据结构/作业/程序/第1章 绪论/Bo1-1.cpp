 // bo1-1.cpp 抽象数据类型Triplet和ElemType(由c1-1.h定义)的基本操作(8个)
 Status InitTriplet(Triplet &T,ElemType v1,ElemType v2,ElemType v3)
 { // 操作结果：构造三元组T，依次置T的3个元素的初值为v1，v2和v3。在教科书第12页
   T=(ElemType*)malloc(3*sizeof(ElemType)); // 分配3个元素的存储空间
   if(!T)
     exit(OVERFLOW); // 分配失败则退出
   T[0]=v1,T[1]=v2,T[2]=v3;
   return OK;
 }

 Status DestroyTriplet(Triplet &T)
 { // 操作结果：三元组T被销毁。在教科书第12页
   free(T); // 释放T所指的三元组存储空间
   T=NULL; // T不再指向任何存储单元
   return OK;
 }

 Status Get(Triplet T,int i,ElemType &e)
 { // 初始条件：三元组T已存在，1≤i≤3。操作结果：用e返回T的第i元的值。在教科书第12页
   if(i<1||i>3) // i不在三元组的范围之内
     return ERROR;
   e=T[i-1]; // 将三元组T的第i个元素的值赋给e
   return OK;
 }

 Status Put(Triplet T,int i,ElemType e)
 { // 初始条件：三元组T已存在，1≤i≤3。操作结果：改变T的第i元的值为e。在教科书第12页
   if(i<1||i>3) // i不在三元组的范围之内
     return ERROR;
   T[i-1]=e; // 将e的值赋给三元组T的第i个元素
   return OK;
 }

 Status IsAscending(Triplet T) // 在教科书第13页
 { // 初始条件：三元组T已存在。操作结果：如果T的3个元素按升序排列，则返回1；否则返回0
   return(T[0]<=T[1]&&T[1]<=T[2]); // 只在T[0]不大于T[1]且T[1]不大于T[2]时返回真
 }

 Status IsDescending(Triplet T) // 在教科书第13页
 { // 初始条件：三元组T已存在。操作结果：如果T的3个元素按降序排列，则返回1；否则返回0
   return(T[0]>=T[1]&&T[1]>=T[2]); // 只在T[0]不小于T[1]且T[1]不小于T[2]时返回真
 }

 Status Max(Triplet T,ElemType &e)
 { // 初始条件：三元组T已存在。操作结果：用e返回指向T的最大元素的值。在教科书第13页
   e=(T[0]>=T[1])?(T[0]>=T[2]?T[0]:T[2]):(T[1]>=T[2]?T[1]:T[2]); // 嵌套的条件运算符
   return OK;
 }

 Status Min(Triplet T,ElemType &e)
 { // 初始条件：三元组T已存在。操作结果：用e返回指向T的最小元素的值。在教科书第13页
   e=(T[0]<=T[1])?(T[0]<=T[2]?T[0]:T[2]):(T[1]<=T[2]?T[1]:T[2]); // 嵌套的条件运算符
   return OK;
 }
