 // c1.h (文件名)
 #include<string.h> // 字符串函数头文件
 #include<ctype.h> // 字符函数头文件
 #include<malloc.h> // malloc()等
 #include<limits.h> // INT_MAX等
 #include<stdio.h> // 标准输入输出头文件，包括EOF(=^Z或F6)，NULL等
 #include<stdlib.h> // atoi()，exit()
 #include<io.h> // eof()
 #include<math.h> // 数学函数头文件，包括floor()，ceil()，abs()等
 #include<sys/timeb.h> // ftime()
 #include<stdarg.h> // 提供宏va_start，va_arg和va_end，用于存取变长参数表
 // 函数结果状态代码。在教科书第10页
 #define TRUE 1
 #define FALSE 0
 #define OK 1
 #define ERROR 0
 // #define INFEASIBLE -1 没使用
 // #define OVERFLOW -2 因为在math.h中已定义OVERFLOW的值为3，故去掉此行
 typedef int Status; // Status是函数的类型，其值是函数结果状态代码，如OK等
 typedef int Boolean; // Boolean是布尔类型，其值是TRUE或FALSE，第7、8章用到
