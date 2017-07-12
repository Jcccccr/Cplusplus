#define _CRT_SECURE_NO_WARNINGS 1


//斐波那契的四次优化问题
#include<iostream>
#include<assert.h>
using namespace std;

//******************递归*********************
//斐波那契数列的解法、数列递归的时间复杂度和空间复杂度。
//第一种有问题
int Fibonacci1(int n)
{
	//assert(n);
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;
	return Fibonacci1(n - 1) + Fibonacci1(n - 2);
}

//前面一种解法的优化 ,在实际中也必须要這样写，因为之前的int肯定是存在问题的。
long long Fibonacci2(long long n)
{
	//assert(n);
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;
	return Fibonacci2(n - 1) + Fibonacci2(n - 2);
}
//递归的时间复杂度是O（n^2）   空间复杂度是O（N）




//  **************非递归*****************
//使用数组和循环，把数列放进去  
//时间复杂度是o（N）   空间复杂度：o（N）  ：开辟的空间大小是N个，所以空间复杂度是o（N）
long long FibonacciR1(long long n)
{
	long long* Fibarr = new long long[n + 1];
	Fibarr[0] = 0;
	Fibarr[1] = 1;
	for (long long i = 2; i <= n; i++)
	{
		Fibarr[i] = Fibarr[i - 1] + Fibarr[i - 2];
	}
	return Fibarr[n];
}
//再次优化
//时间复杂度是o（N）  空间复杂度是o（1） 开辟的空间是常数。
long long FibonacciR2(long long n)
{
	long long Fibarr[3] = { 0, 1, n };
	for (long long i = 2; i <= n; i++)
	{
		Fibarr[2] = Fibarr[0] + Fibarr[1];
		Fibarr[0] = Fibarr[1];
		Fibarr[1] = Fibarr[2];
	}
	return Fibarr[2];
}


void test()
{
	/*int num = Fibonacci1(1);
	printf("%d\n", num);*/

	/*long long num = Fibonacci2(4);
	printf("%d\n", num);*/
	
	/*long long num = FibonacciR1(100);
	printf("%d\n", num);*/
	
	long long num = FibonacciR2(3);
	printf("%d\n", num);

}
int main()
{
	test();
	return 0;
}