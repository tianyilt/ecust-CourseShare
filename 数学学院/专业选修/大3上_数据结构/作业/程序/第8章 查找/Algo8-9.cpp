 // algo8-9.cpp 检验bo8-7.cpp的程序
 #include"c1.h"
 #define NULL_KEY 0 // 0为无记录标志
 #define N 15 // 数组可容纳的数据元素个数
 int m; // 哈希表表长，全局变量
 typedef int KeyType; // 定义关键字域为整型
 struct ElemType // 数据元素类型
 { KeyType key;
   int order;
 };

 #include"c8-2.h"
 #include"c8-11.h"
 #include"bo8-7.cpp"

 void Visit(int p,ElemType r)
 { printf("address=%d (%d,%d)\n",p,r.key,r.order);
 }

 void main()
 {
   ElemType r[N]; // 记录数组
   HashTable h;
   int i,n,p=0;
   Status j;
   KeyType k;
   FILE *f; // 文件指针类型
   f=fopen("f8-6.txt","r"); // 打开数据文件f8-6.txt
   do // 将数据文件中的记录依次读入记录数组r
   { i=fscanf(f,"%d%d",&r[p].key,&r[p].order); // 由文件输入数据给r[p]
     if(i!=-1) // 输入数据成功
       p++;
   }while(!feof(f)&&p<N); // 未到数据文件的结尾且记录数组未满
   fclose(f); // 关闭数据文件
   InitHashTable(h); // 构造一个空的哈希表h
   for(i=0;i<p-1;i++)
   { j=InsertHash(h,r[i]); // 在h中插入前p-1个记录(最后1个记录不插入)
     if(j==DUPLICATE)
       printf("表中已有关键字为%d的记录，无法再插入记录(%d,%d)\n",
       r[i].key,r[i].key,r[i].order);
   }
   printf("按哈希地址的顺序遍历哈希表：\n");
   TraverseHash(h,Visit); // 按哈希地址的顺序遍历哈希表h
   printf("请输入待查找记录的关键字：");
   scanf("%d",&k); // 输入待查找记录的关键字
   j=SearchHash(h,k,p,n); // 查找时n值无用
   if(j==SUCCESS) // 查找成功
     Visit(p,h.elem[p]); // 输出该纪录
   else // 查找失败
     printf("未找到\n"); // 输出未找到信息
   j=InsertHash(h,r[i]); // 插入最后1个记录(需重建哈希表)
   if(j==ERROR) // 重建哈希表
     j=InsertHash(h,r[i]); // 重建哈希表后重新插入
   printf("按哈希地址的顺序遍历重建后的哈希表：\n");
   TraverseHash(h,Visit); // 按哈希地址的顺序遍历哈希表h
   printf("请输入待查找记录的关键字：");
   scanf("%d",&k); // 输入待查找记录的关键字
   j=SearchHash(h,k,p,n); // 查找时n值无用
   if(j==SUCCESS) // 查找成功
     Visit(p,h.elem[p]); // 输出该纪录
   else // 查找失败
     printf("未找到\n"); // 输出未找到信息
   DestroyHashTable(h); // 销毁哈希表h
 }
