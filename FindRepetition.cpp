#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<assert.h>
using namespace std;
// 面试题三：查找数组中重复的数字
//1. 长度为n的数组中的数字的范围是0~n-1  查找出数组中任意一个重复的数字。

//方案一：  快排先排序，然后遍历，可以找到重复，时间复杂度：o（N*logN）   空间复杂度o（1）


//方案二： 建立n个元素的哈希表  映射，查找重复的  时间复杂度o（N）   空间复杂度o（N） 时间复杂度虽然上来了但是牺牲了空间


//方案三： 利用题目条件，如果不存在重复的数字，必定是有序排列的，只要重新排列這个数组，必定能够找到那个重复的数字
//关键是如何做到重排這个数组的时间复杂度控制在o（N）   空间复杂度为o（1）

//int FindRepetition(int *a,size_t n)
//{
//	assert(a);
//	size_t i = 0;
//	for (; i < n; i++)
//	{
//		if (a[i]>n-1)
//		{
//			printf("数组不符合要求\n");
//			return 0;
//		}
//		if (a[i] == i)
//			continue;
//		if (a[i] == a[a[i]])
//			return a[i];
//		else
//			swap(a[i], a[a[i]]);
//	}
//	if (i == n)
//		printf("未找到重复数字\n");
//	return 0;
//}
//void test1()
//{
//	size_t size = 7;
//	int arr[] = { 2, 3, 1, 0, 2, 5, 3 };
//	cout<<FindRepetion(arr, size);
//}
//


/////////////////////////////////////////////////////////////////////////
//2.n+1长度的数组中数字在1~n之内，不能改变原来的数组，查找任意一个重复的数字

//方案一： 這个条件和前面一个不同的是，這个数组里面一定存在重复的数字，上一个不一定
//使用哈希的方式：时间复杂度： o（N）   空间复杂度o（N）

//优化： 方案二 ： 利用一定存在重复数字的特性，不改变数组，采取类似二分查找算法，每次缩小一半的范围
//时间复杂度：o（N*lgN） 空间复杂度o（1）   

int BinarySearch(const int* a, int n, int min, int max, int mid)
{
	assert(max > min);
	size_t i = 0;
	size_t j = 0;
	int count = 0;
	while (max - min > 1)         //while循环走大概lgN次
	{
		for (; i < n; i++)
		{
			if (a[i]>n)
			{
				printf("数组不符合要求\n");
				return 0;
			}
			if (a[i] >= min&&a[i] <= mid)
				count++;
		}
		if (count>(mid - min))
		{
			max = mid;
			mid = max + (min - max >> 1);
			continue;
		}
		else
		{
			min = mid + 1;
			mid = max + (min - max >> 1);
		}
	}
	//循环结束后只剩下两个数，最后遍历一次判断谁重复
	count = 0;
	for (; j < n; j++)
	{
		if (a[i] == a[max])
			count++;
	}
	if (count == 1)
		return a[max];
	else
		return a[min];
}
int FindRepetition2(const int* a,size_t n)     //這里加上const  代码更加严谨
{
	assert(a);
	assert(n);
	int begin = 1;
	int end = n - 1;
	int mid = begin + (end - begin >> 1);
	return BinarySearch(a, n, begin, end, mid);

}
void Test2()
{
	size_t size = 8;
	int arr[] = { 2, 3, 5, 4, 3, 2, 6, 7 };
	cout << FindRepetition2(arr, size) << endl;
}

int main()
{
	Test2();
	//test1();
	return 0;
}