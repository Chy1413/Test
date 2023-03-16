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
//�ѵĳ�ʼ��
void HeapInit(Heap* hp);
// �ѵĹ���
void HeapCreate(Heap* hp, HPDataType* a, int n);
void Swap(HPDataType* p, HPDataType* q);
void AdjustDown(HPDataType* a, int n, int parent);
// �ѵ�����
void HeapDestory(Heap* hp);
// �ѵĲ���
void HeapPush(Heap* hp, HPDataType x);
// �ѵ�ɾ��
void HeapPop(Heap* hp);
// ȡ�Ѷ�������
HPDataType HeapTop(Heap* hp);
// �ѵ����ݸ���
int HeapSize(Heap* hp);
// �ѵ��п�
int HeapEmpty(Heap* hp);

// TopK���⣺�ҳ�N�����������/��С��ǰK�����⡣
// ���磺δ��������ǰ10�����ɣ�������ͨ��ѧ������ҫ����ǰ10�ĺ��ţ�ȫ������ǰ10����ס��ȵ����ⶼ��Topk���⣬
// ��Ҫע�⣺
// ������ǰK��������K������С��
// ����С��ǰK��������K�����Ĵ��
void PrintTopK(int* a, int n, int k);
void TestTopk();
//���ļ���ʽ�������ݣ�Ѱ��ǰK��
void FileCreat(const char* filename, int N);
void FileTopK();