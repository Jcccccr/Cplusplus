#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
#include<assert.h>
using namespace std;


struct _TrueType
{
	bool get()
	{
		return true;
	}
};

struct _FalseType
{
	bool get()
	{
		return false;
	}
};

template<class T>                           //IsPodType：无关紧要的类型
class TypeTraits
{
	typedef  _FalseType IsPodType;
};

template<>
class TypeTraits<int>                       //相对与无数的自定义类型和数不胜数的库类，内置类型占极少数，所以将少数进行特殊化处理，在顺序表代码中允许他们使用memcpy，也是为了提高效率
{
	typedef  _TrueType IsPodType;
};

template<>
class TypeTraits<double>
{
	typedef  _TrueType IsPodType;
};

template<>
class TypeTraits<float>
{
	typedef  _TrueType IsPodType;
};

template<>
class TypeTraits<char>
{
	typedef  _TrueType IsPodType;
};

template<>
class TypeTraits<size_t>
{
	typedef  _TrueType IsPodType;
};

template<class T>
class TypeTraits<T*>                          //這里要注意：实际上我们在特殊化哪些无关紧要的类型，也就是在SeqList里面使用memcpy并不会出现的问题的
{                                           //那些数据类型，而其他的比如标准库中的类型 比如我们自定义的类型  就必须使用for循环拷贝
	typedef  _TrueType IsPodType;               //但是发现为什么這里的T*（或者T&）也是无关紧要的类型呢？  因为T*类型的数据使用memcpy拷贝地址没有什么问题。
};                                            //（貌似T*這里的T只能使用内置类型？，不能是自定义类型或者库里面的）






template<class T>
class SeqList
{
private:
	T* _str;
	size_t _size;
	size_t _capacity;
public:
	SeqList();
	~SeqList();
	SeqList(const SeqList<T>& s);
	SeqList<T>& operator=(const SeqList<T>& s);
	void CheckCapcity();
	void PushBack(T s);
	void PopBack();
	void PushFront(T s);
	void PopFront();
	int  Find(T s);
	void Insert(T s);
	void Erase(T s);
	void Print();
};
template<class T>
SeqList<T>::SeqList()
:_str(NULL)
, _size(0)
, _capacity(0)
{

}
template<class T>
SeqList<T>::SeqList(const SeqList<T>& s)
{
	if (s._str)
	{
		T* tmp = new T[s._capacity];                     

		if (TypeTraits<T>::IsPodType().get())             //使用类型萃取,  利用前面的偏特化 判断实例化的时候的类型是否是无关痛痒的类型
		{
			memcpy(tmp, s._str, sizeof(T)*s._size);
		}   
		else
		{
			for (size_t i = 0; i < s._size; i++)
			{
				tmp[i] = s._str[i];
			}
			_str = tmp;
			_size = s._size;
			_capacity = s._capacity;
		}
	}
}

template<class T>
SeqList<T>& SeqList<T>::operator=(const SeqList<T>& s)
{
	if (s._str)
	{

		if (_str)
		{
			delete[] _str;
			_size = 0;
			_capacity = 0;
		}
		T* tmp = new T[s._capacity];
		if (TypeTraits<T>::IsPodType().get())
		{
			memcpy(tmp, s._str, sizeof(T)*s._size);
		}
		else
		{
			for (size_t i = 0; i < s._size; i++)
			{
				tmp[i] = s._str[i];
			}
			_str = tmp;
			_size = s._size;
			_capacity = s._capacity;
		}
		//记住有返回值
	}
	return *this;
}
template<class T>
void SeqList<T>::CheckCapcity()
{
	if (_size >= _capacity)
	{
		_capacity = _capacity * 2 + 3;
		T* tmp = new T[_capacity]; 
		if (TypeTraits<T>::IsPodType().get())
		{
			memcpy(tmp, _str, sizeof(T)*_size);
		}
		else
		{
			for (size_t i = 0; i < _size; i++)
			{
				tmp[i] = _str[i];
			}
			delete[] _str;
			_str = tmp;
		}
	}
}

template<class T>
void SeqList<T>::PushBack(T s)             //注意成员函数的类外定义   刚开始写错了
{
	CheckCapcity();
	_str[_size] = s;
	_size++;
}

template<class T>
void SeqList<T>::PopBack()
{
	_size--;
}
template<class T>
void SeqList<T>::PushFront(T s)
{
	CheckCapcity();     //要增加数据记住要检测容量
	int i = 0;                           //注意這里面出的错误   在這个递减的循环里面  别用size_t  会造成死循环
	for (i = _size; i >= 0; i--)          //一般运行出不了结果光标跳动 可能陷入死循环
	{
		_str[i + 1] = _str[i];
	}
	_str[0] = s;
	_size++;
}

template<class T>
void SeqList<T>::PopFront()
{
	size_t i = 0;
	for (i = 0; i < _size; i++)
	{
		_str[i] = _str[i + 1];
	}
	_size--;
}

template<class T>
int  SeqList<T>::Find(T s)
{
	size_t i = 0;
	for (i = 0; i < _size; i++)
	{
		if (_str[i] == s)
		{
			return i;   //注意我這里返回的是下标    函数返回值为int      我一开始写成了SeqList<T>* 的返回值
		}
	}
	return NULL;
}
template<class T>
void SeqList<T>::Print()
{
	size_t i = 0;
	for (i = 0; i < _size; i++)
	{
		cout << _str[i] << " ";
	}
	cout << endl;
}

template<class T>
SeqList<T>::~SeqList()
{
	if (_str)
	{
		delete[] _str;
		_size = 0;
		_capacity = 0;
	}
}