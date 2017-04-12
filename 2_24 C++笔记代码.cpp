#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
using namespace std;


//extern "C" int add(int x, int y);
//int main()
//{
//
//	add(1, 2);
//	cout << add(1,2) << endl;             //当c++程序中要用到外部函数的时候需要extern声明  但是当外部是一个C程序的时候 就需要extern“C”；
//	return 0;
//}


//2.缺省参数 默认参数:

//int Add(int i = 0, int j = 1)
//{
//	return i + j;
//}
//
//int main()
//{
//	int ret = Add(1, 3);
//	cout << ret << endl;
//	return 0;
//}


//3.引用  常引用具有常性，对一个常量可以直接常引用
int main()
{
	const int &num = 10;
	cout << num << endl;
}//C++中的临时变量都具有常属性


////引用解决了很多c中指针的缺陷之处    比如c中的函数参数使用指针在C++中可以采用引用的方式变得更加简洁
//void print(const int& num2)
//{
//	cout << num2 << endl;
//	num2 = 20;
//}
//
//void print(const int *pnum)
//{
//	cout << *pnum << endl;
//	*pnum = 20;
//}
//int main()
//{
//
//
//}   //两者的功能是一样的


//关于常引用   我们上面说了临时变量或者中间变量都需要使用常引用去修饰  

int main()
{
	float d = 1.1f;
	const int &num = d;
	printf("%p\n", &num);
	printf("%p\n", &d); // 这里发现两者的地址是不一样的num這个引用的对象是一个临时变量 （因为中间有了类型转换）所以要常引用避免這快内容被改变
	return 0;
}

//注意：与C中的函数返回栈空间的地址相似，引用作为返回值的时候  千万不要返回局部变量的引用 局部变量在栈空间销毁的同时也随之消失