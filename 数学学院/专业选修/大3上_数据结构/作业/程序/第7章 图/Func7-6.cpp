 // func7-6.cpp 包括顶点信息类型的定义及对它的操作
 #define MAX_NAME 9 // 顶点字符串的最大长度+1
 struct VertexType // 顶点信息类型
 { char name[MAX_NAME]; // 顶点名称
   int ve,vl; // (顶点)事件最早发生时间,事件最迟发生时间
 };

 void Visit(VertexType ver) // 访问顶点名称的函数，输出图要用到
 { printf("%s ",ver.name);
 }

 void Input(VertexType &ver) // 输入顶点信息的函数，创建图要用到
 { scanf("%s",ver.name);
 }

 void Visitel(VertexType ver) // 输出顶点ve、vl域的函数
 { printf("%3d%3d",ver.ve,ver.vl);
 }

 void InputFromFile(FILE* f,VertexType &ver) // 从文件输入顶点信息的函数
 { fscanf(f,"%s",ver.name);
 }
