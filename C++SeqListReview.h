
//*********************************************
//*                                     
//*    作品名称：动态顺序表的创建和基本操作
//*    工程日期： 2017年7月15日
//*    版本号：1.1
//*    作者：鞠鑫
//*
//*********************************************



#define _CRT_SECURE_NO_WARNINGS 1

#ifndef __C__SEQLISTREVIEW_H__

#define __C__SEQLISTREVIEW_H__    //编译预处理中的条件编译中如果使用++符号就编译通过为什么？

#endif

#include<iostream>
#include<assert.h>
using namespace std;

//C++实现动态顺序表
typedef int Datatype;
class SeqList
{
private:
	Datatype* _a;
	size_t _size;
	size_t _capacity;
public:
	SeqList()                 //构造
		:_a(NULL)
		, _size(0)
		, _capacity(0)
	{
		cout << "构造顺序表" << endl;
	}

	SeqList(const SeqList& s)   //拷贝构造
	{
		if (s._a == NULL)
			_a == NULL;

		Datatype* tmp = new Datatype[s._size];     //拷size还是拷capacity？
		for (size_t i = 0; i < s._size; i++)       //在增容的时候为什么不使用malloc  在拷贝的时候为什么不使用memcpy  memecpy是一种浅拷贝。            
		{
			tmp[i] = s._a[i];     //[]的优先级> .
		}
		_size = s._size;
		_capacity = s._capacity;
		_a = tmp;
	}

	SeqList& operator=(const SeqList& s)    //赋值运算符重载    考察的重点
	{
		if (this == &s)    //防止自赋值
		{
			return *this;
		}
		if (s._a == NULL)
		{
			_a = NULL;
			return *this;
		}
		if (_a)            //如果被赋值的对象存在元素，就将元素进行析构  指针赋NULL，再进行赋值操作。防止内存泄漏
		{
			delete[] _a;
			_a = NULL;
			_size = _capacity = 0;
		}
		Datatype* tmp = new Datatype[s._size];
		for (size_t i = 0; i < s._size; i++)
		{
			tmp[i] = s._a[i];
		}
		_size = s._size;
		_capacity = s._capacity;
		_a = tmp;
		return *this;
	}
	//增容
	void CheckCapacity()
	{
		if (_size >= _capacity)
		{
			_capacity = _capacity * 2 + 3;                   //增容的时候我如果使用_capacity*2+1增容方式增容方式增容，在delete[]的时候就出错了为什么？
			Datatype* newarr = new Datatype[_capacity];
			for (size_t i = 0; i < _size; i++)
			{
				newarr[i] = _a[i];
			}
			delete[] _a;             //将原来的内容进行析构
			_a = newarr;
		}
	}
	//尾插
	void PushBack(const Datatype& data)     //注意這里的const和引用
	{
		if (_a == NULL)
		{
			_a = new Datatype(data);
			_size++;
			_capacity++;
			return;
		}
		CheckCapacity();
		_a[_size] = data;
		_size++;
	}
	//析构
	~SeqList()
	{
		if (_a)
		{
			delete[] _a;
			_a = NULL;
		}
		_size = _capacity = 0;
	}
	//打印
	void Print()
	{
		if (_a == NULL)
			return;
		for (size_t i = 0; i < _size; i++)
		{
			cout << _a[i] << " ";
		}
		cout << endl;
	}
};
