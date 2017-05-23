#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
using namespace std;

void teststring()
{                             //我们可以把字符串的指针变量当他单独出现的时候就看做是這个字符串
	char* p = "hahahaha";
	cout << *p << endl;     //這个时候p代表指向首字符地址的指针
	cout << p << endl;             
	string a = "hhhhhhhh";
	cout << a << endl;
	string b = p;
	cout << b << endl;
	string c = "ooooooo";
	cout << c << endl;
	c = p;
	cout << c << endl;
	cout << p + 1 << endl;    //這个时候p就不代表這个字符串
}
int main()
{
	teststring();
	return 0;
}