#define _CRT_SECURE_NO_WARNINGS 1
//求一个二进制数中的1的个数是奇数还是偶数个
#include<iostream>
using namespace std;

int test(int value,int bits)
{
	int count = 0;
	while (bits)
	{
		if (value & 1 == 1)
			count++;
		value = value >> 1;
		bits--;
	}
	return count;
}
int main()
{
	cout << test(10, 32) << endl;
	return 0;
}