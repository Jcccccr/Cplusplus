#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<string>
using namespace std;
//泛型编程——动态顺序表+ 特化
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
		T* tmp = new T[s._capacity];                      //在C++里面  多用new 少用malloc realloc  因为对于一些内置类型可能不需要构造  而对于自定义类型
		//memcpy(tmp, s._str, sizeof(T)*s._size);             //我们在开辟空间之后必定需要构造初始化之后才能进行拷贝  赋值
		for (size_t i = 0; i < s._size; i++)
		{
			tmp[i] = s._str[i];             //這里面相比于前面的memcpy有了不同  让string自己拷贝过去（深）而不是单单的值拷贝 
		}
		_str = tmp;
		_size = s._size;
		_capacity = s._capacity;
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
		//memcpy(tmp, s._str, sizeof(T)*s._size);
		for (size_t i = 0; i < s._size; i++)
		{
			tmp[i] = s._str[i];
		}
		_str = tmp;
		_size = s._size;
		_capacity = s._capacity;
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
		T* tmp = new T[_capacity];            //這里运行发现增容之后变成随机值 后来我才反应过来new是重开空间 realloc是增容如果地方不够再重新开而且会吧之前的值考过来 
		/*	memcpy(tmp, _str, sizeof(T)*_size);  */  //拷数据
		for (size_t i = 0; i < _size; i++)
		{
			tmp[i] = _str[i];                 //memcpy实际上是一种浅拷贝  也就是说我们再拷贝的时候只是把string的值考下来 然后却忽略了会调用string的析构函数 之后找不到這个对象
		}
		delete[] _str;                      //在使用new进行增容的时候记得要把原来的空间释放
		_str = tmp;
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





//特化就是特殊化，   为了特殊类型特殊处理
//1. 全特化
template<>
class SeqList<int>     //实际上這里這个东西到底算是类名还是类型也不知道   但是是类型肯定是没错的   
{                      //全特化之后类域里面的成员函数不在需要模板参数  所有的T替换成需要特化的数据类型
private:
	int* _str;
	size_t _size;
	size_t _capacity;
public:
	SeqList();
	~SeqList();
	SeqList(const SeqList<int>& s);
	SeqList<int>& operator=(const SeqList<int>& s);
	void CheckCapcity();
	void PushBack(int s);
	void PopBack();
	void PushFront(int s);
	void PopFront();
	int  Find(int s);
	void Insert(int s);
	void Erase(int s);
	void Print();
};
  //template<>    在這里可以不写這个东西了  没有必要
SeqList<int>::SeqList()
:_str(NULL)
, _size(0)
, _capacity(0)
{

}

SeqList<int>::SeqList(const SeqList<int>& s)
{
	if (s._str)
	{
		int* tmp = new int[s._capacity];                      //在C++里面  多用new 少用malloc realloc  因为对于一些内置类型可能不需要构造  而对于自定义类型
		//memcpy(tmp, s._str, sizeof(T)*s._size);             //我们在开辟空间之后必定需要构造初始化之后才能进行拷贝  赋值
		for (size_t i = 0; i < s._size; i++)
		{
			tmp[i] = s._str[i];             //這里面相比于前面的memcpy有了不同  让string自己拷贝过去（深）而不是单单的值拷贝 
		}
		_str = tmp;
		_size = s._size;
		_capacity = s._capacity;
	}
}

//template<>
SeqList<int>& SeqList<int>::operator=(const SeqList<int>& s)
{
	if (s._str)
	{

		if (_str)
		{
			delete[] _str;
			_size = 0;
			_capacity = 0;
		}
		int* tmp = new int[s._capacity];
		//memcpy(tmp, s._str, sizeof(T)*s._size);
		for (size_t i = 0; i < s._size; i++)
		{
			tmp[i] = s._str[i];
		}
		_str = tmp;
		_size = s._size;
		_capacity = s._capacity;
		//记住有返回值
	}
	return *this;
}
//template<class T>
void SeqList<int>::CheckCapcity()
{
	if (_size >= _capacity)
	{
		_capacity = _capacity * 2 + 3;
		int* tmp = new int[_capacity];            //這里运行发现增容之后变成随机值 后来我才反应过来new是重开空间 realloc是增容如果地方不够再重新开而且会吧之前的值考过来 
		/*	memcpy(tmp, _str, sizeof(T)*_size);  */  //拷数据
		for (size_t i = 0; i < _size; i++)
		{
			tmp[i] = _str[i];                 //memcpy实际上是一种浅拷贝  也就是说我们再拷贝的时候只是把string的值考下来 然后却忽略了会调用string的析构函数 之后找不到這个对象
		}
		delete[] _str;                      //在使用new进行增容的时候记得要把原来的空间释放
		_str = tmp;
	}
}

//template<class T>
void SeqList<int>::PushBack(int s)             //注意成员函数的类外定义   刚开始写错了
{
	CheckCapcity();
	_str[_size] = s;
	_size++;
}

//template<class T>
void SeqList<int>::PopBack()
{
	_size--;
}
//template<class T>
void SeqList<int>::PushFront(int s)
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

//template<class T>
void SeqList<int>::PopFront()
{
	size_t i = 0;
	for (i = 0; i < _size; i++)
	{
		_str[i] = _str[i + 1];
	}
	_size--;
}

//template<class T>
int  SeqList<int>::Find(int s)
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
//template<class T>
void SeqList<int>::Print()
{
	size_t i = 0;
	for (i = 0; i < _size; i++)
	{
		cout << _str[i] << " ";
	}
	cout << endl;
}

//template<class T>
SeqList<int>::~SeqList()
{
	if (_str)
	{
		delete[] _str;
		_size = 0;
		_capacity = 0;
	}
}


void test()
{
	SeqList<int> s1;   //通过调试可以看到這里实例化這个对象走的特化版本
	SeqList<double> s2;    //這个对象走的原生版本
}
int main()
{
	test();
	return 0;
}

//2.偏特化（不完全特化）
//实际上：偏特化是对模板参数的进一步限制，所以说对于多个参数的模板，偏特化并非指的特化部分参数，而特化参数的指针或者引用也是一种偏特化

//具体使用例子在课件

