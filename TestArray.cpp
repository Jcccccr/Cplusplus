#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<vector>
using namespace std;
//测试最简单的数组
int main()
{
	char* dst = "hello world";
	char* src = "郭";
	char p[256] = { 0 }; 
	p[-1] = 10;
	cout << p[-1] << endl;
	//int i = 0;
	//while (*src)
	//{
	//	p[*src++] = 1;
	//}
	/*for (int j = 0; j < 20; j++)
	{
		cout << p[j] << endl;
	}*/
	system("pause");
	return 0;
}