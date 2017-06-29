#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>

void bubble_sort(int arr[], int sz)               //冒泡排序
{
	int i = 0;
	int j = 0;
	int tmp = 0;
	for (j = 0; j < sz - 1; j++)
	{

		for (i = 0; i < sz -j-1; i++)          //该程序可以优化：面试的时候最后写最优方案
		{
			if (arr[i] < arr[i + 1])
			{
				tmp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = tmp;
			}
		}
	}
	return;
}
int main()
{
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	int i = 0;
	bubble_sort(arr, sz);
	for (i = 0; i < sz; i++)
	{
		printf("%d ", arr[i]);
	}
	return 0;
}