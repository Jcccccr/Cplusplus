#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<assert.h>
using namespace std;
//求数组中出现次数超过数组长度一半的数字
//方案一： 排序之后用一个指针指向中间下标处 必定是目标数字 ： 事件复杂度： o（N*lgN）
//方案二： 递归的二分算法实现  时间复杂度： o（N）
//方案三： 利用数组的特性，使用描述变量  遍历一遍数组，时间复杂度：o（N）


//方案一： 递归的二分算法：




//很重要的是要考虑输入的数组是否是满足题目要求的
bool CheckMoreThanHalf(const int* a, int length, int num)
{
	int size = 0;
	for (size_t i = 0; i < length; i++)
	{
		if (a[i] == num)
			size++;
	}
	if (size * 2>length)
		return true;
	else
		return false;
}
//方案三： 利用数组特性 ，带有一定的技巧 
//這个方案的意思就是： 只要输入的数组出现次数最多的元素的次数大于数组长度的一半，這样的方案是一定可以判正确的
int SearchNumInArr(const int* a ,size_t n)
{
	assert(a);                     //考虑输入的指针是否为空
	assert(n);                     //考虑数组的长度是否为0
	int TargeNum = 0;
	int tmpnum = a[0];
	int count = 1;
	for (size_t i = 1; i < n; i++)
	{
		if (a[i] == tmpnum)
			count++;
		else
			count--;
		if (count == 0)
		{
			tmpnum = a[i];
			count = 1;
			TargeNum = a[i];
		}
	}
	if (CheckMoreThanHalf(a, n, TargeNum))
		return TargeNum;
	else
	{
		printf("INPUT ERROR");
		return 0;
	}
}

void test()
{
	//int arr[] = { 1, 2, 3, 2, 2, 2, 4, 5, 2 };
	int arr[] = { 1, 2, 3, 2, 2, 2, 4, 5, 7, 9, 10, 13, 15, 3 };
	size_t size = sizeof(arr) / sizeof(arr[0]);
	cout << SearchNumInArr(arr, size) << endl;
}
int main()
{
	test();
	return 0;
}