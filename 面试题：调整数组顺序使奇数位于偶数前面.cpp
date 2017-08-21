#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<assert.h>
using namespace std;
//调整数组顺序使得奇数位于偶数前面

void ReoederOddEven(int arr[],int length)
{
	assert(arr);
	assert(length);
	int begin = 0;
	int end = length - 1;
	while (begin < end)
	{
		while (arr[begin] % 2)  //奇数
		{
			begin++;
		}
		while (arr[end] % 2 == 0)   //偶数
		{
			end--;
		}
		swap(arr[begin], arr[end]);
	}
}
int main()
{
	int arr[] = { 2, 5, 7, 1, 9, 3, 4, 6 };
	ReoederOddEven(arr, sizeof(arr) / sizeof(arr));
	for (size_t i = 0; i < sizeof(arr) / sizeof(arr); i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
	return 0;
}