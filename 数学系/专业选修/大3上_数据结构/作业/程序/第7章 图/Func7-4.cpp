 // func7-4.cpp 包括弧(边)的相关信息类型的定义及对它的操作
 typedef int VRType; // 定义权值类型为整型
 struct InfoType // 最简单的弧(边)的相关信息类型(只有权值)
 { VRType weight; // 权值
 };

 void InputArc(InfoType* &arc) // 与之配套的输入弧(边)的相关信息的函数
 { arc=(InfoType*)malloc(sizeof(InfoType)); // 动态生成存放弧(边)信息的空间
   scanf("%d",&arc->weight);
 }

 void OutputArc(InfoType* arc) // 与之配套的输出弧(边)的相关信息的函数
 { printf("：%d",arc->weight);
 }

 void InputArcFromFile(FILE* f,InfoType* &arc) // 由文件输入弧(边)的相关信息的函数
 { arc=(InfoType*)malloc(sizeof(InfoType)); // 动态生成存放弧(边)信息的空间
   fscanf(f,"%d",&arc->weight);
 }
