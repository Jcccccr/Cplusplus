#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<string>
#include<assert.h>
using namespace std;

template <class T>
struct ListNode
{
	T _data;
	ListNode<T>* _next;
	ListNode<T>* _prev;
	ListNode(const T& d)   
		:_data(d)
		,_next(NULL)
		,_prev(NULL)
	{
	    
	}
};

template<class T>
struct ListIterator
{
	typedef ListNode<T> Node;
	Node* _node;
	ListIterator(Node* node)
		: _node(node)
	{
		cout << "构造迭代器对象" << endl;     //注意 迭代器不需要写析构函数 它没這个必要 它的任务仅仅是遍历和更改
	}
	T& operator*()
	{
		return _node->_data;            //出了作用域 _node->_data依然存在 所以返回引用
	}
	T* operator->()
	{
		return &(_node->_data);
	}
	ListIterator<T>& operator++()
	{
		_node = _node->_next;
		return *this;
	}
	bool operator!=(ListIterator<T>& l1)
	{
		return  _node != l1._node;
	}
};
//****************************************************************************************************************


template <class T>
class List
{
	typedef ListNode<T> Node;
public:
	typedef ListIterator<T> Iterator;          //在类外需要使用 ，所以为public
private:
	Node* _head;                  //为什么我這里老是写成List<T>*  
	Node* _tail;
public:
	List()
		:_head(new Node(T()))        //這里会显示没有默认构造函数可用；所以這里要传一个匿名数据，记住：类型+( )就是這个类的一个匿名对象，T( )表示T类型的一个匿名对象
		,_tail(_head)
	{
		cout << "构造" << endl;
		_head->_next = _head;
		_head->_prev = _head;
	}

	void PushBack(const T& d)   //在這里不需要考虑没有头节点的问题，直接后插就行了   如果我使用常数传递过来必须要使用const修饰，const修饰的变量就是一个常量
	{
		Node* cur = _tail;
		Node* tmp = new Node(d);
		cur->_next = tmp;
		tmp->_next = _tail;
		cur->_prev = tmp;
		tmp->_prev = cur;
		_tail = tmp;
	}

	Iterator Begin()
	{
		return Iterator(_head->_next);         //  为啥這里要這样返回？ 返回一个Iterator的有值的匿名对象？？
	}
	Iterator End()
	{
		return Iterator(_head);
	}
	~List()
	{
		if (_head)
		{
			cout << "析构" << endl;
			Node* cur = _head;
			while (cur!=_tail)
			{
				Node* tmp = cur;
				cur = cur->_next;
				delete tmp;
			}
			delete _tail;
			_head = NULL;
			_tail = NULL;
		}
	
	}
};
template <class T>
void PrintList(List<T>& l1)
{
	List<T>::Iterator it = l1.Begin();          //這里调用了迭代器的赋值运算符重载  但是迭代器里面没有写，为什么？是因为浅拷贝也没有影响
	while (it != l1.End())
	{
		cout << *it << " ";
		it++;
	}
	cout << endl;
}

void test()
{
	List<int> l1;
	l1.PushBack(1);
	l1.PushBack(2);
	l1.PushBack(3);
	l1.PushBack(4);
	l1.PushBack(5);
	PrintList(l1);
}
int main()
{
	test();
    return 0;
}