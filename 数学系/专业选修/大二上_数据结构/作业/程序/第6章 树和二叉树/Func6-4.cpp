 // func6-4.cpp 求赫夫曼编码的主函数
 void main()
 {
   HuffmanTree HT;
   HuffmanCode HC;
   int *w,n,i;
   printf("请输入权值的个数(>1)：");
   scanf("%d",&n);
   w=(int*)malloc(n*sizeof(int)); // 动态生成存放n个权值的空间
   printf("请依次输入%d个权值(整型)：\n",n);
   for(i=0;i<=n-1;i++)
     scanf("%d",w+i); // 依次输入权值
   HuffmanCoding(HT,HC,w,n); // 根据w所存的n个权值构造赫夫曼树HT，n个赫夫曼编码存于HC
   for(i=1;i<=n;i++)
     puts(HC[i]); // 依次输出赫夫曼编码
 }
