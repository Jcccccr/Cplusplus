#define _CRT_SECURE_NO_WARNINGS 1

//问题：一次可跳1个台阶，一次可跳2个台阶  共有n个台阶，问有多少中跳的方法
#include<iostream>
using namespace std;

//方案一：  递归、但是时间复杂度过大，效率低
int jumpFloor(int number)
{
	if (number == 0)
		return 1;
	if (number == -1)
		return 0;
	return jumpFloor(number - 1) + jumpFloor(number - 2);
}
void test(void)
{
	cout<<jumpFloor(20)<<endl;
}
int main()
{
	test();
	return 0;
}