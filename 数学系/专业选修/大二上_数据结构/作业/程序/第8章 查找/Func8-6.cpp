 // func8-6.cpp 包括对B_树的输入输出操作
 void Visit(BTNode c,int i) // TraverseDSTable()调用的与之配套的访问记录的函数
 { printf("(%d,%d)",c.recptr[i]->key,c.recptr[i]->others.order);
 }

 void InputKey(KeyType &k) // 与之配套的由键盘输入关键字的函数
 { scanf("%d",&k);
 }
