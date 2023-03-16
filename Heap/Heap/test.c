#define _CRT_SECURE_NO_WARNINGS 1
#include"Heap.h"
#include<time.h>
#include<stdlib.h>

void Test()
{
	srand(time(0));
	HPDataType a[Capacity];
	int i = 0;
	while (i < 10)
	{
		a[i++] = rand() % (20 - 5 + 1) + 5;
	}
	Heap HP;
	HeapInit(&HP);
	HeapCreate(&HP, a, 10);
	Print(&HP);
	HeapPush(&HP, 2);
	HeapPush(&HP, 1);
	Print(&HP);
	HPDataType x = HeapTop(&HP);
	printf("É¾³ý¶Ñ¶¥ÔªËØ£º%d\n", x);
	Print(&HP);
}
int main()
{
	
	//Test();
	//TestTopk();
	FileTopK();
	return 0;
}