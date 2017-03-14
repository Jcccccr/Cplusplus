#include<iostream>
using namespace std;
inline int Max(int x, int y)//内联函数，其实和C里面的宏定义差不多 #define 但是在C++里面不用宏定义
{
	return x > y ? x : y;
}
int main()
{
	int max = Max(2, 3);//這里其实相当于int max=2>3?2:3;  直接把本应该调用的函数的内容移植到這里来了
	cout << max << endl;
	return 0;
}