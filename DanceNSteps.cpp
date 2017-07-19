#define _CRT_SECURE_NO_WARNINGS 1

//问题：一次可跳1个台阶，一次可跳2个台阶  共有n个台阶，问有多少中跳的方法
#include<iostream>
using namespace std;

//方案一：  递归、但是时间复杂度过大，效率低
//int jumpFloor(int number)
//{
//	if (number == 0)
//		return 1;
//	if (number == -1)
//		return 0;
//	return jumpFloor(number - 1) + jumpFloor(number - 2);
//}
//

//方案二：

int jumpFloor(int number)
{
	//本质是实现一个斐波那契数列：（非递归）
	//n从3开始
	if (number == 0)
		return 0;
	if (number == 1)
		return 1;
	if (number == 2)
		return 2;
	if (number >= 3)
	{
		int t = 0;
		int arr[3] = { 1, 2, t };
		for (int i = 2; i<number; i++)
		{
			arr[2] = arr[0] + arr[1];
			arr[0] = arr[1];
			arr[1] = arr[2];
		}
		return arr[2];
	}
}

//void test(void)
//{
//	cout<<jumpFloor(20)<<endl;
//}
int main()
{
	cout<<jumpFloor(4)<<endl;
	//test();
	return 0;
}