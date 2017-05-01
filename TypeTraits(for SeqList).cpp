#define _CRT_SECURE_NO_WARNINGS 1

#include"TypeTraits.h"

void test()
{
	SeqList<int> s1;
	SeqList<double>s2;
	SeqList<size_t>s3;
	SeqList<string>s4;
	//我们可以调试，看看不同类型的对象在运行代码的时候分别走的哪一段
}
int main()
{
	test();
	return 0;
}