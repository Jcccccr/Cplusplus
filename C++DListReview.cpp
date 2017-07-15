#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<string>
#include<assert.h>
using namespace std;

//C++双向链表复习  带头节点和尾结点
template<class T>
struct  DListNode
{
	T _data;
	DListNode<T>* _next;
	DListNode<T>* _prev;

	DListNode(const T& data)
		:_data(data)
		, _next(NULL)
		, _prev(NULL)
	{
		cout << "构造结点" << endl;
	}
};

template<class T>
class DList
{
	typedef DListNode<T> Node;
private:
	Node* _head;
	Node* _tail;
public:
	DList()
		:_head(new Node(T()))
		,_tail(_head)
	{
		_head->_next = _head;
		_head->_prev = _head;
		cout << "构造链表头结点" << endl;
	}
	DList(const DList<T>& l1)
	{
		_head = new Node(T());
		_tail = _head;
		if (l1._head->_next == l1._head)
		{
			return;
		}
		Node* cur = (l1._head)->_next;
		while (cur != l1._head)
		{
			PushBack(cur->_data);
			cur = cur->_next;
		}
	}
	//赋值运算符重载
	DList<T>& operator=(const DList<T>& l1)
	{
		if (this != &l1)
		{
			if (l1._head->_next == l1._head)
			{
				return *this;
			}
			if (_head->_next != _head)       //当原来的对象不为空的时候，释放原来的空间
			{
				Destory();
			}
			Node* cur = l1._head->_next;
			while (cur != l1._head)
			{
				PushBack(cur->_data);
				cur = cur->_next;
			}
		}
		return *this;
	}
	//尾插
	void PushBack(const T& data)
	{
		Node* newnode = new Node(data);
		_tail->_next = newnode;
		newnode->_prev = _tail;
		newnode->_next = _head;
		_head->_prev = newnode;
		_tail = newnode;
	}
	//头插
	void PushFront(const T& data)
	{
		Node* newnode = new Node(data);
		Node* tmp = _head->_next;
		_head->_next = newnode;
		newnode->_prev = _head;
		newnode->_next = tmp;
		tmp->_prev = newnode;
	}
	void PopBack()
	{}
	void PopFront()
	{}
	Node* Find(const T& data)
	{
		if (_head->_next == _head)
			return NULL;
		else
		{
			Node* cur = _head->_next;
			while (cur != _head)
			{
				if (cur->_data == data)
					return cur;
				cur = cur->_next;
			}
			return NULL;
		}
	}
	//实现随机位置的插入和删除
	void Insert(const T& data,Node* pos)
	{}
	void Erase(Node* pos)
	{}
	bool Empty()
	{
		if (_head->_next == _head)
			return true;
		else
			return false;
    }
	//不销毁头结点的destory
	void Destory()
	{
		Node* cur = _head->_next;
		while (cur != _head)
		{
			Node* tmp = cur;
			cur = cur->_next;
			delete tmp;
		}
		_head->_next = _head;     //记住自己刚开始是怎么构造的，后面还需要回复最初的状态
		_head->_prev = _head;
		_tail = _head;
	}
	~DList()
	{
		Destory();
		delete _head;
		_head = _tail = NULL;
	}
	void Print()
	{
		Node* cur = _head->_next;
		while (cur != _head)
		{
			cout << cur->_data << " ";
			cur = cur->_next;
		}
		cout << endl;
	}
};

//----------------test-----------------------------
void test()
{
	DList<int> d1;
	d1.PushBack(1);
	d1.PushBack(2);
	d1.PushBack(3);
	d1.PushBack(4);
	d1.PushBack(5);
	d1.PushBack(6);
	d1.Print();
	DList<int> d2(d1);
	d2.Print();
	DList<int> d3;
	d3.PushBack(7);
	d3.PushBack(8);
	d3.PushBack(9);
	d3.PushBack(10);
	d1 = d3;
	d1.Print();
}
int main()
{
	test();
	return 0;
}