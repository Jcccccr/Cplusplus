#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<assert.h>
using namespace std;


//插入排序   不能够一次性确定某个数的位置
//直接插入&希尔排序


void InsertSort(int* a, size_t size)
{
	assert(a);
	int NowIndex = 1;
	while (NowIndex != size)
	{
		int cur = NowIndex - 1;
		int tmp = a[NowIndex];
		while (cur >= 0 && a[cur] > tmp)
		{
			a[cur + 1] = a[cur];
			cur--;
			if (cur < 0)
			{
				a[0] = tmp;
				break;
			}
			if (a[cur] <= tmp)
			{
				a[cur + 1] = tmp;
				break;
			}
		}
		NowIndex++;
	}
}


//希尔排序：  预先排序+直接插入排序

void test(void)
{
	int arr[] = { 5, 6, 1, 0, 9, 3, 4, 2, 8, 7 };
	InsertSort(arr, sizeof(arr) / sizeof(arr[0]));
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