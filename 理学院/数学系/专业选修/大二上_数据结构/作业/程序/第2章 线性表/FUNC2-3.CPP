 // func2-3.cpp 检验单链表基本操作的主函数
 // main2-2.cpp、main2-3.cpp、main2-4.cpp和main2-5.cpp调用
 void main()
 {
   LinkList L; // 与main2-1.cpp不同
   ElemType e,e0;
   Status i;
   int j,k;
   InitList(L); // 初始化线性表L
   for(j=1;j<=5;j++)
     i=ListInsert(L,1,j); // 在L的表头插入j
   printf("在L的表头依次插入1～5后，L=");
   ListTraverse(L,print); // 依次对元素调用print()，输出元素的值
   i=ListEmpty(L); // 检测表L是否空
   printf("L是否空？i=%d(1:是 0:否)，表L的长度=%d\n",i,ListLength(L));
   ClearList(L); // 清空表L
   printf("清空L后，L=");
   ListTraverse(L,print);
   i=ListEmpty(L); // 再次检测表L是否空
   printf("L是否空？i=%d(1:是 0:否)，表L的长度=%d\n",i,ListLength(L));
   for(j=1;j<=10;j++)
     ListInsert(L,j,j); // 在L的表尾插入j
   printf("在L的表尾依次插入1～10后，L=");
   ListTraverse(L,print); // 依次输出表L中的元素
   for(j=0;j<=1;j++)
   {
 #ifdef SLL // 仅用于静态链表
     k=LocateElem(L,j); // 查找表L中与j相等的元素，并将其位序赋给k
     if(k) // k不为0，表明有符合条件的元素
       printf("值为%d的元素的位序为%d\n",j,k);
 #else // 仅用于链表
     k=LocateElem(L,j,equal); // 查找表L中与j相等的元素，并将其在链表中的排序赋给k
     if(k) // k不为0，表明有符合条件的元素
       printf("第%d个元素的值为%d\n",k,j);
 #endif
     else // k为0，没有符合条件的元素
       printf("没有值为%d的元素，",j);
   }
   for(j=1;j<=2;j++) // 测试头2个数据
   { GetElem(L,j,e0); // 把表L中的第j个数据赋给e0
     i=PriorElem(L,e0,e); // 求e0的前驱，如成功，将值赋给e
     if(i==ERROR) // 操作失败
       printf("元素%d无前驱，",e0);
     else // 操作成功
       printf("元素%d的前驱为%d\n",e0,e);
   }
   for(j=ListLength(L)-1;j<=ListLength(L);j++) // 最后2个数据
   { GetElem(L,j,e0); // 把表L中的第j个数据赋给e0
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
       printf("删除第%d个元素失败(不存在此元素)。",j);
     else // 表中存在第j个数据，删除成功，其值赋给e
       printf("删除第%d个元素成功，其值为%d\n",j,e);
   }
   printf("依次输出L的元素：");
   ListTraverse(L,print); // 依次输出表L中的元素
   DestroyList(L); // 销毁表L
 #ifndef SLL // 仅用于链表
   printf("销毁L后，L=%u\n",L);
 #endif
 }

