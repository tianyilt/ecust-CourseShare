#include<stdio.h>
#include<malloc.h>
#include <stdlib.h>
#define MaxSize 100 

typedef int dataType;
typedef struct {
	dataType data[MaxSize];
	int size;
} SqList;

//创建顺序表 
SqList* CreateList() {
	SqList* t = (SqList*)malloc(sizeof(SqList));
	t->size = 0;
	return t;
}

//在顺序表的第k个位置插入元素x 
void Insert(SqList* l, int k, dataType x) {
	if (k < 1 || k > l->size + 1) exit(1);
	if (l->size == MaxSize) exit(1);
	for (int i = l->size; i >= k; i--)
		l->data[i] = l->data[i - 1];
	l->data[k - 1] = x;
	l->size++;
}

//删除顺序表的第k个元素
void Delete(SqList* l, int k) {
	if (k < 1 || k > l->size) exit(1);
	for (int i = k; i < l->size; i++)
		l->data[i - 1] = l->data[i];
	l->size--;
}

//判断顺序表是否为空
int Empty(SqList* l) {
	return l->size == 0;
}

//判断顺序表是否满
int Full(SqList* l) {
	return l->size == MaxSize;
}


//求顺序表第i个元素的值
dataType GetData(SqList* l, int i) {
	if (i < 1 || i > l->size) exit(1);
	return l->data[i-1];
}

//查找值为x的元素
int Locate(SqList* l, dataType x) {
	for (int i = 0; i < l->size; i++)
		if (l->data[i] ==  x)
			return i + 1;
	return 0;
}








//输出顺序表 
void Print(SqList* l) {
	for (int i = 0; i < l->size; i++)
		printf("%d ", l->data[i]);
	printf("\n");
}

int main() {
	SqList* pl = CreateList();
	Insert(pl, 1, 10); // 此时顺序表样子 10
	Insert(pl, 1, 20); // 此时顺序表样子 20 10 第二位是 10
	Delete(pl, 2); // 此时顺序表样子 20
	Insert(pl, 1, 30); // 此时顺序表样子 30 20 第二位是 20
	Insert(pl, 1, 40); // 此时顺序表样子 40 30 20 第二位是 30
	Print(pl);
	printf("%d", GetData(pl, 2));
}
