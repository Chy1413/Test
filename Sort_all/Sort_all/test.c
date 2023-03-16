#define _CRT_SECURE_NO_WARNINGS 1
#include"Sort.h"

#include<stdlib.h>
#include<stdio.h>
#include<time.h>

void InsertTest(int* a,int n)
{
	
	InsertSort(a, 100);
	for (int i = 0; i < 100; i++)
	{
		printf("%d ",a[i]);
	}
}
void ShellTest(int *a,int n)
{
	ShellSort(a, n);
	for (int i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
}

void SelectTest(int* a, int n)
{
	SelectSort(a, n);
	for (int i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
}

void HeapTest(int* a, int n)
{
	HeapSort(a, n);
	for (int i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
}
void QuickTest(int* a, int n)
{
	QuickSortNonR(a, 0, n - 1);
	for (int i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
}
void MergeSortTest(int* a, int n)
{
	MergeSort(a, n-1);
	for (int i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
}
int main()
{
	srand(time(0));
	int *a=(int *)malloc(sizeof(int)*100000);
	int i = 0;
	int temp = 0;
	for (i; i < 100000; i++)
	{
		temp = rand() % 1000000;
		a[i] = temp;
	}


	//InsertTest(a,100);
	//ShellTest(a, 1000);
	//SelectTest(a, 1000);
	//HeapTest(a, 200);
	//QuickTest(a, 100000);
	//MergeSortTest(a, 100000);
	return 0;
}