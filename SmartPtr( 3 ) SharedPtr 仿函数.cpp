#define _CRT_SECURE_NO_WARNINGS 1

//仿函数实际上是一个对象，就是对象模仿函数去完成一些工作 就是类似F（）這样  
//那么就需要进行 operator()的重载，让這个对象可以像函数那样使用，就实现了仿函数。暂时理解就是這样
#include<iostream>
#include<assert.h>
#include<string>
using namespace std;

template<class T>
class deleteArr
{
public:
	void  operator()(T* ptr)         //operator()的重载     注意：没有返回值
	{
		delete[] ptr;
	}
};

template<class T>
class Delete
{
public:
	void  operator()(T* ptr)
	{
		delete ptr;
	}
};


template<class T,class Del=Delete<T>>       //注意這里写 默认的时候怎么写 不能写成类名，必须要写成类型！！！
class SharedPtr
{
private:
	T* _ptr;
	int* _refCount; 
	Del del;                                //這里Del类实例化出一个对象del del可以调用Del类中的成员函数 
public:
	SharedPtr(T* ptr = NULL)
		:_ptr(ptr)
		, _refCount(new int(1))       
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
	SharedPtr(SharedPtr<T, Del>& s)
	{
		if (s._ptr)
		{
			_ptr = s._ptr;
			_refCount = s._refCount;
			(*_refCount)++;
		}
	}
	SharedPtr<T, Del>& operator=(SharedPtr<T, Del>& s)
	{
		if (this != &s)
		{
			if (s._ptr != NULL)
			{
				if (--(*_refCount) == 0)
				{
					del(_ptr);                    //del可以调用Del中的成员函数 默认Del为Delete 那么這个类中只有一个成员函数
				}                                //调用方式为： del.operator()(_ptr); 写出来就是del(_ptr); 所以這里就是调用成员函数而已
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
			del(_ptr);
			_ptr = NULL;
		}
	}

};

void test()
{  //显示实例化
	SharedPtr<int> p1(new int(10));    //這里调用默认模板参数的那个默认值
	SharedPtr<string> p2(new string);
	SharedPtr<string,deleteArr<string>> p3(new string[10]);//因为前面我们已经写出来了deleteArr 所以這里手动调用它，完成delete[]的工作
}
int main()
{
	test();
	return 0;
}