#define _CRT_SECURE_NO_WARNINGS 1

//利用数组实现一个栈

#include<iostream>
#include<string>
#include<assert.h>
using namespace std;

//静态栈
//静态数组实现
template<class T,size_t N>
class MyStack
{
protected:
	T _a[N];
	size_t size;
public:
	MyStack()
		:size(0)
	{
		cout << "构造" << endl;
	}
	void Push(const T& t)
	{
		if (size > N)
		{
			cout << "out of range" << endl;
			return;
		}
		else
		{
			_a[size] = t;
			size++;
		}
	}
	//這个是這样实现的码？
	void Pop()
	{
		if (_size == 0)
		{
			printf("栈为空\n");
			return;
		}
		size--;
	}
	T& Top()
	{
		assert(_size != 0);
		return _a[size];
	}
	bool Empty()
	{
		if (size == 0)
			return true;
		else
			return false;
	}
};



//动态数组实现的动态栈
template<class T>
class ACStack
{
protected:
	T* _a;
	size_t _size;     //数组元素
	size_t _capacity;  //数组容量  

	//增容[*]       //动态数组的增容方式
	void CheckCapacity()
	{
		if (_size >= _capacity)
			_capacity = _capacity * 2 + 1;           //增容的方式

		T* tmp = new T[_capacity];
		for (size_t i = 0; i < _size; i++)
		{
			tmp[i] = _a[i];
		}
		delete[] _a;
		_a = tmp;
	}
public:
	ACStack()
		:_a(NULL)
		, _size(0)         //注意這样的定义下  size是数组的元素  ，size-1是动态数组的下标  這个意识很重要
		, _capacity(1)
	{
		cout << "构造" << endl;
	}
	//入栈
	void Push(const T& t)
	{
		if (_size > _capacity)
		{
			cout << "out of range" << endl;
			return;
		}
		//在第一次插入元素的时候需要注意 此时_a = NULL
		if (_size == 0)
		{
			_a = new T(t);
			_size++;
			return;
		}
			CheckCapacity();
			_a[_size] = t;
			_size++;  
	}
	//出栈
	void Pop()
	{
		if (_size == 0)
		{
			printf("栈为空\n");
			return;
		}
		_size--;
	}
	T& Top()
	{
		assert(_size != 0);
		return _a[_size - 1];
	}
	bool Empty()
	{
		if (_size == 0)
			return true;
		else
			return false;
	}
	size_t Size()
	{
		return _size;
	}
	void PrintStack()
	{
		if (_size == 0)
		{
			printf("栈为空\n");
			return;
		}
		while (_size)
		{
			cout << Top() << " ";
			Pop();
		}
		cout << endl;
	}
};



//-----------------------test-----------------------------
void TestStack()
{
	//MyStack<int, 10> _stack;
	/*_stack.Push(1);
	_stack.Push(2);
	_stack.Push(3);
	_stack.Push(4);
	_stack.Push(5);
	_stack.Push(6);
	_stack.Push(7);
	_stack.Push(8);
	_stack.Push(9);
	_stack.Push(10);
	_stack.Pop();
	_stack.Pop();
	_stack.Pop();
	_stack.Pop();*/

	ACStack<int>  _stac;
	_stac.Push(0);
	_stac.Push(2);
	_stac.Push(3);
	_stac.Push(4);
	_stac.Push(5);
	_stac.Push(6);
	_stac.Push(7);
	_stac.Push(8);
	//_stac.PrintStack();
	_stac.Pop();
	_stac.Pop();
	_stac.Pop();
	_stac.Pop();
	//_stac.PrintStack();
	_stac.Push(9);
	_stac.Push(9);
	_stac.Push(9);
	_stac.Push(9);
	//_stac.PrintStack();
	_stac.Push(0);
	cout << _stac.Size() << endl;
	cout << _stac.Top() << endl;
}
int main()
{
	TestStack();
	return 0;

}