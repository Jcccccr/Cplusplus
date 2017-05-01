#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
//RAII

//当T为内置类型的时候
//template<class T>
//class AutoPtr            //第一版的智能指针
//{
//protected:
//	T* _ptr;
//public:
//	AutoPtr(T* ptr=NULL)
//		:_ptr(ptr)
//	{
//		cout << "原生指针构造智能指针" << endl;
//	}
//	T& operator*()        //'*'的重载   之前都是写的双目运算符的重载，里面除了this还有参数，但是现在是单目运算符，就写错了 记住括号里永远有this
//	{
//		return *_ptr;
//	}
//
//	~AutoPtr()
//	{
//		cout << "释放指针指向的空间" << endl;
//		delete _ptr;
//		_ptr = NULL;
//	}
//
//};
//
//void test()
//{
//	int* pa = new int(4);
//	AutoPtr<int> p1(pa);      //這里相当与 把pa指针所指向的空间的管理权交给了智能指针对象p1 那么之后pa可以不用执行什么操作 一切交给对象p1
//	cout << *p1 << endl;      //這样就能像原生指针一样解引用
//	*p1 = 10;                //为什么我上面的解引用成员函数需要返回T& 如果返回T這里就会执行错误
//	cout << *p1 << endl;
//    
//}
//int main()
//{
//	test();
//	return 0;
//}


// 当T不是内置类型时

struct A         //创建一个A类
{
	int a;
	int b;

};

//template<class T>
//class AutoPtr
//{
//private:
//	T* _ptr;
//public:
//	AutoPtr(T* ptr=NULL)
//		:_ptr(ptr)
//	{
//		cout << "构造智能指针" << endl;
//	}
//	//权限的转移-----AutoPtr
//	AutoPtr(AutoPtr<T>& a)     //拷贝构造函数   這里就不用const修饰了
//	{
//		this->_ptr = a._ptr;
//		a._ptr = NULL;            //這里就是AutoPtr的一个严重缺陷 原来的AutoPtr就不能管理指向的内容了 這样拷贝构造之后会带来一些不便
//	}
//
//	AutoPtr<T>& operator=(AutoPtr<T>& a)
//	{
//		if (this != &a)
//		{
//			delete _ptr;               //我刚开始判空了  其实delete 和 free在遇到NULL指针的时候并不会报错 只不过不去执行 但是這两个不能释放野指针，当然要记住delete和free之后指针置NULL防止野指针
//			_ptr = a._ptr;
//			a._ptr = NULL;
//		}
//		return *this;
//	}
//	T& operator*()        
//	{
//	    return *_ptr;
//	}
//	T* operator->()
//	{
//		return _ptr;
//	}
//	~AutoPtr()
//	{
//		cout << "释放指针所指向的空间" << endl;
//		delete _ptr;
//		_ptr = NULL;
//	}
//
//};
//void test()
//{
//    //如果对于一个原生的A类的指针
//	//A* pp = new A;      //A没构造函数，就不初始化了
//	//(*pp).a = 10;
//	//(*pp).b = 20;
//	//pp->a = 30;
//	//pp->b = 40;
//	//那么以上就是一个原生指针所能完成的一些操作
//	//如果我要将一个原生指针交给一个智能指针进行操作的话 我需要完成同样的事情的话那么我需要重载一些函数来达到我的目的 查处了上面的operator* 我们在這了还需要operator->的重载
//
//
//	A*  pa = new A;
//	AutoPtr<A> p1(pa);      //p1指向一个A类的匿名对象
//	(*p1).a = 10;
//	(*p1).b = 20;          //*的重载能够让自定义类型完成对自己类型内部的成员的访问
//	p1->a = 30;
//	p1->b = 40;            //按道理展开的话就是p1.operator->(this->b)=40,那么简写的话就是 ：p1->->b=40 也就是_ptr->b=40；但是這里有个编译器的优化，为了增强可读性，所以這里就這样写了
//
//	AutoPtr<A> p2(p1);
//	cout << p2->a << endl;
//	AutoPtr<A> p3;
//    p3 = p2;
//	cout << p3->a << endl;
//                    
//}
//int main()
//{
//	test();
//	return 0;
//}
//以上就是模拟了一个智能指针中的AutoPtr   但是我们都知道它其中存在的很严重的设计缺陷





//实际上由于98版的执政指针AutoPtr在拷贝中产生的一些问题，后期智能指针的发展实际上一直在围绕這个问题的解决方案
//  2. ScopedPtr

  //這个就比较粗暴了 ，在這里面拷贝构造函数和赋值只是声明了（而且是保护，类外无法访问）但是没有定义出来 ，
   //很明显了：這个指针就是不让你对智能指针之间进行有关于拷贝的工作，智能构造啊读取数据啊之类

template<class T>
class ScopedPtr
{
protected:
	T* _ptr;
	//防拷贝——————一种方法
protected:
	ScopedPtr(ScopedPtr<T>& a);                     //注意：把這两个接口声明为保护：主要目的是为了防止有人在类外进行定义然后使用 
	ScopedPtr<T>& operator=(ScopedPtr<T>& a);        //如果有成员函数在类内声明为私有，那么在类外是不能对之进行定义的，因为访问不到（之前我一直有误解）

public:
	ScopedPtr(T* ptr = NULL)
		:_ptr(ptr)
	{
		cout << "构造智能指针" << endl;
	}

	T& operator*()        
	{
	    return *_ptr;
	}
	T* operator->()
	{
		return _ptr;
	}
	~ScopedPtr()
	{
		cout << "释放指针所指向的空间" << endl;
		delete _ptr;
		_ptr = NULL;
	}

};

void test()
{
	int* p1 = new int(10);
	ScopedPtr<int>  s1(p1);
	cout << *s1 << endl;
	*s1 = 20;
	cout << *s1 << endl;
	ScopedPtr<A> s2(new A);
	s2->a = 10;
	s2->b = 20;
	(*s2).a = 30;
	(*s2).b = 40;
	//ScopedPtr<A> s3(s2);       //报错：无法访问在protect的成员  
}
int main()
{
	test();
	return 0;
}



//实际上智能指针要满足的条件就是那么两个要素 一是要负责释放指针（因为智能指针实例化出来的对象就是在接收已经创建好的对象啊，只不过一旦出了作用域我就会释放掉）
//二是要能够完成像原生指针那样的功能。    但是就是因为存在问题（拷贝），所以出现了很多不一样的版本，实质上就是這两点

//所谓防拷贝：  1. 只声明，不定义
//              2.声明成私有或者保护，防止有人在类外进行定义操作