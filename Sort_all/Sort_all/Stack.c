#define _CRT_SECURE_NO_WARNINGS 1
#include "stack.h"
#include<stdlib.h>
#include<assert.h>
#define DEFSTACKSIZE 100

void CheckCapacity(Stack* ps)
{
	if (ps->size == ps->_capacity)
	{
		ps->_capacity *= 2;
		STDataType* tmp=(STDataType*)realloc(ps->_a, ps->_capacity * sizeof(STDataType));
		if (tmp != NULL)
		{
			ps->_a = tmp;
		}
		else
		{
			perror("realloc failed\n");
			exit(-1);
		}
	}
}

void StackInit(Stack* ps)
{
	ps->_a = (STDataType*)calloc(DEFSTACKSIZE, sizeof(STDataType));
	ps->_capacity = DEFSTACKSIZE;
	ps->size = 0;
}

void StackPush(Stack* ps, STDataType x)
{
	CheckCapacity(ps);

	ps->_a[ps->size] = x;
	ps->size++;
}

void StackPop(Stack* ps)
{
	if (ps->size == 0)
	{
		return;
	}
	ps->size--;
}

STDataType StackTop(Stack* ps)
{
	if (ps->size == 0)
	{
		return (STDataType)0;
	}
	return ps->_a[ps->size - 1];
}

int StackEmpty(Stack* ps)
{
	return ps->size == 0;
}

int StackSize(Stack* ps)
{
	return ps->size;
}

void StackDestroy(Stack* ps)
{
	if (ps->_a)
	{
		free(ps->_a);
		ps->_a = NULL;
		ps->size = 0;
		ps->_capacity = 0;
	}
}