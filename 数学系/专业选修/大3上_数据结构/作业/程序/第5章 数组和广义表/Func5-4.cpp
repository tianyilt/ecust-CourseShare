 // func5-4.cpp 广义表的主函数，main5-4.cpp和main5-5.cpp调用
 void main()
 {
   char p[80];
   SString t;
   GList n,m;
   InitGList(n); // 初始化广义表n，n为空表
   printf("空广义表n的深度=%d，n是否空？%d(1:是 0:否)\n",GListDepth(n),
   GListEmpty(n));
   printf("请输入广义表n(书写形式：空表:()，单原子:(a)，其他:(a,(b),c))：\n");
   gets(p); // 将描述广义表n的字符串赋给p
   StrAssign(t,p); // 将p转换为SString类型的t
   CreateGList(n,t); // 根据t创建广义表n
   printf("广义表n的长度=%d，",GListLength(n));
   printf("深度=%d，n是否空？%d(1:是 0:否)\n",GListDepth(n),GListEmpty(n));
   printf("遍历广义表n：");
   Traverse_GL(n,print2); // 遍历广义表n
   CopyGList(m,n); // 复制广义表m=n
   printf("\n复制广义表m=n，m的长度=%d，",GListLength(m));
   printf("m的深度=%d\n遍历广义表m：",GListDepth(m));
   Traverse_GL(m,print2); // 遍历广义表m
   DestroyGList(m); // 销毁广义表m，释放存储空间
   m=GetHead(n); // 生成广义表n的表头元素，并由m指向
   printf("\nm是n的表头元素，遍历m：");
   Traverse_GL(m,print2); // 遍历广义表m
   DestroyGList(m); // 销毁广义表m，释放存储空间
   m=GetTail(n); // 将广义表n的表尾(除表头之外的部分)生成为广义表，并由m指向其
   printf("\nm是由n的表尾形成的广义表，遍历广义表m：");
   Traverse_GL(m,print2); // 遍历广义表m
   InsertFirst_GL(m,n); // 将广义表n插到广义表m中，并作为m的第1个元素(表头)
   printf("\n插入广义表n为m的表头，遍历广义表m：");
   Traverse_GL(m,print2); // 遍历广义表m
   DeleteFirst_GL(m,n); // 删除广义表m的表头，并由n指向删除的表头
   printf("\n删除m的表头，并由n指向m的表头，遍历广义表m：");
   Traverse_GL(m,print2); // 遍历广义表m
   printf("\n遍历广义表n(广义表m的原表头)：");
   Traverse_GL(n,print2); // 遍历广义表n
   printf("\n");
   DestroyGList(m); // 销毁广义表m、n，并释放存储空间
   DestroyGList(n);
 }
