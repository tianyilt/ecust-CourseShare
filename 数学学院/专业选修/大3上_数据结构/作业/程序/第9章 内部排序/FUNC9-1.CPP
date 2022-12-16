 // func9-1.cpp 与KeyType和InfoType均为整型情况配套的输入输出函数
 void Print(SqList L) // 输出顺序表
 { int i;
   for(i=1;i<=L.length;i++)
     printf("(%d,%d)",L.r[i].key,L.r[i].otherinfo);
   printf("\n");
 }

 void InputFromFile(FILE* f,RedType &c) // 从文件输入记录的函数
 { fscanf(f,"%d%d",&c.key,&c.otherinfo);
 }
