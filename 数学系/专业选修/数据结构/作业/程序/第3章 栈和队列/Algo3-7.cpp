 // algo3-7.cpp 用递归调用求Ackerman(m,n)的值
 #include<stdio.h>
 int ack(int m,int n)
 { int z;
   if(m==0)
     z=n+1; // 出口
   else if(n==0)
     z=ack(m-1,1); // 对形参m降阶
   else
     z=ack(m-1,ack(m,n-1)); // 对形参m、n降阶
   return z;
 }

 void main()
 {
   int m,n;
   printf("请输入m,n：");
   scanf("%d,%d",&m,&n);
   printf("Ack(%d,%d)=%d\n",m,n,ack(m,n));
 }
