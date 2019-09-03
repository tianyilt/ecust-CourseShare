 // main3-4.cpp 循环队列 检验bo3-4.cpp的主程序
 #include"c1.h"
 typedef int QElemType; // 定义队列元素为整型
 #include"c3-3.h" // 队列的顺序存储结构(循环队列)
 #include"bo3-4.cpp" // 循环队列存储结构的基本操作(9个)
 #define ElemType QElemType // 将func2-2.cpp中的ElemType类型定义为QElemType类型
 #include"func2-2.cpp" // 包括equal()、comp()、print()、print1()和print2()函数

 void main()
 {
   Status j;
   int i=0,m;
   QElemType d;
   SqQueue Q;
   InitQueue(Q); // 初始化队列Q，失败则退出
   printf("初始化队列后，队列空否？%u(1:空 0:否)\n",QueueEmpty(Q));
   printf("请输入整型队列元素(不超过%d个)，-1为提前结束符：",MAX_QSIZE-1);
   do
   { scanf("%d",&d); // 由键盘输入整型队列元素
     if(d==-1) // 输入的是提前结束符
       break; // 退出输入数据循环
     i++; // 计数器+1
     EnQueue(Q,d); // 入队输入的元素
   }while(i<MAX_QSIZE-1); // 队列元素的个数不超过允许的范围
   printf("队列长度为%d，",QueueLength(Q));
   printf("现在队列空否？%u(1:空 0:否)\n",QueueEmpty(Q));
   printf("连续%d次由队头删除元素，队尾插入元素：\n",MAX_QSIZE);
   for(m=1;m<=MAX_QSIZE;m++)
   { DeQueue(Q,d); // 删除队头元素，其值赋给d
     printf("删除的元素是%d，请输入待插入的元素：",d);
     scanf("%d",&d); // 输入要入队的元素给d
     EnQueue(Q,d); // 将d入队
   }
   m=QueueLength(Q); // m为队列Q的长度
   printf("现在队列中的元素为");
   QueueTraverse(Q,print); // 从队头到队尾依次对队列Q的每个元素调用函数print()
   printf("共向队尾插入了%d个元素。",i+MAX_QSIZE);
   if(m-2>0)
     printf("现在由队头删除%d个元素，",m-2);
   while(QueueLength(Q)>2)
   { DeQueue(Q,d); // 删除队头元素，其值赋给d
     printf("删除的元素值为%d，",d);
   }
   j=GetHead(Q,d); // 将队头元素赋给d
   if(j) // 队列Q不空
     printf("现在队头元素为%d\n",d);
   ClearQueue(Q); // 清空队列Q
   printf("清空队列后，队列空否？%u(1:空 0:否)\n",QueueEmpty(Q));
   DestroyQueue(Q); // 销毁队列Q
 }
