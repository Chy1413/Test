#define _CRT_SECURE_NO_WARNINGS 1
#include"Sort.h"
#include<stdlib.h>
#include<string.h>
#include"Stack.h"

//插入排序
void InsertSort(int* a, int n)
{
	for (int i = 0; i < n-1; i++)
	{
		int end = i;
		int tmp = a[end + 1];
		while (end >= 0)
		{
			if (a[end] > tmp)
			{
				a[end + 1] = a[end];
				end--;
			}
			else
				break;
		}
		a[end+1] = tmp;
	}
}

//希尔排序
void Swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
void ShellSort(int* a, int n)
{
	int  gap = n;
	while (gap > 1)
	{
		gap = gap/3+1;
		for(int i=0;i<n-gap;i+=gap)
		{
			int end = i; int tmp = a[end + gap];
			while (end >= 0)
			{
				if (a[end] > tmp)
				{
					a[end + gap] = a[end];
					end -= gap;
				}
				else
					break;
			}
			a[end + gap] = tmp;
		}
		
	}
	
}

// 选择排序
void SelectSort(int* a, int n)
{
	int begin = 0, end = n - 1;
	int min, max;

	while (begin <= end)
	{
		min = max = begin;
		int i = begin+1;
		while (i <= end)
		{
			if (a[i] < a[min])
			{
				min = i;
			}
			if (a[i] > a[max])
			{
				max = i;
			}
			i++;
		}
		Swap(&a[begin], &a[min]);
		if (max == begin)
		{
			max = min;	
		}
		Swap(&a[end], &a[max]);
		begin++;
		end--;
	}
}

// 堆排序
void AdjustDwon(int* a, int n, int root)
{
	int parent = root;
	int minchild = parent * 2 + 1;
	while (minchild < n)
	{
		if (minchild + 1 < n && a[minchild] > a[minchild + 1])
		{
			minchild++;
		}
		if (a[parent] > a[minchild])
		{
			Swap(&a[parent], &a[minchild]);
			parent = minchild;
			minchild = parent * 2 + 1;
		}
		else
			break;
	}
}
void HeapSort(int* a, int n)
{
	for (int i = (n - 2) / 2; i >= 0; i--)
	{
		AdjustDwon(a, n, i);
	}
}


int GetMid(int* a, int left, int right)
{
	int mid = (right + left) / 2;
	if (a[mid] < a[right])
	{
		if (a[mid] > a[left])
		{
			return mid;
		}
		else if (a[right] < a[left])
		{
			return right;
		}
		else
			return left;
	}
	else//a[mid]>a[right]
	{
		if (a[right] > a[left])
			return right;
		else if (a[left] > a[mid])
			return mid;
		else
			return left;
	}
}
// 快速排序递归实现
// 快速排序hoare版本
int PartSort1(int* a, int left, int right)
{
	int keyi = GetMid(a,left,right);
	Swap(&a[keyi], &a[left]);
	keyi = left;
	while (left < right)
	{
		while(a[right] >= a[keyi]&& left < right)
		{
			right--;
		}
		
		while (a[left] <= a[keyi]&&left < right)
		{
			left++;
		}
		if (left < right)
			Swap(&a[left], &a[right]);
		else
			Swap(&a[keyi], &a[left]);
	}
	return left;
}
// 快速排序挖坑法
int PartSort2(int* a, int left, int right)
{
	int hole = GetMid(a, left, right);
	Swap(&a[hole], &a[left]);
	hole = left;
	int key = a[hole];
	while (left < right)
	{
		while (a[right] >= key && left < right)
		{
			right--;
		}
		
		a[hole] = a[right];
		hole=right;
		
		while (a[left] <= key && left < right)
		{
			left++;
		}
		
		
		a[hole] = a[left];
		hole=left;
		
	}
	a[hole] = key;
	return hole;
}
// 快速排序前后指针法
int PartSort3(int* a, int left, int right)
{
	int keyi = GetMid(a, left, right);
	Swap(&a[keyi], &a[left]);
	keyi = left;
	int key = a[left];
	int pre = left, cur = left + 1;
	while (cur <= right)
	{
		if (a[cur] < key && ++pre != cur)
		{
			Swap(&a[cur], &a[pre]);
		}
		cur++;
	}
	Swap(&a[left], &a[pre]);
	return pre;
}
void QuickSort(int* a, int left, int right)
{
	if (left >= right)
		return;
	int key=PartSort3(a, left, right);
	QuickSort(a, left, key - 1);
	QuickSort(a, key + 1, right);
}

// 快速排序 非递归实现
void QuickSortNonR(int* a, int left, int right)
{
	Stack St;
	StackInit(&St);
	StackPush(&St, left);
	StackPush(&St, right);
	while (!StackEmpty(&St))
	{
		int right = StackTop(&St);
		StackPop(&St);

		int left = StackTop(&St);
		StackPop(&St);
		if (left >= right)
			continue;
		int key = PartSort3(a, left, right);

		StackPush(&St, key + 1);
		StackPush(&St, right);

		StackPush(&St, left);
		StackPush(&St, key - 1);
	}
	StackDestroy(&St);
}

//归并排序
void _MergeSort(int* a,int*tmp, int left,int right)
{
	if (left >= right)
		return;
	int mid = (left + right) / 2;
	int begin1 = left, end1 = mid ;
	int begin2 = mid + 1, end2 = right;

	_MergeSort(a, tmp,begin1, end1);
	_MergeSort(a, tmp,begin2, end2);
	ShellSort(a + left, right - left + 1);
	strncpy(tmp, a + left, 4 * (right - left+1));
}
void MergeSort(int* a, int n)
{
	int* tmp = (int*)malloc(sizeof(int) * n);
	_MergeSort(a, tmp,0, n);
	strcpy(a, tmp);
}


