#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<assert.h>
using namespace std;

//1.选择排序： 一次选择一个&一个选两个
//2.堆排

//选择排序  -----一次选择一个数字
void ChoseSort1(int* a,size_t size)
{
	assert(a);
	int begin = 0;
	int end = size - 1;
	while (begin != end)
	{
		int minindex = begin;
		for (int i = begin; i <= end; i++)
		{
			if (a[i] < a[minindex])
				minindex = i;
		}
		swap(a[begin], a[minindex]);
		begin++;
	}
}

//一次选择两个数作为最大和最小
void ChoseSort2(int* a, size_t size)
{
	assert(a);
	assert(size);
	int begin = 0;
	int end = size - 1;
	while (begin != end)
	{
		int minindex = begin;
		int maxindex = end;
		for (size_t i = 0; i <= end; i++)
		{
			if (a[i] < a[minindex])
				minindex = i;
			if (a[i]>a[maxindex])
				maxindex = i;
		}
		swap(a[begin], a[minindex]);
		swap(a[end], a[maxindex]);
		begin++;
		end--;
	}
}


//堆排序【*】
void AdjustDown(int* a,size_t _start,size_t _end)    //向下调整算法
{
	int parent = _start;
	int left = parent * 2 + 1;
	int right = left + 1;
	int child = 0;
	if (right <= _end)
	{
		child = (a[left] > a[right] ? left : right);
	}
	else
		child = left;
	while (child <= _end)          //闭区间，刚开始是开区间，错了
	{
		if (a[child] > a[parent])
			swap(a[child], a[parent]);
		else
			break;
		parent = child;
	    left = parent * 2;
		right = parent * 2 + 1;
		if (right <= _end)
		{
			child = a[left] > a[right] ? left : right;
		}
		else
			child = left;
	}
}
void HeapSort(int* a,size_t size)
{
	assert(a);
	assert(size);
	int end = size - 1;
	while (end)
	{
		int start = (end - 1) / 2;           //注意括号
		while (start >= 0)                   //单趟：选出最大值  start=0的时候范围没考虑进去
		{
			AdjustDown(a, start, end);
			start--;
		}
		swap(a[0], a[end]);
		end--;
	}
}
void test()
{
	int arr[] = { 3, 6, 5, 2, 0, 9, 1, 8 };
    //ChoseSort1(arr, sizeof(arr) / sizeof(arr[0]));
	HeapSort(arr, sizeof(arr) / sizeof(arr[0]));
	for (size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}
int main()
{
	test();
	return 0;
}