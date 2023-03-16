#define _CRT_SECURE_NO_WARNINGS 1
#include"Heap.h"
#include<stdlib.h>
#include<stdbool.h>
#include<stdio.h>
#include<assert.h>
#include<time.h>


//��ӡ
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

//�������
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
//���µ���
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
//���ϵ���
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
//�ѵĳ�ʼ��
void HeapInit(Heap* hp)
{
	hp->_a = (HPDataType*)malloc(sizeof(HPDataType)*Capacity);
	hp->_capacity = Capacity;
	hp->_size = 0;
}
// �ѵĹ���
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


// �ѵ�����
void HeapDestory(Heap* hp)
{
	free(hp->_a);
	free(hp);
	hp = NULL;
}
// �ѵĲ���
void HeapPush(Heap* hp, HPDataType x)
{
	assert(hp != NULL);
	CheckCapacity(hp);
	hp->_a[hp->_size] = x;
	hp->_size++;
	AdjustUp(hp->_a, hp->_size - 1);
}
// �ѵ�ɾ��
void HeapPop(Heap* hp)
{
	hp->_a[0] = hp->_a[hp->_size - 1];
	hp->_size--;
	AdjustDown(hp->_a, hp->_size, 0);
}

// ȡ�Ѷ�������
HPDataType HeapTop(Heap* hp)
{
	assert(hp != NULL);
	assert(hp->_size != 0);
	return hp->_a[0];
}
// �ѵ����ݸ���
int HeapSize(Heap* hp)
{
	assert(hp != NULL);
	return hp->_size;
}
// �ѵ��п�
int HeapEmpty(Heap* hp)
{
	assert(hp != NULL);
	return hp->_size == 0 ? 0 : 1;
}

// TopK���⣺�ҳ�N�����������/��С��ǰK�����⡣
// ���磺δ��������ǰ10�����ɣ�������ͨ��ѧ������ҫ����ǰ10�ĺ��ţ�ȫ������ǰ10����ס��ȵ����ⶼ��Topk���⣬
// ��Ҫע�⣺
// ������ǰK��������K������С��
// ����С��ǰK��������K�����Ĵ��

//����С�ѣ�������ǰk��
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
//�����ļ����������
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
//ͨ���ļ���ʽ�������ݣ�Ѱ������ǰK��
void FileTopK()
{
	const char* filename = "Data";
	int k=0;
	printf("����������Ҫ�ҵ�������ǰK������");
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