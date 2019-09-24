 // func8-5.cpp 包括数据元素类型的定义及对它的操作
 typedef int KeyType; // 定义关键字类型为整型
 struct ElemType // 数据元素类型
 { KeyType key; // 关键字
   int others; // 其他数据
 };

 void Visit(ElemType c) // Traverse()调用的与之配套的访问数据元素的函数
 { printf("(%d,%d)",c.key,c.others);
 }

 void InputFromFile(FILE* f,ElemType &c) // 与之配套的从文件输入数据元素的函数
 { fscanf(f,"%d%d",&c.key,&c.others);
 }

 void InputKey(KeyType &k) // 与之配套的由键盘输入关键字的函数
 { scanf("%d",&k);
 }
