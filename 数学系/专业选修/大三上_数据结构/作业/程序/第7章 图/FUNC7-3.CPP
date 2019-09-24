 // func7-3.cpp 用于检验邻接矩阵和邻接表的主函数
 void main()
 {
   int i,j,k,n;
   char s[3]="边";
   Graph g; // 抽象的图类型
   VertexType v1,v2; // 顶点类型
   printf("请依次选择有向图，有向网，无向图，无向网：\n");
   for(i=0;i<4;i++) // 验证4种情况
   { CreateGraph(g); // 构造图g
     Display(g); // 输出图g
     printf("插入新顶点，请输入新顶点的值：");
     Input(v1); // 根据顶点信息的类型，输入顶点v1的信息，在func7-1.cpp中
     InsertVex(g,v1); // 在图g中插入顶点v1
     if(g.kind<2) // 有向
       strcpy(s,"弧");
     printf("插入与新顶点有关的%s，请输入%s数：",s,s);
     scanf("%d",&n);
     for(k=0;k<n;k++) // 依次插入n条弧(边)
     { printf("请输入另一顶点的名称：");
       scanf("%s",v2.name);
       if(g.kind<=1) // 有向
       { printf("请输入另一顶点的方向(0：弧头 1：弧尾)：");
         scanf("%d",&j);
         if(j) // v2是弧尾
           InsertArc(g,v2,v1); // 在图g中插入弧v2→v1
         else // v2是弧头
           InsertArc(g,v1,v2); // 在图g中插入弧v1→v2
       }
       else // 无向
         InsertArc(g,v1,v2); // 在图g中插入边v1—v2
     }
     Display(g); // 输出图g
     printf("删除顶点及相关的%s，请输入待删除顶点的名称：",s);
     scanf("%s",v1.name);
     DeleteVex(g,v1); // 在图g中删除顶点v1
     Display(g); // 输出图g
     if(i==3) // 对于最后一个(无向网)，测试以下函数
     { printf("修改顶点的值，请输入待修改顶点名称 新值：");
       scanf("%s",v1.name); // 输入待修改顶点名称，以查找待修改的顶点
       Input(v2); // 输入顶点的新值，以代替原值
       PutVex(g,v1,v2); // 将图g中顶点v1的值改为v2
       if(g.kind<2) // 有向(假设最后一个可以不是无向网)
         printf("删除一条%s，请输入待删除%s的弧尾 弧头：",s,s);
       else // 无向
         printf("删除一条%s，请输入待删除%s的顶点1 顶点2：",s,s);
       scanf("%s%s",v1.name,v2.name); // 输入待删除弧(边)的2顶点的名称
       DeleteArc(g,v1,v2); // 删除图g中由顶点v1指向顶点v2的弧(边)
       Display(g); // 输出图g
     }
     DestroyGraph(g); // 销毁图g
   }
 }
