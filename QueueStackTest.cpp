#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<string>
#include<stack>
#include<queue>
#include<assert.h>
using  namespace std;


//目标一：实现一个栈要求 push pop min（返回栈中最小值）的时间复杂度是  o（1）
//方案一 ：一个栈
template<class T>
class MyOneStack
{
private:
	stack<T> _stc;
	T Min;
public:
	MyOneStack()       //成员变量调用自己的缺省构造函数
	{
		cout << "构造" << endl;
	}
	void Push(const T& data)
	{
		if (_stc.empty())
		{
			Min = data;
			_stc.push(data);
			_stc.push(data);
			return;
		}
		if (data < Min)
			Min = data;
		_stc.push(data);
		_stc.push(Min);
	}
	void PopMin()                  //注意：每次pop都会pop两次拿最小的元素和栈顶（pop掉最小的元素之后）的元素。這样就实现了功能
	{
		if (_stc.empty())
		{
			return;
		}
		_stc.pop();
		_stc.pop();
	}
};

//方案二： 使用辅助栈
template<class T>
class MyDoubleStack
{
private:
	stack<T> _stac1;
	stack<T> _stac2;
public:
	MyDoubleStack()
	{
	}
	void Push(const T& data)
	{
		if (_stac1.empty() && _stac2.empty())
		{
			_stac1.push(data);
			_stac2.push(data);
			return;
		}
		if (data <= _stac2.top())
		{
			_stac1.push(data);
			_stac2.push(data);
		}
		else
			_stac1.push(data);
		return;
	}
	void Pop()
	{
		if (_stac1.empty())
			return;
		if (_stac1.top() > _stac2.top())
		{
			_stac1.pop();
		}
		else if (_stac1.top() == _stac2.top())
		{
			_stac1.pop();
			_stac2.pop();
		}
	}
	T& GetMin()
	{
		assert(!_stac2.empty());
		return _stac2.top();
	}
};

//目标二：两个栈实现一个队列
template<class T>
class DoublStacQueue
{
private:
	stack<T> _stk1;          //push区
	stack<T> _stk2;          //pop区
public:
	DoublStacQueue()
	{
	}
	void Push(const T& data)   //push只管入栈
	{
		_stk1.push(data);
	}
	void Pop(void)            //当pop区为空的时候，就需要将push区的所有元素入到pop区
	{
		if (_stk1.empty() && _stk2.empty())
		{
			printf("队列为空\n");
			return;
		}
		if (_stk2.empty())  
		{
			while (!_stk1.empty())
			{
				_stk2.push(_stk1.top());
				_stk1.pop();
			}
			_stk2.pop();
			return;
		}
		_stk2.pop();
	}
};


//目标三： 两个队列实现一个栈,不论是在push的时候还是pop的时候，让其中的一个队列为空，就能达到目的
template<class T>
class DoublQueStack
{
private:
	queue<T> _q1;
	queue<T> _q2;
	T   _buf;
public:
	DoublQueStack()
	{
		cout << "构造" << endl;
	}

	void Push(const T& data)
	{
		assert(_q1.empty() || _q2.empty());
		if (_q1.empty() && _q2.empty())    //两个队列都为空
		{
			_q1.push(data);
		}
		else if (_q1.empty() && (!_q2.empty()))     //_q1为空，说明是刚才出栈的队列
		{
			_q2.push(data);
		}
		else
		{
			_q1.push(data);
		}
		return;
	}

	int Pop(void)         //pop依然需要判空  pop的时候不为空的需要转移数据
	{
		if (_q1.empty() && _q2.empty())
		{
			perror("Pop");
		}
		if (_q1.empty() && (!_q2.empty()))
		{
			while (!_q2.empty())
			{
				_buf = _q2.front();
				_q2.pop();
				if (!_q2.empty())
				_q1.push(_buf);
			}
			return _buf;
		}
		if ((!_q1.empty()) && _q2.empty())
		{
			while (!_q1.empty())
			{
				_buf = _q1.front();
				_q1.pop();
				if (!_q1.empty())
					_q2.push(_buf);
			}
			return _buf;
		}
	}

	void Print()
	{
		cout << "出栈：";
		while (!_q1.empty() || !_q2.empty())
		{
			cout << Pop() << " ";
		}
		cout << endl;
	}
};

//目标四： 检验元素出栈入栈的合法性，入栈的顺序为（1，2，3，4，5） 出栈为（4，5，3，2，1）
bool CheckPushPop(int* arr1,size_t lenth1,int* arr2,size_t lenth2)
{
	stack<int>  _stk;
	//情况一： 两个数组的长度都不一样，定是不合法的
	if (lenth1 != lenth2)
		return false;
	int i = 0;
	int j = 0;
	_stk.push(arr1[i]);
	i++;
	while (!_stk.empty())         //用栈为空作为总循环跳出的条件
	{
		while (_stk.top() != arr2[j])
		{
			if (i > lenth1 - 1)
			{
				break;
			}
			_stk.push(arr1[i]);
			i++;
		}
		if (i > lenth1 - 1)
			break;
		j++;
		_stk.pop();
		if (i < lenth1 - 1)
		_stk.push(arr1[i]);
	}
	return _stk.empty() ? true : false;
}

void test1(void)
{
	MyOneStack<int>  _M;
	_M.Push(6);
	_M.Push(3);
	_M.Push(5);
	_M.Push(2);
	_M.Push(9);
	_M.Push(0);
	_M.Push(7);
	_M.Push(1);
	_M.PopMin();
}
void test2(void)
{
	MyDoubleStack<int>  _MD;
	_MD.Push(2);
	_MD.Push(3);
	_MD.Push(6);
	_MD.Push(5);
	_MD.Push(0);
	_MD.Push(9);
	_MD.Push(7);
	_MD.Push(8);
	_MD.Push(1);
	_MD.Push(4);
	_MD.Pop();
	_MD.GetMin();
}

void test3(void)
{
	DoublQueStack<int> _DQ;
	_DQ.Push(1);
	_DQ.Push(2);
	_DQ.Push(3);
	_DQ.Push(4);
	_DQ.Push(5);
	_DQ.Push(6);
	//cout << _DQ.Pop() << endl;
	_DQ.Print();
}

void test4(void)
{
	DoublStacQueue<int>  _DS;
	_DS.Push(1);
	_DS.Push(2);
	_DS.Push(3);
	_DS.Push(4);
	_DS.Push(5);
	_DS.Push(6);
	_DS.Push(7);
	_DS.Push(8);
	_DS.Pop();
	_DS.Pop();
	_DS.Pop();
	_DS.Pop();
	_DS.Pop();
	_DS.Pop();
	_DS.Pop();
	_DS.Pop();
	_DS.Pop();
}

void test5()
{
	int arr1[] = { 1, 2, 3, 4, 5 };
	int arr2[] = { 4, 5, 3, 2, 1 };
	//int arr2[] = { 1, 5, 3, 2, 4 };
	int lenth1 = sizeof(arr1) / sizeof(arr1[0]);
	int lenth2 = sizeof(arr2) / sizeof(arr2[0]);
	int ret=CheckPushPop(arr1, lenth1, arr2, lenth2);
	cout << ret << endl;
}
int main()
{
	test5();
	//test4();
	 //test3();
	//test2();
	//test1();
	return 0;
}