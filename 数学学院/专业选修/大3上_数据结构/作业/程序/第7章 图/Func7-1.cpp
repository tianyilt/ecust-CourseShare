 // func7-1.cpp 包括顶点信息类型的定义及对它的操作
 #define MAX_NAME 9 // 顶点名称字符串的最大长度+1
 struct VertexType // 最简单的顶点信息类型(只有顶点名称)
 { char name[MAX_NAME]; // 顶点名称
 };

 void Visit(VertexType ver) // 与之配套的访问顶点的函数
 { printf("%s ",ver.name);
 }

 void Input(VertexType &ver) // 与之配套的输入顶点信息的函数
 { scanf("%s",ver.name);
 }

 void InputFromFile(FILE* f,VertexType &ver) // 与之配套的从文件输入顶点信息的函数
 { fscanf(f,"%s",ver.name);
 }
