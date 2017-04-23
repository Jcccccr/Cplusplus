
//                                 C++ 实现链表
#include<iostream>
using namespace std;


typedef int DataType;
typedef struct ListNode              //有点类似于BuyNode     配合下面的new创建一个节点并且初始化
{
	DataType _data;
	ListNode* _next;
	ListNode(DataType d)          //ListNode的一个构造函数   初始化一个节点   在下面使用new的时候会自动调用节点的构造函数
		:_data(d)                                    //相当于一个new Node（d）就把C中链表的BuyNode干的所有事情都干好了  
		,_next(NULL)
	{
	}
}Node;
class List
{
private:
	Node* _head;
	Node* _tail;                   //其实在C里面写链表里面好像没有_tail（尾节点） 但是這里用_tail  在每次操作的时候  _tail也需要做相应的更改
public:                                        //可能目的就是为了在有必要的时候直接用_tail吧 省去每次都要循环找到最后一个或者最后一个的前一个
	List()
		:_head(NULL)
		,_tail(NULL)
	{
	}
	List(const List& l)                       //拷贝构造的时候在初始化列表里面进行初始化 不然在下面调用PushBack函数的时候就会出
		:_head(NULL)
		, _tail(NULL)                 //如果這里不赋值为NULL程序直接挂掉
	{
		Node* cur = l._head;
		while (cur)
		{
			PushBack(cur->_data);         //函数的复用
			cur = cur->_next;
		}
		/*_head = l._head;*/                //我原本是这么写的 没想到居然写出了一个浅拷贝 我上面写的是深拷贝 但是這里这么做确实不应该
		
	}

	List& operator=(const List& l)          //赋值运算符重载
	{
		if (_head)
		{
			Desdroy();              //函数的复用  
		}
		_head = NULL;
		_tail = NULL;
		Node* cur = l._head;
		while (cur)
		{
			PushBack(cur->_data);        
			cur = cur->_next;
		}
		return *this;                    //赋值运算符重载记得返回值
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
	void Desdroy()                         //清空函数    因为要复用它 所以把他单独拿出来写一下
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
	~List()
	{
		if (_head)
		{
			Desdroy();
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
		List s3;
		s3.PushBack(1);
		s3.PushBack(1);
		s3.PushBack(1);
		s3.PushBack(1);
		s3.PushBack(1);
		s2 = s3;
		s2.Print();
	}