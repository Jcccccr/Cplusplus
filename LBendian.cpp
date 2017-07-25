#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;

//使用联合体判断大小端存储    有坑
void test1()
{
	const int num = 10;
	char* p = (char*)&num;
	if (*p == 0)
		cout << "大端" << endl;
	else
		cout << "小端" << endl;
}

void test2()
{
	union Utest
	{
		int i;
		char a;
	}ut;
	ut.i = 1;          //注意在使用联合判断的时候不能设置char的值来判断int 因为char的值确定了但是空间中剩余的字节空间是随机值，這样int也是随机值无法判断
	if (ut.a==1)
		cout << "小端" << endl;
	else
		cout << "大端" << endl;
}
//下面這个输出多少？？？？  使用联合体判断大小端存储先初始化int（大的）  在看char（小的）  如果反之则为随机值
void test3()
{
	union                 //union好像可以没有联合体类名
	{
		int i;
		char a[2];
	}*p,u;
	
	p = &u;
	p->a[0] = 0x39;
	p->a[1] = 0x38;
	cout << p->i << endl;
}

//小端机下，下面的输出是多少？
void test4()
{
	int a[5] = { 1, 2, 3, 4, 5 };
	int* ptr1 = (int*)(&a + 1);
	int* ptr2 = (int*)((int)a + 1);
	printf("%x,%x", ptr1[-1], *ptr2);
}
int main()
{
	test4();
	return 0;
}