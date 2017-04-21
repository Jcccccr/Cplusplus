#include<iostream>
#include<assert.h>
#include<stdlib.h>
using namespace std;

typedef int DataType;
class SeqList
{  
private:
	DataType* _str;
	size_t _size;
	size_t _capacity;
public:
	SeqList()                   //构造  初始化
		:_str(NULL)
		, _size(0)
		, _capacity(0)
	{
	}
	SeqList(const SeqList& s)            //拷贝构造
	{
		if (s._str)
		{
			_str = new DataType[s._capacity];          //new 不用计算字节数  而且会调构造函数
			memcpy(_str, s._str, sizeof(DataType)*s._size);
			_size = s._size;  
			_capacity = s._capacity;
		}
		else
			_str = NULL;
	}
	SeqList& operator=(const SeqList& s)       //赋值运算符重载
	{
		if (this != &s)
		{
			if (s._str)
			{
				if (_str)
				{
					free(_str);                            //如果被赋值的对象原来已经指向一块空间
				}
					_str = new DataType[s._capacity];
					memcpy(_str, s._str, sizeof(DataType)*s._size);
					_size = s._size;
					_capacity = s._capacity;
				
			}
			else
				_str = NULL;
		}
		return *this;
	}
	void CheckCapacity()                //增容
	{
		if (_size == _capacity)
			/*_str = (DataType*)realloc(_str, sizeof(DataType)* 2 + 3);
		_capacity=? */
		_capacity = _capacity * 2 + 3;
		_str = (DataType*)realloc(_str, sizeof(DataType)*_capacity);
	}
	void PushBack(DataType d)       //头插
	{
		CheckCapacity();
		_str[_size] = d;
		_size++;
	}
	void PopBack()                    //尾删
	{
		_size--;
	}
	void PushFront(DataType d)                         //头插
	{
		CheckCapacity();
		int i = 0;
		for (i = _size; i >= 0; i--)
		{
			_str[i+1] = _str[i];
		}
		_str[0] = d;
		_size++;
	}
	void PopFront()                                     //头删
	{
		size_t i = 0;
		for (i = 0; i < _size - 1; i++)
		{
			_str[i] = _str[i + 1];
		}
		_size--;
	}
	void Print()                                //打印
	{
		size_t i = 0;
		for (i = 0; i < _size; i++)
		{
			cout << _str[i] <<" ";
		}
		cout << endl;
	}
	int  Find(DataType d)                      //查找
	{
		size_t i = 0;
		for (i = 0; i < _size; i++)
		{
			if (_str[i] == d)
				return i;
		}
		return -1;
	}
	~SeqList()                                 //析构
	{
		if (_str)
		{
			free(_str);
			_str = NULL;
			_size = 0;
			_capacity = 0;
		}
	}
};


void test()
{
	SeqList s1;
	s1.PushBack(1);
	s1.PushBack(2);
	s1.PushBack(3);
	s1.PushBack(4);
	s1.PushBack(5);
	s1.PopBack();
	s1.PopFront();
	s1.PushFront(1);
	s1.PushFront(2);
	s1.Print();
	cout << s1.Find(3) << endl;
	SeqList s2(s1);
	s2.PushBack(5);
	s2.PushBack(6);
	s2.PushBack(7);
	s2.PushBack(8);
	s2.PushBack(9);
	s2.Print();
	SeqList s3;
	s3 = s2;
	s3.Print();
	s1 = s3;
	s1.Print();
}

