#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<assert.h>
using namespace std;

//归并排序
//数组两路归并
void _TwoLineofMerge(int* a, int* tmp, int start1, int end1, int start2, int end2)
{
	int cur1 = start1;
	int cur2 = start2;
	int index = start1;
	while (cur1 <= end1&&cur2 <= end2)
	{
		if (a[cur1] < a[cur2])
		{
			tmp[index++] = a[cur1++];
		}
		else     //cur1 > cur2
		{
			tmp[index++] = a[cur2++];
		}
	}
	//两个数组其中有一个结束了
	while (cur1 <= end1)
	{
		tmp[index++] = a[cur1++];
	}
	while (cur2 <= end2)
	{
		tmp[index++] = a[cur2++];
	}

	//将数据拷贝回原数组
	memcpy(a + start1, tmp + start1, (end2 - start1 + 1)*sizeof(int));    //记住memcpy的单位是字节数      
}
//递归部分
void _MergeSort(int* a, int* tmp, int begin, int end)
{
	if (begin >= end)
		return;
	int Mid = begin + ((end - begin) >> 1);
	_MergeSort(a, tmp, begin, Mid);
	_MergeSort(a, tmp, Mid + 1, end);
	//递归到最深处两路归并
	_TwoLineofMerge(a, tmp, begin, Mid, Mid + 1, end);
}

void MergeSort(int* a,int n)
{
	assert(a);
	int* tmp = new int[n];              //开辟临时数组

	_MergeSort(a, tmp, 0, n - 1);
	delete[] tmp;
}
void test()
{
	int arr[] = { 2, 6, 3, 8, 9, 8, 7, 5, 3, 7, 8 };
	MergeSort(arr, sizeof(arr) / sizeof(arr[0]));
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