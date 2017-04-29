#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<assert.h>
using namespace std;

//template<class T>
/*typedef struct ListNode
{
T _data;
ListNode<T>* _next;
ListNode<T>* _prev;
ListNode(const T& d)
: _data(d)
, _next(NULL)
, _prev(NULL)
{
}
}Node; */                 //我刚开始这么写  错了 其实我之前写能正确是因为 那时候ListNode既是类型名又是类型  但是要注意有了模板之后类型名和类型不同 


template<class T>                                 //在這里  ListNode是类型名  ListNode<T>是类型  我们用到类型名的地方只有声明类  构造函数名和拷贝构造函数名
struct ListNode
{
	T _data;
	ListNode<T>* _next;
	ListNode<T>* _prev;
	ListNode(const T& d)      //构造函数
		: _data(d)
		, _next(NULL)
		, _prev(NULL)
	{
	}
};                            //所以上面就不能使用typedef 因为typdef后面必须是一个类型  而不是类型名  给类型重新起一个名字



template<class T>
class List
{
	typedef ListNode<T> Node;
private:
	Node* _head;
	Node* _tail;
public:
	List()
		:_head(NULL)
		, _tail(NULL)
	{
	}
	List(const List<T>& s)
		:_head(NULL)
		, _tail(NULL)
	{
		if (s._head)
		{
			Node* cur = s._head;
			while (cur)
			{
				PushBack(cur->_data);
				cur = cur->_next;
			}
		}
	}
	List<T>& operator=(List<T>& s)
	{
		if (_head)
		{
			Destory();
		}
		else if (s._head)
		{
			Node* cur = s._head;
			while (cur)
			{
				PushBack(cur->_data);
				cur = cur->_next;
			}
		}
		else
			_head = _tail = NULL;
		return *this;
	}
	void Destory()
	{
		if (_head == NULL)
		{
			cout << "链表为空" << endl;
			cout << "析构" << endl;
		}
		else if (_head->_next == NULL)
		{
			cout << "析构" << endl;
			delete _head;
			_head = NULL;
		}
		else
		{
			Node* cur = _head;
			while (cur)
			{
				Node* tmp = cur;
				cur = cur->_next;
				delete tmp;
				cout << "析构" << endl;
			}
		}
	}
	~List()
	{
		Destory();
	}
	void PushBack(const T& d);
	void PopBack();
	void PushFront(const T& d);
	void PopFront();
	Node* Find(const T& d);
	void Print();
	bool Empty();
	size_t Size();
	T& Front();                   //這里面我对引用作为返回值的使用依然不太了解
	T& Back();
};

template<class T>
void List<T>::PushBack(const T& d)
{
	if (_head == NULL)
	{
		_head = new Node(d);
		_tail = _head;
	}
	else
	{
		_tail->_next = new Node(d);
		Node* tmp;
		tmp = _tail->_next;
		tmp->_prev = _tail;
		_tail = tmp;
	}
}

template<class T>
void List<T>::PopBack()                            //在类外定义一个函数的形式？  返回值+所在的类型（不是类名！！）::函数（形参返回类型，形参名）
{
	if (_head == NULL)
	{
		cout << "链表为空" << endl;
	}
	else if (_head->_next == NULL)
	{
		delete _head;
		_head = NULL;
	}
	else
	{
		Node* tmp = _tail->_prev;
		tmp->_next = NULL;
		delete _tail;
		_tail = tmp;
	}
}

template<class T>
void List<T>::PushFront(const T& d)
{
	if (_head == NULL)
	{
		_head = new Node(d);
	}
	else
	{
		Node* tmp = new Node(d);
		Node* cur = _head;
		_head = tmp;
		tmp->_next = cur;
		cur->_prev = tmp;
	}


}
template<class T>
void List<T>::PopFront()
{
	if (!_head)
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
		Node* tmp = _head->_next;
		tmp->_prev = NULL;
		delete _head;
		_head = tmp;
	}
}

template<class T>
ListNode<T>* List<T>::Find(const T& d)
{
	if (_head == NULL)
	{
		cout << "链表为空" << endl;
		return NULL;
	}
	else
	{
		Node* cur = _head;
		while (cur)
		{
			if (cur->_data == d)
				return cur;
			cur = cur->_next;
		}
		return NULL;
	}
}

template<class T>
bool List<T>::Empty()
{
	return _head == NULL;

}

template<class T>
size_t List<T>::Size()
{
	size_t count = 0;
	Node* cur = _head;
	while (cur)
	{
		cur = cur->_next;
		count++;
	}
	return count;
}

template<class T>
T&  List<T>::Front()                            //我在這里为什么要返回引用  
{
	assert(_head);
	return _head->_data;

}

template<class T>
T&  List<T>::Back()
{
	assert(_head);                          //对于这些接口  用断言判断一下 就不要if else来了
	return _tail->_data;
}

template<class T>
void List<T>::Print()
{
	if (_head == NULL)
	{
		cout << "链表为空" << endl;
	}
	else
	{
		Node* cur = _head;
		while (cur)
		{
			cout << cur->_data << " ";
			cur = cur->_next;
		}
		cout << endl;
	}
}






//void test()
//{
//	List<int> s1;
//	s1.PushBack(1);
//	s1.PushBack(2);
//	s1.PushBack(3);
//	s1.PushBack(4);
//	s1.PushBack(5);
//	s1.PushBack(6);
//	s1.Print();
//	s1.PopBack();
//	s1.PopBack();
//	s1.PopBack();
//	s1.PopBack();
//	s1.Print();
//	s1.PushFront(0);
//	s1.PushFront(0);
//	s1.PushFront(0);
//	s1.Print();
//	s1.PopFront();
//	s1.PopFront();
//	s1.PopFront();
//	s1.Print();
//	cout << s1.Size() << endl;
//	cout << s1.Empty() << endl;
//	cout << s1.Back() << endl;
//	cout << s1.Front() << endl;
//	List<int> s2(s1);
//	s2.Print();
//	List<int>s3;
//	s3 = s2;
//	s3.Print();
//}
//int main()
//{
//	test();
//	return 0;
//}