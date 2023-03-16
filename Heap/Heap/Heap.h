#pragma once
typedef int HPDataType;
#define Capacity 100
#define TopMax 1000000
typedef struct Heap
{
	HPDataType* _a;
	int _size;
	int _capacity;
}Heap;

void Print(Heap* hp);
//堆的初始化
void HeapInit(Heap* hp);
// 堆的构建
void HeapCreate(Heap* hp, HPDataType* a, int n);
void Swap(HPDataType* p, HPDataType* q);
void AdjustDown(HPDataType* a, int n, int parent);
// 堆的销毁
void HeapDestory(Heap* hp);
// 堆的插入
void HeapPush(Heap* hp, HPDataType x);
// 堆的删除
void HeapPop(Heap* hp);
// 取堆顶的数据
HPDataType HeapTop(Heap* hp);
// 堆的数据个数
int HeapSize(Heap* hp);
// 堆的判空
int HeapEmpty(Heap* hp);

// TopK问题：找出N个数里面最大/最小的前K个问题。
// 比如：未央区排名前10的泡馍，西安交通大学王者荣耀排名前10的韩信，全国排名前10的李白。等等问题都是Topk问题，
// 需要注意：
// 找最大的前K个，建立K个数的小堆
// 找最小的前K个，建立K个数的大堆
void PrintTopK(int* a, int n, int k);
void TestTopk();
//以文件方式输入数据，寻找前K个
void FileCreat(const char* filename, int N);
void FileTopK();