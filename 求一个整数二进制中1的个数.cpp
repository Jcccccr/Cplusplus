#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
using namespace std;

//求二进制中的1的个数
//方案一： 除模法
int main()
{
	int num = 0;
	cout << "请输入数字：" << endl;
	cin >> num;
	int count = 0;
	while (num)
	{
		if (num % 2 == 1)       //为啥????  好奇怪
			count++;
		num = num / 2;
	}
	cout << count << endl;
	return 0;
}

//方案二： 移位
