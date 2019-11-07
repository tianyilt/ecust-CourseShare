 // func7-7.cpp 包括弧的相关信息类型的定义及对它的操作
 typedef int VRType; // 定义权值类型为整型
 struct InfoType // 弧的相关信息类型
 { VRType weight; // 权值
   int ee,el; // (活动)最早开始时间,最迟开始时间
 };

 void InputArc(InfoType* &arc) // 动态生成弧的相关信息的空间并输入权值的函数，创建图用到
 { arc=(InfoType*)malloc(sizeof(InfoType)); // 动态生成存放弧信息的空间
   scanf("%d",&arc->weight); // 输入权值
 }

 void OutputArc(InfoType* arc) // 输出弧的权值的函数，输出图要用到
 { printf("：%d",arc->weight);
 }

 void OutputArcwel(InfoType* arc) // 输出弧的权值、ee和el的函数
 { printf(" %3d %3d %3d ",arc->weight,arc->ee,arc->el); // 输出弧的权值、ee和el
 }

 void InputArcFromFile(FILE* f,InfoType* &arc) // 由文件输入弧(边)的相关信息的函数
 { arc=(InfoType*)malloc(sizeof(InfoType)); // 动态生成存放弧(边)信息的空间
   fscanf(f,"%d",&arc->weight);
 }
