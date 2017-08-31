#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<assert.h>
#include<vector>
using namespace std;

//题目2： 输入一个整数，例如是15 然后输出和是它的连续正数序列  
void PrintArray(int begin, int end)
{
	if (begin >= end)
		return;
	for (size_t i = begin; i <= end; i++)
	{
		cout << i << " ";
	}
	cout << endl;
}
void GetVectorSumN(size_t N, int& small, int& big)
{
	assert(N);
	small = 1;
	big = 2;
	int middle = (N + 1) / 2;      //注意为什么它是终止条件
	int sum = small + big;
	while (small < middle)
	{
		if (N < 3)
			return;
		if (sum == N)
		{
			PrintArray(small, big);
			big++;
			sum += big;
			continue;
		}
		else if (sum < N)            //如果小了则大的数后移
		{
			big++;
			sum += big;
			continue;
		}
		else                        //如果大了，注意怎么走
		{
			sum -= small;
			small++;
			continue;
		}
	}
}

void test()
{
	int small = 0;
	int big = 1;
	GetVectorSumN(15, small, big);
}
int main()
{
	test();
	return 0;
}