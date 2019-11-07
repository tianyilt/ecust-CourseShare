 // bo3-1.cpp 顺序栈(存储结构由c3-1.h定义)的基本操作(9个)
 void InitStack(SqStack &S)
 { // 构造一个空栈S。在教科书第47页
   S.base=(SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
   if(!S.base)
     exit(OVERFLOW); // 动态分配存储空间失败，则退出
   S.top=S.base; // 栈顶指向栈底(空栈)
   S.stacksize=STACK_INIT_SIZE; // 存储空间为初始分配量
 }

 void DestroyStack(SqStack &S)
 { // 销毁栈S，S不再存在
   free(S.base); // 释放栈空间
   S.top=S.base=NULL; // 栈顶、栈底指针均为空
   S.stacksize=0; // 当前已分配的存储空间为0
 }

 void ClearStack(SqStack &S)
 { // 把栈S置为空栈
   S.top=S.base; // 栈顶指针指向栈底
 }

 Status StackEmpty(SqStack S)
 { // 若栈S为空栈，则返回TRUE；否则返回FALSE
   if(S.top==S.base) // 空栈条件
     return TRUE;
   else
     return FALSE;
 }

 int StackLength(SqStack S)
 { // 返回栈S的元素个数，即栈的长度
   return S.top-S.base;
 }

 Status GetTop(SqStack S,SElemType &e) // 在教科书第47页
 { // 若栈S不空，则用e返回S的栈顶元素，并返回OK；否则返回ERROR
   if(S.top>S.base) // 栈不空
   { e=*(S.top-1); // 将栈顶元素赋给e
     return OK;
   }
   else
     return ERROR;
 }

 void Push(SqStack &S,SElemType e)
 { // 插入元素e为栈S新的栈顶元素。
   // 在教科书第47页
   if(S.top-S.base==S.stacksize) // 栈满
   { S.base=(SElemType*)realloc(S.base,
     (S.stacksize+STACK_INCREMENT)*
     sizeof(SElemType)); // 追加存储空间
     if(!S.base) // 追加存储空间失败，则退出
       exit(OVERFLOW);
     S.top=S.base+S.stacksize; // 修改栈顶指针，指向新的栈顶
     S.stacksize+=STACK_INCREMENT; // 更新当前已分配的存储空间
   }
   *(S.top)++=e; // 将e入栈，成为新的栈顶元素，栈顶指针上移1个存储单元
 }

 Status Pop(SqStack &S,SElemType &e) // 在教科书第47页
 { // 若栈S不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR
   if(S.top==S.base) // 栈空
     return ERROR;
   e=*--S.top; // 将栈顶元素赋给e，栈顶指针下移1个存储单元
   return OK;
 }

 void StackTraverse(SqStack S,void(*visit)(SElemType))
 { // 从栈底到栈顶依次对栈S中每个元素调用函数visit()
   while(S.top>S.base) // S.base指向栈元素
     visit(*S.base++); // 对该栈元素调用visit()，
   printf("\n");       // 栈底指针上移1个存储单元
 }
