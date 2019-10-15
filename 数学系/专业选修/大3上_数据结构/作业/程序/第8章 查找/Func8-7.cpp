 // func8-7.cpp 包括对键树的输入输出操作
 void Visit(Record* r) // TraverseDSTable()调用的与之配套的访问记录的函数
 { printf("(%s,%d)",r->key.ch,r->others.order);
 }

 void InputKey(char* k) // 与之配套的由键盘输入关键字符串的函数
 { scanf("%s",k); // 输入待查找记录的关键字符串给k
 }
