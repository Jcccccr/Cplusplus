//#include<stdio.h>
//int main()
//{
//	int i = 43;
//	printf("%d\n", printf("%d", printf("%d", i)));  //這里的值为啥输出来时4321呢？
//	system("pause");
//	return 0;
//
//}

#include<stdio.h>
int main()
{
	int m;
	m = printf("%d", 1234);              //printf（）是一个函数 函数都是有返回值的，那么這个函数的返回值是多少？ 如果我再输出一个换行那么结果又是多少？
	printf("%d", m);
	system("pause");
    return 0;
}


