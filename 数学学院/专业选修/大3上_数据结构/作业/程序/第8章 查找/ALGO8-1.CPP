 // algo8-1.cpp 检验bo8-1.cpp(无序顺序表部分)的程序
 #include"c1.h"
 #include"func8-1.cpp" // 包括数据元素类型的定义及对它的操作
 #include"c8-1.h" // 静态查找表的顺序存储结构
 #include"c8-2.h" // 对两个数值型关键字比较的约定
 #include"bo8-1.cpp" // 静态查找表(顺序表和有序表)的基本操作(7个)

 void main()
 {
   SSTable st;
   int i;
   long s;
   char filename[13]; // 存储数据文件名(包括路径)
   printf("请输入数据文件名：");
   scanf("%s",filename);
   Creat_SeqFromFile(st,filename); // 由数据文件产生顺序静态查找表st
   for(i=1;i<=st.length;i++) // 依次计算每项数据元素的总分
     st.elem[i].total=st.elem[i].politics+st.elem[i].Chinese+st.elem[i].English+
     st.elem[i].math+st.elem[i].physics+st.elem[i].chemistry+st.elem[i].biology;
   printf("准考证号  姓名  政治 语文 外语 数学 物理 化学 生物 总分\n");
   Traverse(st,Visit); // 按顺序输出静态查找表st
   printf("请输入待查找人的考号：");
   InputKey(s); // 由键盘输入关键字s，在func8-1.cpp中
   i=Search_Seq(st,s); // 在静态查找表st中顺序查找含有关键字s的项的序号
   if(i) // 找到
     Visit(st.elem[i]); // 输出该项元素，在func8-1.cpp中
   else
     printf("未找到\n");
   Destroy(st); // 销毁静态查找表st
 }
