 // func7-2.cpp 包括弧(边)的相关信息类型的定义及对它的操作
 #define MAX_INFO 20 // 弧(边)的相关信息字符串的最大长度+1
 typedef char InfoType; // 弧(边)的相关信息类型

 void InputArc(InfoType* &arc) // 与之配套的输入弧(边)的相关信息的函数
 { char s[MAX_INFO]; // 临时存储空间
   int m;
   printf("请输入该弧(边)的相关信息(<%d个字符)：",MAX_INFO);
   gets(s); // 输入字符串(可包括空格)
   m=strlen(s); // 字符串长度
   if(m) // 长度不为0
   { arc=(char*)malloc((m+1)*sizeof(char)); // 动态生成相关信息存储空间
     strcpy(arc,s); // 复制s到arc
   }
 }

 void InputArcFromFile(FILE* f,InfoType* &arc) // 由文件输入弧(边)的相关信息的函数
 { char s[MAX_INFO]; // 临时存储空间
   fgets(s,MAX_INFO,f); // 由文件输入字符串(可包括空格)
   arc=(char*)malloc((strlen(s)+1)*sizeof(char)); // 动态生成相关信息存储空间
   strcpy(arc,s); // 复制s到arc
 }

 void OutputArc(InfoType* arc) // 与之配套的输出弧(边)的相关信息的函数
 { printf("%s\n",arc);
 }
