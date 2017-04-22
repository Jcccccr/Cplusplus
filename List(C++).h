
//                                 C++ 实现链表
#include<iostream>
using namespace std;
typedef int DataType;
typedef struct ListNode
{
	DataType _data;
	ListNode* _next;
	struct ListNode(DataType d)      //struct的一个构造函数   初始化一个节点
		:_data(d)
		,_next(NULL)
	{
	}
}Node;
class List
{
private:
	Node* _head;
	Node* _tail;
public:
	List()
		:_head(NULL)
		,_tail(NULL)
	{
	}
	List(List& l)               //拷贝构造
	{
		Node* cur = l._head;
		while (cur)
		{
			this->PushBack(cur->_data);
			cur = cur->_next;
		}
		_head = l._head;
		_tail = l._tail;
	}
	void PushBack(DataType d)
	{
		if (_head == NULL)
		{
			_head = new Node(d);
			_tail = _head;
		}
		else
		{
			Node* cur = _head;
			while (cur->_next != NULL)
			{
				cur = cur->_next;
			}
			cur->_next = new Node(d); 
			_tail = cur->_next;
		}
	}
	void PopBack()
	{
		if (_head == NULL)
		{
			cout << "链表为空" << endl;
		}
		else if (_head->_next == NULL)
		{
			delete _head;
			_head = _tail = NULL;
		}
		else
		{
			Node* cur = _head;
			while (cur->_next != _tail)
			{
				cur = cur->_next;
			}
			delete _tail;
			cur->_next = NULL;
			_tail = cur;
		}
	}
		void PushFront(DataType d)
		{                                  
			if (_head == NULL)
			{
				_head = new Node(d);
				_head = _tail;
			}
			else
			{
				Node* tmp = _head;
				_head = new Node(d);
				_head->_next = tmp;
			}
		}
		void PopFront()
		{
			if (_head)
			{

				if (_head->_next == NULL)
				{
					delete _head;
					_head = _tail = NULL;
				}
				else
				{
					Node* tmp = _head;
					_head = _head->_next;
					delete tmp;
				}
			}

		}
		Node* Find(DataType d)
		{
			if (_head == NULL)
			{
				cout << "链表为空" << endl;
			}
			else
			{
				Node* cur = _head;
				while (cur != NULL)
				{
					if (cur->_data == d)
						return cur;
					cur = cur->_next;
				}
				return NULL;
			}
		}
	void Print()
	{
		Node* cur = _head;
		if (_head == NULL)
		{
			cout << "链表为空" << endl;
		}
		else
		{
			while (cur != NULL)
			{
				cout << cur->_data <<" ";
				cur = cur->_next;
			}
		}
		cout << endl;
	}
	~List()
	{
		if (_head)
		{
			if (_head->_next == NULL)
			{
				cout << "析构" << endl;
				delete _head;
				_head = _tail = NULL;
			}
			else
			{
				Node* cur = _head;
				while (cur != NULL)
				{   
					cout << "析构" << endl;
					Node* tmp = cur;
					cur = cur->_next;
					delete tmp;
				}
			}
		}
	}
};

	void test()
	{
		List s1;
		s1.PushBack(1);
		s1.PushBack(2);
		s1.PushBack(3);
		s1.PushBack(4);
		s1.Print();
		s1.PopBack();
		s1.Print();
		s1.PushFront(6);
		s1.PushFront(7);
		s1.PushFront(8);
		s1.PopFront();
		s1.Print();
		cout<<s1.Find(7)<<endl;         //输出地址
		s1.Print();
		List s2(s1);
		s2.Print();
	}