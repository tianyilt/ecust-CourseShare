 // c4-1.h 串的定长顺序存储结构。在教科书第73页
 #define MAX_STR_LEN 40 // 用户可在255(1个字节所能表示的最大整数)以内定义最大串长
 typedef unsigned char SString[MAX_STR_LEN+1]; // 0号单元存放串的长度
