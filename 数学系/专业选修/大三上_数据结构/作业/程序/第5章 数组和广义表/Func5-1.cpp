 // func5-1.cpp
 int comp(int c1,int c2) // 比较整数c1和c2的大小关系，分别返回-1、0和1
 { // AddSMatrix()和MultSMatrix()函数要用到
   if(c1<c2)
     return -1;
   if(c1==c2)
     return 0;
   return 1;
 }
