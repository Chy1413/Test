#define _CRT_SECURE_NO_WARNINGS 1
#include"Heap.h"
#include<stdlib.h>
#include<stdbool.h>
#include<stdio.h>
#include<assert.h>
#include<time.h>


//打印
void Print(Heap* hp)
{
	int i = 0;
	while (i < hp->_size)
	{
		printf("%d ", hp->_a[i]);
		i++;
	}
	printf("\n");
}

void Swap(HPDataType* p, HPDataType* q)
{
	HPDataType x = *p;
	*p = *q;
	*q = x;
}

//容量检查
void CheckCapacity(Heap* hp)
{
	if (hp->_capacity == hp->_size)
	{
		int NewCapacity = 2 * hp->_capacity;
		HPDataType* p = (HPDataType*)realloc(hp->_a,sizeof(HPDataType) * NewCapacity);
		if (p == NULL)
			exit(-1);
		hp->_a = p;
	}
}
//向下调整
void AdjustDown(HPDataType* a, int n, int parent)
{
	assert(a != NULL);
	int minchild = parent * 2 + 1;
	while (minchild < n)
	{
		if (minchild + 1 < n && a[minchild + 1] < a[minchild])
		{
			minchild++;
		}
		if (a[minchild] < a[parent])
		{
			Swap(&a[minchild], &a[parent]);
			parent = minchild;
			minchild = parent * 2 + 1;
		}
		else
			break;
	}
}
//向上调整
void AdjustUp(HPDataType *a,int child)
{
	int parent = (child - 1) / 2;
	while ( child> 0)
	{
		if (a[parent] > a[child])
		{
			Swap(&a[parent], &a[child]);
			child = parent;
			parent = (child - 1) / 2;
		}
		else
			break;
	}
}
//堆的初始化
void HeapInit(Heap* hp)
{
	hp->_a = (HPDataType*)malloc(sizeof(HPDataType)*Capacity);
	hp->_capacity = Capacity;
	hp->_size = 0;
}
// 堆的构建
void HeapCreate(Heap* hp, HPDataType* a, int n)
{
	if (n > Capacity)
	{
		;
	}
	assert(hp != NULL);
	assert(a != NULL);
	int parent = (n - 1 - 1) / 2;
	while (parent >= 0)
	{
		AdjustDown(a, n, parent);
		parent--;
	}
	int i = 0;
	while (i < n)
	{
		int tmp= *(a + i);
		hp->_a[hp->_size] = tmp;
		i++;
		hp->_size++;
	}
}


// 堆的销毁
void HeapDestory(Heap* hp)
{
	free(hp->_a);
	free(hp);
	hp = NULL;
}
// 堆的插入
void HeapPush(Heap* hp, HPDataType x)
{
	assert(hp != NULL);
	CheckCapacity(hp);
	hp->_a[hp->_size] = x;
	hp->_size++;
	AdjustUp(hp->_a, hp->_size - 1);
}
// 堆的删除
void HeapPop(Heap* hp)
{
	hp->_a[0] = hp->_a[hp->_size - 1];
	hp->_size--;
	AdjustDown(hp->_a, hp->_size, 0);
}

// 取堆顶的数据
HPDataType HeapTop(Heap* hp)
{
	assert(hp != NULL);
	assert(hp->_size != 0);
	return hp->_a[0];
}
// 堆的数据个数
int HeapSize(Heap* hp)
{
	assert(hp != NULL);
	return hp->_size;
}
// 堆的判空
int HeapEmpty(Heap* hp)
{
	assert(hp != NULL);
	return hp->_size == 0 ? 0 : 1;
}

// TopK问题：找出N个数里面最大/最小的前K个问题。
// 比如：未央区排名前10的泡馍，西安交通大学王者荣耀排名前10的韩信，全国排名前10的李白。等等问题都是Topk问题，
// 需要注意：
// 找最大的前K个，建立K个数的小堆
// 找最小的前K个，建立K个数的大堆

//建立小堆，找最大的前k个
void PrintTopK(int* a, int n, int k)
{
	Heap* hp = (Heap*)malloc(sizeof(Heap));
	HeapInit(hp);
	HeapCreate(hp, a, k);
	int i = k;
	while (i < n)
	{
		if (a[i] > hp->_a[0])
		{
			hp->_a[0] = a[i];
			AdjustDown(hp->_a, k, 0);
		}
		i++;
	}
	Print(hp);
	free(hp->_a);
	free(hp);
	hp = NULL;
}
void TestTopk()
{
	srand(time(0));
	int* arr = (int*)malloc(sizeof(int) * TopMax);
	int i = 0; int tmp = 0;
	while (i < TopMax)
	{
		tmp = rand() % (100001);
		arr[i] = tmp;
		i++;
	}
	PrintTopK(arr, TopMax, 10);

}
//建立文件，存放数据
void FileCreat(const char* filename, int N)
{
	FILE* fout = fopen(filename, "w");
	if (fout == NULL)
	{
		perror("fopen failed");
		return;
	}
	srand(time(0));
	for (int i = 0; i < N; i++)
	{
		fprintf(fout, "%d ", rand() % 10000);
	}
	fclose(fout);

}
//通过文件方式输入数据，寻找最大的前K个
void FileTopK()
{
	const char* filename = "Data";
	int k=0;
	printf("请输入所需要找到的最大的前K个数：");
	scanf("%d",&k);
	FileCreat(filename, TopMax);


	int arr[100],i=0;
	FILE* fp = fopen(filename, "r");
	if(fp==NULL)
	{
		perror("fopen failed");
		return;
	}
	while (i<k)
	{
		fscanf(fp, "%d", &arr[i]);
		i++;
	}

	Heap *hp=(Heap*)malloc(sizeof(Heap));
	HeapInit(hp);
	HeapCreate(hp, arr, k);
	int tmp = 0;
	while (fscanf(fp, "%d", &tmp) != EOF)
	{
		if (tmp>hp->_a[0])
		{
			hp->_a[0] = tmp;
			AdjustDown(hp->_a, k, 0);
		}
	}
	Print(hp);
	free(hp->_a);
	free(hp);
	hp = NULL;
	fclose(fp);
}