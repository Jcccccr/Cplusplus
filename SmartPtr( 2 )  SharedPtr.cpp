#define _CRT_SECURE_NO_WARNINGS 1
//  模拟实现智能指针 SharedPtr

//  在前面有两个有缺陷的智能指针的逼迫下  促使了更牛×的智能指针的诞生，当然了，都是被拷贝问题所迫，
//那么在SharedPtr中，相比于前面不同点就是加入了引用计数（我越来越觉得引用计数很厉害），這样就能顺利解决析构问题和拷贝牺牲

#include<iostream>
#include<assert.h>
#include<string>
using namespace std;

struct S
{
	int a;
	int b;
};

template<class T>
class SharedPtr
{
private:
	T* _ptr;
	int* _refCount;              //引用计数
public:
	SharedPtr(T* ptr=NULL)
		:_ptr(ptr)
		, _refCount(new int(1))       //注意计数空间的初始化
	{
		cout << "构造智能指针" << endl;
	}
	T& operator*()                      //单目
	{
		return *_ptr;
	}
	T* operator->()
	{
		return _ptr;
	}
	SharedPtr(SharedPtr<T>& s)
	{
		if (s._ptr)
		{
			_ptr = s._ptr;
			_refCount = s._refCount;
			(*_refCount)++;
		}
	}
	SharedPtr<T>& operator=(SharedPtr<T>& s)
	{
		if (this != &s)
		{
			if (s._ptr != NULL)
			{
				if (--(*_refCount) == 0)
				{
					delete _ptr;
				}
				_ptr = s._ptr;
				_refCount = s._refCount;
				(*_refCount)++;
			}
		}
		return *this;                        //又忘了
	}
	~SharedPtr()
	{
		if (--(*_refCount) == 0)
		{
			cout << "析构指针指向对象" << endl;
			delete _ptr;
			_ptr = NULL;
		}
	}

};
void test()
{
	SharedPtr<int> p1(new int(10));
	cout << *p1 << endl;
	*p1 = 20;
	cout << *p1 << endl;
	S* ps = new S;
	SharedPtr<S> p2(ps);              //差点把這里看成拷贝构造
	(*p2).a = 10;
	(*p2).b = 20;
	cout << ps->a << endl;
	cout << ps->b << endl;
	p2->a = 30;
	p2->b = 40;
	cout << ps->b << endl;
	SharedPtr<S> p3(new S);
	p3 = p2;
	cout << p3->a << endl;
	cout << p3->b << endl;
	SharedPtr<S> p4(new S[10]);
	SharedPtr<string> p5(new string);
	//SharedPtr<string> p6(new string[5]);    //程序在這里挂掉 想想为什么  智能指针只是负责释放 ，但是T各有不同 对于自定义类型 可以直接delete
}                                          //但是对于c++库类（string）或者一些自定义类型 需要释放空间的同时调用析构函数 使用delete []  
int main()                                  //虽然這里解决了浅拷贝的问题：但是又引入了新的问题
{
	test();
	return 0;
}

//這个问题可以使用仿函数解决，C++的一种用法  這种方法让SharedPtr变得更加稳