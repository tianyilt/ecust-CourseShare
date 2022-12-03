 // main1-1.cpp 检验基本操作bo1-1.cpp的主函数
 #include"c1.h" // 要将程序中所有#include命令所包含的文件复制到当前目录下
 // 以下两行可根据需要选其一(且只能选其一)，而无须改变基本操作bo1-1.cpp
 typedef int ElemType; // 定义抽象数据类型ElemType在本程序中为整型。第4行
 //typedef double ElemType; // 定义抽象数据类型ElemType在本程序中为双精度型。第5行
 #include"c1-1.h" // 在此命令之前要定义ElemType的类型
 #include"bo1-1.cpp" // 在此命令之前要包括c1-1.h文件(因为其中定义了Triplet)
 #include"func1-1.cpp" // 输出函数，根据ElemType的类型选择不同的语句
 void main()
 {
   Triplet T;
   ElemType m;
   Status i;
   i=InitTriplet(T,5,7,9); // 初始化三元组T，其3个元素依次为5，7，9。第14行
 //i=InitTriplet(T,5.0,7.1,9.3); // 当ElemType为双精度型时，可取代上句。第15行
   printf("调用初始化函数后，i=%d(1:成功)。T的3个值为",i);
   PrintT(T); // 输出T的3个值
   i=Get(T,2,m); // 将三元组T的第2个值赋给m
   if(i==OK) // 调用Get()成功
   { printf("T的第2个值为");
     PrintE(m); // 输出m(=T[1])
   }
   i=Put(T,2,6); // 将三元组T的第2个值改为6
   if(i==OK) // 调用Put()成功
   { printf("将T的第2个值改为6后，T的3个值为");
     PrintT(T); // 输出T的3个值
   }
   i=IsAscending(T); // 测试升序的函数
   printf("调用测试升序的函数后，i=%d(0:否 1:是)\n",i);
   i=IsDescending(T); // 测试降序的函数
   printf("调用测试降序的函数后，i=%d(0:否 1:是)\n",i);
   if((i=Max(T,m))==OK) // 先赋值再比较
   { printf("T中的最大值为");
     PrintE(m); // 输出最大值m
   }
   if((i=Min(T,m))==OK)
   { printf("T中的最小值为");
     PrintE(m); // 输出最小值m
   }
   DestroyTriplet(T); // 函数也可以不带回返回值
   printf("销毁T后，T=%u\n",T);
 }
