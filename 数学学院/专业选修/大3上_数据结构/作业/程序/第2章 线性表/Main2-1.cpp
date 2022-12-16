 // main2-1.cpp 检验bo2-1.cpp的主程序
 #include"c1.h"
 typedef int ElemType; // 定义ElemType为整型
 #include"c2-1.h" // 线性表的顺序存储结构
 #include"bo2-1.cpp" // 线性表顺序存储结构的基本操作
 #include"func2-2.cpp" // 包括equal()、comp()、print()、print1()和print2()函数

 Status sq(ElemType c1,ElemType c2)
 { // 数据元素判定函数(平方关系)，LocateElem()调用的函数
   if(c1==c2*c2)
     return TRUE;
   else
     return FALSE;
 }

 void dbl(ElemType &c)
 { // ListTraverse()调用的另一函数(元素值加倍)
   c*=2;
 }

 void main()
 {
   SqList L;
   ElemType e,e0;
   Status i;
   int j,k;
   InitList(L); // 初始化线性表L
   printf("初始化L后，L.length=%d，L.listsize=%d，L.elem=%u\n",L.length,
   L.listsize,L.elem);
   for(j=1;j<=5;j++)
     i=ListInsert(L,1,j); // 在L的表头插入j
   printf("在L的表头依次插入1～5后，*L.elem=");
   for(j=1;j<=5;j++)
     printf("%d ",*(L.elem+j-1)); // 依次输出表L中的元素
   printf("\n调用ListTraverse()函数，依次输出表L中的元素：");
   ListTraverse(L,print1); // 依次对表L中的元素调用print1()函数(输出元素的值)
   i=ListEmpty(L); // 检测表L是否空
   printf("L.length=%d(改变)，L.listsize=%d(不变)，",L.length,L.listsize);
   printf("L.elem=%u(不变)，L是否空？i=%d(1:是 0:否)\n",L.elem,i);
   ClearList(L); // 清空表L
   i=ListEmpty(L); // 再次检测表L是否空
   printf("清空L后，L.length=%d，L.listsize=%d，",L.length,L.listsize);
   printf("L.elem=%u，L是否空？i=%d(1:是 0:否)\n",L.elem,i);
   for(j=1;j<=10;j++)
     ListInsert(L,j,j); // 在L的表尾插入j
   printf("在L的表尾依次插入1～10后，L=");
   ListTraverse(L,print1); // 依次输出表L中的元素
   printf("L.length=%d，L.listsize=%d，L.elem=%u\n",L.length,L.listsize,L.elem);
   ListInsert(L,1,0); // 在L的表头插入0，增加存储空间
   printf("在L的表头插入0后，L.length=%d(改变)，L.listsize=%d(改变)，"
   "L.elem=%u(有可能改变)\n",L.length,L.listsize,L.elem);
   GetElem(L,5,e); // 将表L中的第5个元素的值赋给e
   printf("第5个元素的值为%d\n",e);
   for(j=10;j<=11;j++)
   { k=LocateElem(L,j,equal); // 查找表L中与j相等的元素，并将其位序赋给k
     if(k) // k不为0，表明有符合条件的元素
       printf("第%d个元素的值为%d，",k,j);
     else // k为0，没有符合条件的元素
       printf("没有值为%d的元素\n",j);
   }
   for(j=3;j<=4;j++) // 测试2个数据
   { k=LocateElem(L,j,sq); // 查找表L中与j的平方相等的元素，并将其位序赋给k
     if(k) // k不为0，表明有符合条件的元素
       printf("第%d个元素的值为%d的平方，",k,j);
     else // k为0，没有符合条件的元素
       printf("没有值为%d的平方的元素\n",j);
   }
   for(j=1;j<=2;j++) // 测试头2个数据
   { GetElem(L,j,e0); // 将表L中的第j个元素的值赋给e0
     i=PriorElem(L,e0,e); // 求e0的前驱，如成功，将值赋给e
     if(i==ERROR) // 操作失败
       printf("元素%d无前驱，",e0);
     else // 操作成功
       printf("元素%d的前驱为%d\n",e0,e);
   }
   for(j=ListLength(L)-1;j<=ListLength(L);j++) // 最后2个数据
   { GetElem(L,j,e0); // 将表L中的第j个元素的值赋给e0
     i=NextElem(L,e0,e); // 求e0的后继，如成功，将值赋给e
     if(i==ERROR) // 操作失败
       printf("元素%d无后继\n",e0);
     else // 操作成功
       printf("元素%d的后继为%d，",e0,e);
   }
   k=ListLength(L); // k为表长
   for(j=k+1;j>=k;j--)
   { i=ListDelete(L,j,e); // 删除第j个数据
     if(i==ERROR) // 表中不存在第j个数据
       printf("删除第%d个元素失败。",j);
     else // 表中存在第j个数据，删除成功，其值赋给e
       printf("删除第%d个元素成功，其值为%d",j,e);
   }
   ListTraverse(L,dbl); // 依次对元素调用dbl()，元素值乘2
   printf("L的元素值加倍后，L=");
   ListTraverse(L,print1); // 依次输出表L中的元素
   DestroyList(L); // 销毁表L
   printf("销毁L后，L.length=%d，L.listsize=%d，L.elem=%u\n",L.length,
   L.listsize,L.elem);
 }
