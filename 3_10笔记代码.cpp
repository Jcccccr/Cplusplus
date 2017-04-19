#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
using namespace std;
//class Array
//{
//private:
//	size_t _sz;         //数组的大小
//	int* _ptr;          //数组首元素地址
//public:
//	Array(size_t sz = 5)
//		: _sz(sz)
//		, _ptr(NULL)
//	{
//		cout << "Array" << endl;
//		if (_sz > 0)
//		{
//			_ptr = new int[_sz];
//		}
//	}
//	~Array()
//	{
//		cout << "~Array" << endl;
//		if (_ptr != NULL)
//		{
//			delete[] _ptr;
//		}
//	}
//};
//int main()
//{
//	//Array a;                        //实例化一个对象a
//	Array* parray = new Array;      //而這里是new出一个指向Array类的指针  都会调用构造函数和析构函数  其实和实例化对象意思差不多
//	delete parray;
//	return 0;
//}  //（对于自定义类型）先开辟空间 在调用构造函数    先调用析构函数 再释放空间



//模拟实现new/delete表达式
//class A
//{
//private:
//	int _a;
//public:
//	A(int a=10)
//	{
//		cout << "A()" << endl;
//	}
//	~A()
//	{
//		cout << "~A()" << endl;
//	}
//};
//int main()
//{
//	A* pa = (A*)operator new(sizeof(A));           //开辟空间
//	new(pa) A(20);                               //定位new表达式  初始化对象指针指向的空间
//	//delete pa
//	pa->~A();                       //调用析构 一次                  
//	return 0;
//}



//模拟实现new[]/delete[]

class A
{
private:
	int _a;
public:
	A(int a=10)
	{
		cout << "A()" << endl;
	}
	~A()
	{
		cout << "~A()" << endl;
	}
};
int main()
{
	/*A* pa = new A[10];
	delete[] pa;*/
	A* pa = (A*)operator new(10*sizeof(A)+4);    //pa为首地址    多加4个字节的意思是要存放对象个数 是一个整形
	*(int*)pa = 10;                           //第一个四个字节存放对象个数为10；
	pa = (A*)((int*)pa + 1);                //  跳过存放对象个数的空间位置  注意强制类型转换			强转之后变量就变成了转换后的类型
	int i = 0;
	for (i = 0; i < 10; i++)                 //调用10次构造
	{
		new(pa + i) A;               //new定位表达式：在已经分配好的空间里面调用构造函数初始化一个对象
	}
	for (i = 0; i < 10; i++)                  //调用10次析构
	{
		(pa + i)->~A();
	}
	return 0;
}
//实际上对于自定义类型来说  new/delete的最大特点就是会调用构造和析构 不单单是开辟空间



//C++动态内存管理的几个考点： 1.c和c++的动态内存管理有什么区别分别有什么特征 ？   
//                            2.new([])/delete([])底层如何实现？
//                            3.为什么要成对使用？