 // algo3-3.cpp 行编辑程序，实现算法3.2
 typedef char SElemType; // 定义栈元素类型为字符型
 #include"c1.h"
 #include"c3-1.h" // 栈的顺序存储结构
 #include"bo3-1.cpp" // 顺序栈存储结构的基本操作(9个)
 FILE *fp;

 void copy(SElemType c)
 { // 将字符c送至fp所指的文件中
   fputc(c,fp);
 }

 void LineEdit()
 { // 利用字符栈s，从终端接收一行并送至调用过程的数据区。算法3.2
   SqStack s;
   char ch;
   InitStack(s); // 初始化栈s
   printf("请输入一个文本文件，^Z结束输入：\n");
   ch=getchar(); // 接收字符到ch
   while(ch!=EOF) // 当全文未结束(EOF为^Z键，全文结束符)
   { while(ch!=EOF&&ch!='\n') // 当全文未结束且未到行末(不是换行符)
     { switch(ch) // 对于当前字符ch，分情况处理
       { case '#':if(!StackEmpty(s))
                    Pop(s,ch); // 仅当栈非空时弹出栈顶元素，c可由ch替代
                  break;
         case '@':ClearStack(s); // 重置s为空栈
                  break;
         default :Push(s,ch); // 其他字符进栈
       }
       ch=getchar(); // 从终端接收下一个字符到ch
     } // 到行末或全文结束，退出此层循环
     StackTraverse(s,copy); // 将从栈底到栈顶的栈内字符依次传送至文件(调用copy()函数)
     fputc('\n',fp); // 向文件输入一个换行符
     ClearStack(s); // 重置s为空栈
     if(ch!=EOF) // 全文未结束
       ch=getchar(); // 从终端接收下一个字符到ch
   }
   DestroyStack(s); // 销毁栈s
 }

 void main()
 {
   fp=fopen("ed.txt","w");
   // 在当前目录下建立ed.txt文件，用于写数据，如已有同名文件则先删除原文件
   if(fp) // 建立文件成功
   { LineEdit(); // 行编辑
     fclose(fp); // 关闭fp所指的文件
   }
   else
     printf("建立文件失败！\n");
 }
