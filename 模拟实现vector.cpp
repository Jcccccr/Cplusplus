#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<string>
#include<assert.h>

using namespace std;

//  模拟STL中的vector练习
template<class T>
class Vector
{
public:
	typedef T* Iterator;
private:
	Iterator _start;
	Iterator _finished;
	Iterator _endofstorage;
public:
	Vector()
		: _start(NULL)
		, _finished(NULL)
		, _endofstorage(NULL)
	{
		cout << "初始化" << endl;
	}

	Vector(const Vector<T>& v)     //注意拷贝构造的时候 vector的设计方案
		:_start(NULL)
		, _finished(NULL)
		, _endofstorage(NULL)
	{
		Iterator tmp = new T[v.Size()];
		for (size_t i = 0; i < v.Size(); i++)
		{
			tmp[i] = v[i];
		}
		_start = tmp;
		_finished = _start + v.Size();
		_endofstorage = _start + v.Capacity();
	}
	void Expand(size_t n)  //增容
	{
		if (n < Capacity())
			return;
		size_t size = Size();
		Iterator tmp = new T[n];
		for (size_t i = 0; i <size ; i++)
		{
			tmp[i] = _start[i];
		}
		delete[] _start;

		_start = tmp;
		_finished = _start + size;
		_endofstorage = _start + n;
	}

	void PushBack(const T& d)
	{
		if (_finished >= _endofstorage)
		{
			size_t capacity = Capacity();
			size_t size = Size();
			capacity = capacity + capacity / 2;
			if (capacity < size + 1)                   //[*]    這个判断是为了什么？ 弄清除
			{
				capacity = capacity + 1;
			}
			Expand(capacity);
		}
		*_finished = d;              //注意這里   通过這里要知道对于vector来说這三个指针的位置分别是指向哪里
		_finished++;
	}

	void PopBack()
	{
		if (_start == NULL || Size() == 0)
			return;
		Iterator tmp = _finished;
		_finished--;
		delete tmp;
	}

	T& operator[](const size_t& index)    //可写
	{
		return _start[index];
	}
	const T& operator[](const size_t& index) const  //只读
	{
		return _start[index];
	}
	void reserve(size_t n)
	{
		Expand(n);
	}
	void resize()             //[*]
	{

	}
	// -----------------迭代器失效-----------
	void Insert(Iterator pos,const T& d)
	{
	
	}
	void Erase(Iterator pos)
	{
	}
	Iterator Begin()
	{
		return _start;
	}
	Iterator End()
	{
		return _finished;
	}
	size_t Size() const                //這里需要使用const实际上是在上面的拷贝构的时候const对象调用const修饰的成员函数
	{
		return _finished - _start;
	}
	size_t Capacity() const
	{
		return _endofstorage - _start;
	}
	
	void Destory()
	{
		if (_start == NULL)
			return;
		delete[] _start;
		_start = _finished = _endofstorage = NULL;
	}
	~Vector()
	{
		Destory();
		cout << "析构" << endl;
	}

};

template<class T>
void PrintVector(Vector<T>& v)
{
	Vector<T>::Iterator it = v.Begin();
	while (it!=v.End())
	{
		cout << *it << " ";
		it++;
	}
	cout << endl;
}


void testVector()
{
	Vector<int> v1;
	v1.PushBack(1);
	v1.PushBack(2);
	v1.PushBack(3);
	v1.PushBack(4);
	v1.PushBack(5);
	v1.PushBack(6);
	PrintVector(v1);
	Vector<int> v2(v1);
	PrintVector(v2);
}
int main()
{
	testVector();
	return 0;
}