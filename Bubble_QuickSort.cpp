#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<assert.h>
#include<string.h>
using namespace std;


//交换排序—冒泡排序
void Bubble_Sort(int* a,size_t size)
{
	assert(a);
	assert(size);
	int end = size - 1;
	while (end)
	{
		bool flag = false;                //增加标志位，一种优化
		for (int i = 0; i < end; i++)
		{
			if (a[i]>a[i + 1])
			{
				swap(a[i], a[i + 1]);
				flag = true;
			}
		}
		if (flag == false)
			break;
		end--;
	}
}


//快排  递归
//三数取中
int GetMid(int* a, int begin, int end)    //返回下标
{
	assert(a);
	//assert(end);
	if (end - begin < 0)
	{
		perror("indexerr");
		return 0;
	}
	int mid = begin + ((end - begin) >> 1);
	if (a[begin] > a[end])
	{
		if (a[mid] >= a[begin])
			return begin;
		else
		{
			if (a[mid] >= a[end])
				return mid;
			else
				return end;
		}
	}
	else if (a[begin] < a[end])
	{
		if (a[mid] <= a[begin])
			return begin;
		else
		{
			if (a[mid] <= a[end])
				return mid;
			else
				return end;
		}
	}
	else
		return begin;

}
//左右指针
int PartSort(int* a, int left, int right)
{
	assert(a);
	int begin = left;
	int end = right;
	int key = a[end];
	while (begin < end)
	{
		while (begin < end&&a[begin] <= key)    //注意条件：注意是>= 如果是相等的元素的话，很可能就死循环了
		{
			begin++;
		}
		while (begin < end&&a[end] >= key)
		{
			end--;
		}
		if (begin < end)
		swap(a[begin], a[end]);
	}
	if (begin == end)
	{
		swap(a[begin], a[right]);
		return begin;
	}
}
//递归过程
void QuickSort(int* a, int begin, int end)
{
	if (begin < end)
	{
		int MidValueIndex = GetMid(a, begin, end);       //使用三数取中让数组的最后一个值是中间值。
		swap(a[MidValueIndex], a[end]);

		int Mid = PartSort(a, begin, end);
		QuickSort(a, begin, Mid - 1);
		QuickSort(a, Mid + 1, end);
	}
	else
		return;
}

void test()
{
	//测试用例  ，這种使用排序的数组的测试用例，短可测常别测。
	int arr[] = { 5, 4, 3, 1, 6, 5 };
	//int arr[] = { 1, 1, 1, 1, 1, 1 };
	//Bubble_Sort(arr, sizeof(arr) / sizeof(arr[0]));
	QuickSort(arr, 0, sizeof(arr) / sizeof(arr[0]) - 1);
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