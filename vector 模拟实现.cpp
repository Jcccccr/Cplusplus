#define _CRT_SECURE_NO_WARNINGS 1

//模拟STL中的vector
#include<iostream>
#include<assert.h>
#include<string>
#include"TypeTaritsV.h"
using namespace std;


template<class T>
class Vector
{
public:
	typedef T* Iterator;    //std中的vector将数组原生指针作为迭代器，注意：原生指针类型本身就是一个迭代器
	typedef const T* ConstIterator;
	typedef TypeTarits<T>  TypeTarits;
private:
	Iterator _start;
	Iterator _finish;
	Iterator _EndofStorage;
public:
	Vector()
		:_start(NULL)
		,_finish(NULL)
		,_EndofStorage(NULL)
	{
		cout << "构造" << endl;
	}

	Vector(const Vector<T>& v)    //[*]      注意vector里面的拷贝构造的方式   1.深拷贝 2.使用考数据个数而没有选择拷贝容量的方式 3.使用类型萃取
		:_start(NULL)            // 注意： 拷贝构造一定要初始化
		,_finish(NULL)
		,_EndofStorage(NULL)
	{
		Expand(v.Size());          //vector拷贝构造使用了拷贝size的方式   为什么？？？？
		if (TypeTarits::IspodType().get())    //使用类型萃取    std::vector中的实现方式
		{
			memcpy(_start, v._start, sizeof(T)*v.Size());
		}
		for (size_t i = 0; i < v.Size(); i++)    //如果是内置类型，這里可以使用memcpy因为效率高，但是如果是自定义类型就不能使用，所以可以使用类型萃取
		{
			_start[i] = v[i];      //這里调用了[]运算符重载
		}
		_finish = _start + v.Size();
		_EndofStorage = _finish;

	}
	Vector<T>& operator=(const Vector<T>& v)
	{
		if (_start)
			Destory();
		Expand(v.Size());      
		if (TypeTarits::IspodType().get())
		{
			memcpy(_start, v._start, sizeof(T)*v.Size);
		}
		for (size_t i = 0; i < v.Size(); i++)    
		{
			_start[i] = v[i];      
		}
		_finish = _start + v.Size();
		_EndofStorage = _finish;
	
	}

	size_t Capacity()
	{
		return _EndofStorage - _start;
	}
	size_t Capacity() const 
	{
		return _EndofStorage - _start;
	}

	size_t Size()
	{
		return _finish - _start;
	}
	size_t Size() const 
	{
		return _finish - _start;
	}

	void Expand(size_t n)   //[*] 增容 开n个大的空间然后拷数据
	{
		if (n <= Capacity())
			return;
		size_t size = Size();                //对size大小先做保留
		Iterator newstart = new T[n];        //调用T的默认构造函数进行初始化,所以扩容后的

		for (size_t i = 0; i < size; i++)
		{
			newstart[i] = _start[i];
		}

		delete[] _start;                 //我這里已经把_start释放了 如果后面要调用Size()会找不到_start
		_start = newstart;
		//_finish = _start + Size();        我原来这么写出错了。
		_finish = _start + size;
		_EndofStorage = _start + n;
	}

	void PushBack(const T& d)
	{
		if (_finish >= _EndofStorage)
		{
			size_t capacity = Capacity();
			size_t size = Size();
			capacity = capacity + capacity / 2;               //   STL中使用1/2倍增容，但是要考虑特殊情况
			if (capacity < size + 1)
			{
				capacity = size + 1;
			}
			Expand(capacity);
		}
		*_finish = d; //[*]
		_finish++;
	}

	void PopBack()
	{
		if (_start == NULL || Size() == 0)
			return;
		Iterator tmp = _finish-1;
		delete _finish;
		_finish = tmp;
	}

	//resize 的模拟   很重要  
	void Resize(size_t n,const T& d=T())     //  很重要//默认值为缺省值      capacity的值增大了就不会缩小了  
	{
		if (n > Capacity())     //這有问题
			Expand(n);
		size_t size = Size();
		if (n < size)
		{
			Iterator tmp = _start + n;
			while (tmp != _finish)
			{
				tmp->~T();
			}
			_finish = _start + n;
		}
		else
			Iterator tmp = _finish;
		    while (tmp != (_start + n))
		   {
			    *tmp = d;
		   }
			_finish = _start + n;
	}
	void Reverse(size_t n)// 扩容
	{
		Expand(n);
	}

	//注意：這里的插入和删除都会涉及到迭代器失效的问题
	void Insert(Iterator pos, const T& d)
	{
	}
	void Erase(Iterator pos)
	{
	
	}
	Iterator Begin()
	{
		return _start;
	}

	Iterator Begin()const     //为ConstIterator所用
	{
		return _start;
	}

	Iterator End()
	{
		return _finish;
	}

	Iterator End() const
	{
		return _finish;
	}
	//************************************对下标运算符的重载是为了达到类似于迭代器的功效使得Vector对象调用[]实现在类外打印*******************
	//可写
	T& operator[](size_t index)
	{
		if (index >= Size())
		{
			perror("index");
		}
		return _start[index];
	}
	//只读
	const T& operator[](size_t index) const 
	{
		if (index >= Size())                    //注意： 這里的Size()是元素个数
		{
			/*cout << "越界" << endl;
			return NULL;*/
			perror("index");
		}
		return _start[index];
	}

	void Destory()
	{
		delete[] _start;                       //注意细节： delete[]
		_start = NULL;
		_finish = NULL;
		_EndofStorage = NULL;
	}
	~Vector()
	{
		if (_start == NULL)
			return;
		Destory();
		cout << "析构" << endl;
	}
};

// 类外打印
template<class T>
void PrintVector(Vector<T>& v)
{
	//-------------------------使用迭代器打印-------------------------------------
	//Vector<T>::Iterator itv = v.Begin();    
	//while (itv != v.End())              //原生指针本身就是一个迭代器
	//{
	//	cout << *itv << " ";           //因为是原生指针，所以這写++  ！= 不需要重载了 
	//	itv++;
	//}
	//cout << endl;
	//-------------------------使用[]的重载打印------------------------------------
	for (size_t i = 0; i < v.Size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;
	
}
template<class T>      //------------------------------const迭代器实现----------------------------------
void cPrintVector(const Vector<T>& v)
{
	Vector<T>::ConstIterator itv = v.Begin();
	while (itv!=v.End())
	{
		cout << *itv << " ";
		itv++;
	}
}
void test()
{
	Vector<int> v1;
	v1.PushBack(1);
	v1.PushBack(2);
	v1.PushBack(3);
	v1.PushBack(4);
	PrintVector(v1);
	v1.Reverse(10);
	PrintVector(v1);
	//v1.Resize(2);
	Vector<int> v2 = v1;
	PrintVector(v2);
	cPrintVector(v2);
}
int main()
{
	test();
	return 0;
}