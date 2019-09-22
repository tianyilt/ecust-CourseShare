 // func8-1.cpp 包括数据元素类型的定义及对它的操作
 typedef long KeyType; // 定义关键字域为长整型
 #define key number // 定义关键字为准考证号
 struct ElemType // 数据元素类型(以教科书图9.1高考成绩为例)
 { long number; // 准考证号，与关键字类型同
   char name[9]; // 姓名(4个汉字加1个串结束标志)
   int politics; // 政治
   int Chinese; // 语文
   int English; // 英语
   int math; // 数学
   int physics; // 物理
   int chemistry; // 化学
   int biology; // 生物
   int total; // 总分
 };

 void Visit(ElemType c) // Traverse()调用的与之配套的访问数据元素的函数
 { printf("%-8ld%-8s%4d%5d%5d%5d%5d%5d%5d%5d\n",c.number,c.name,c.politics,
   c.Chinese,c.English,c.math,c.physics,c.chemistry,c.biology,c.total);
 }

 void InputFromFile(FILE* f,ElemType &c) // 与之配套的从文件输入数据元素的函数
 { fscanf(f,"%ld%s%d%d%d%d%d%d%d",&c.number,c.name,&c.politics,&c.Chinese,
   &c.English,&c.math,&c.physics,&c.chemistry,&c.biology);
 }

 void InputKey(KeyType &k) // 与之配套的由键盘输入关键字的函数
 { scanf("%ld",&k);
 }
