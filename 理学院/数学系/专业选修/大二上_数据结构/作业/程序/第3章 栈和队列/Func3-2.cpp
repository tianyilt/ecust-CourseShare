 // func3-2.cpp 链队列的主函数，main3-2.cpp和main3-3.cpp调用
 void main()
 {
   int i;
   QElemType d;
   LinkQueue q;
   InitQueue(q); // 构造空队列q，失败则退出
   printf("成功地构造了一个空队列\n");
   printf("是否空队列？%d(1:空 0:否)，",QueueEmpty(q));
   printf("队列的长度为%d\n",QueueLength(q));
   EnQueue(q,-5); // 依次入队3个元素
   EnQueue(q,5);
   EnQueue(q,10);
   printf("插入3个元素(-5，5，10)后，队列的长度为%d\n",QueueLength(q));
   printf("是否空队列？%d(1:空 0:否)，",QueueEmpty(q));
   printf("队列的元素依次为");
   QueueTraverse(q,print); // 从队头到队尾依次对队列q中每个元素调用函数print()
   i=GetHead(q,d); // 将队头元素赋给d
   if(i==OK) // 队列q不空
     printf("队头元素是%d，",d);
   DeQueue(q,d); // 删除队头元素，其值赋给d
   printf("删除了队头元素%d，",d);
   i=GetHead(q,d); // 将队列q的队头元素赋给d
   if(i==OK) // 队列q不空
     printf("新的队头元素是%d\n",d);
   ClearQueue(q); // 清空队列q
   printf("清空队列后，q.front=%u，q.rear=%u，q.front->next=%u\n",q.front,
   q.rear,q.front->next);
   DestroyQueue(q); // 销毁队列q
   printf("销毁队列后，q.front=%u，q.rear=%u\n",q.front,q.rear);
 }
