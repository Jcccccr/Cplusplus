#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<assert.h>
#include<string>
using namespace std;
//题目描述：  整数N的阶乘结果有多少个0？  
//例如：  N=10，N！=3628800，N的末尾又两个0

//方案一： 暴力求解： 先求阶乘结果，然后一路除模  时间复杂度o（N）  空间复杂度o（1）
int CountNZero(long long num)
{
	assert(num > 0);
	//step1: get the N!
	long long sum = 1;
	size_t ZeroCount = 0;
	while (num && (num - 1))
	{
		sum *= num*(num - 1);
		num -= 2;
	}
	//step2: get the '0'number  in tail of sum
	while (sum)
	{
		if (sum % 10 == 0)
			ZeroCount++;
		sum /= 10;
	}
	return ZeroCount;
}

//--------------------test.c-------------------------------
void test()
{
	cout << CountNZero(10) << endl;
	cout << CountNZero(20) << endl;
	cout << CountNZero(1) << endl;
	cout << CountNZero(8) << endl;
	cout << CountNZero(0) << endl;
	cout << CountNZero(-10) << endl;
}
int main()
{
	test();
	return 0;
}