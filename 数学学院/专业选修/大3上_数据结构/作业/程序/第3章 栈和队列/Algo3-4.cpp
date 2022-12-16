 // algo3-4.cpp 利用栈求解迷宫问题(只输出一个解，算法3.3)
 #include"c1.h"
 struct PosType // 迷宫坐标位置类型
 { int x; // 行值
   int y; // 列值
 };
 // 全局变量
 PosType begin,end; // 迷宫的入口坐标,出口坐标
 PosType direc[4]={{0,1},{1,0},{0,-1},{-1,0}};
 // {行增量,列增量}，移动方向依次为东南西北

 #define MAXLENGTH 25 // 设迷宫的最大行列为25
 typedef int MazeType[MAXLENGTH][MAXLENGTH]; // 迷宫数组类型[行][列]
 MazeType m; // 迷宫数组
 int x,y; // 迷宫的行数,列数

 void Print()
 { // 输出迷宫的解(m数组)
   int i,j;
   for(i=0;i<x;i++)
   { for(j=0;j<y;j++)
       printf("%3d",m[i][j]);
     printf("\n");
   }
 }

 void Init()
 { // 设定迷宫布局(墙值为0，通道值为1)
   int i,j,x1,y1;
   printf("请输入迷宫的行数,列数(包括外墙)：");
   scanf("%d,%d",&x,&y);
   for(i=0;i<y;i++) // 定义周边值为0(外墙)
   { m[0][i]=0; // 上边
     m[x-1][i]=0; // 下边
   }
   for(i=1;i<x-1;i++)
   { m[i][0]=0; // 左边
     m[i][y-1]=0; // 右边
   }
   for(i=1;i<x-1;i++)
     for(j=1;j<y-1;j++)
       m[i][j]=1; // 定义除外墙，其余都是通道，初值为1
   printf("请输入迷宫内墙单元数：");
   scanf("%d",&j);
   printf("请依次输入迷宫内墙每个单元的行数,列数：\n");
   for(i=1;i<=j;i++)
   { scanf("%d,%d",&x1,&y1);
     m[x1][y1]=0; // 修改内墙的值为0
   }
   printf("迷宫结构如下：\n");
   Print();
   printf("请输入入口的行数,列数：");
   scanf("%d,%d",&begin.x,&begin.y);
   printf("请输入出口的行数,列数：");
   scanf("%d,%d",&end.x,&end.y);
 }

 int curstep=1; // 当前足迹，初值(在入口处)为1
 struct SElemType // 栈的元素类型。在教科书第51页
 { int ord; // 通道块在路径上的“序号”
   PosType seat; // 通道块在迷宫中的“坐标位置”
   int di; // 从此通道块走向下一通道块的“方向”(0～3表示东～北)
 };

 #include"c3-1.h" // 采用顺序栈存储结构
 #include"bo3-1.cpp" // 采用顺序栈的基本操作函数

 // 定义墙元素值为0，可通过路径为1，经试探不可通过路径为-1，通过路径为足迹
 Status Pass(PosType b)
 { // 当迷宫m的b点的值为1(可通过路径)，返回OK；否则，返回ERROR
   if(m[b.x][b.y]==1)
     return OK;
   else
     return ERROR;
 }

 void FootPrint(PosType b)
 { // 使迷宫m的b点的值变为足迹(curstep)
   m[b.x][b.y]=curstep;
 }

 void NextPos(PosType &b,int di)
 { // 根据当前位置b及移动方向di，修改b为下一位置
   b.x+=direc[di].x;
   b.y+=direc[di].y;
 }

 void MarkPrint(PosType b)
 { // 使迷宫m的b点的值变为-1(标记为经试探由此不能到达终点的路径)
   m[b.x][b.y]=-1;
 }

 Status MazePath(PosType start,PosType end) // 算法3.3
 { // 若迷宫m中存在从入口start到出口end的通道，则求得一条存放在栈中(从栈底到栈顶)，
   // 并返回TRUE；否则返回FALSE
   PosType curpos=start; // 当前位置在入口
   SqStack S; // 顺序栈
   SElemType e; // 栈元素
   InitStack(S); // 初始化栈
   do
   { if(Pass(curpos)) // 当前位置可以通过，即是未曾走到过的通道块
     { FootPrint(curpos); // 留下足迹(使迷宫m的当前位置的值为curstep)
       e.ord=curstep; // 栈元素的序号为当前足迹curstep
       e.seat=curpos; // 栈元素的位置为当前位置
       e.di=0; // 从当前位置出发，下一位置是向东
       Push(S,e); // 入栈当前位置及状态
       curstep++; // 足迹加1
       if(curpos.x==end.x&&curpos.y==end.y) // 到达终点(出口)
         return TRUE;
       NextPos(curpos,e.di); // 由当前位置及移动方向，确定下一个当前位置，仍赋给curpos
     }
     else // 当前位置不能通过
     { if(!StackEmpty(S)) // 栈不空
       { Pop(S,e); // 退栈到前一位置
         curstep--; // 足迹减1
         while(e.di==3&&!StackEmpty(S)) // 前一位置处于最后一个方向(北)且栈不空
         { MarkPrint(e.seat); // 在前一位置留下由其不能到达终点的标记(-1)
           Pop(S,e); // 再退回一步
           curstep--; // 足迹再减1
         }
         if(e.di<3) // 未到最后一个方向(北)
         { e.di++; // 换下一个方向探索
           Push(S,e); // 入栈该位置的下一个方向
           curstep++; // 足迹加1
           curpos=e.seat; // 确定当前位置
           NextPos(curpos,e.di); // 由当前位置及移动方向，确定下一个当前位置，仍赋给curpos
         }
       }
     }
   }while(!StackEmpty(S));
   return FALSE;
 }

 void main()
 {
   Init(); // 初始化迷宫
   if(MazePath(begin,end)) // 有通路
   { printf("此迷宫从入口到出口的一条路径如下：\n");
     Print(); // 输出此通路(m数组)
   }
   else
     printf("此迷宫没有从入口到出口的路径\n");
 }
