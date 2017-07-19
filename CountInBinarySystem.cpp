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
		//num = num / 2;
		num = num >> 1;
	}
	cout << count << endl;
	return 0;
}
//這样的方法有问题，当num是负数的时候，就会出现问题。

//方案二：  移位    移位运算不管是正数还是负数，但是麻烦
//int main()
//{
//	int num = 0;
//	cout << "请输入数字：" << endl;
//	cin >> num;
//	int i = 0;
//	int count = 0;
//    for (; i < 32; i++)
//	{
//	     if ((num >> i) & 1 == 1)
//		    count++;
//	}
//	cout << count << endl;
//	return 0;
//}


//方案三： 按位相与   方法巧妙时间复杂度低

//int main()
//{
//	int num = 0;
//	cout << "请输入数字：" << endl;
//	cin >> num;
//	int count = 0;
//	while (num)
//	{
//		num = num&(num - 1);
//		count++;
//	}
//	cout << count << endl;
//	return 0;
//}


