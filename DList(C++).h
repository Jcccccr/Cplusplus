

//C++  实现双向链表   在写的时候根据老师的建议   以后在对链表进行操作的时候多定义一些节点指针  這样逻辑不容易混乱  也不容易错
//   但是在链表的逆置还存在一些问题  
#include<iostream>
#include<assert.h>
using namespace std;

typedef int DataType;
typedef struct DListNode       
{
	DataType _data;
	DListNode* _next;                  //前驱指针                 
	DListNode* _prev;                  //后驱指针
	DListNode(DataType d)               //节点构造函数
		: _data(d)
		, _next(NULL)
		, _prev(NULL)
	{  
	}   
}Node;
class DList
{
private:
	Node* _head;
	Node* _tail;
public:
	DList()
		: _head(NULL)    
		, _tail(NULL)   
	{
	}
	DList(const DList& s)      //拷贝构造
		:_head(NULL)
		,_tail(NULL)
	{
		Node* cur = s._head;
		while (cur)
		{
			PushBack(cur->_data);
			cur = cur->_next;
		}
	}
	DList& operator=(const DList& s)           //拷贝构造        千万不要忘了返回值  我每次写都会网卡了返回值
	{
		if (_head == NULL)
		{
			Node* cur = s._head;
			while (cur)
			{
				PushBack(cur->_data);
				cur = cur->_next;
			}
		}
		else
		{
			Clear();
			_head = NULL;
			_tail = NULL;
			Node* cur = s._head;
			while (cur)
			{
				PushBack(cur->_data);
				cur = cur->_next;
			}
		}
		return *this;
	}
	void PushBack(DataType d)
	{
		if (_head == NULL)
		{
			_head = new Node(d);
			_tail=_head;
		}
		else
		{
			_tail->_next = new Node(d);
			_tail->_next->_prev = _tail;
			_tail = _tail->_next;
		}
	}

	void PopBack()
	{
		if (_head == NULL)
		{
			cout << "链表为空" << endl;
			return;
		}
		else if (_head->_next == NULL)
		{
			delete _head;
			_head = NULL;
			_tail = NULL;
		}
		else
		{
			Node* tmp = _tail;
			_tail->_prev->_next = NULL;    //尽量少用這中方法写  因为這样的话需要判断_tail->_prev为不为空 后面也需要判断是不是为空 
			_tail = _tail->_prev;                 //所以可以定义两个指针指向我们要操作的对象   然后用這两个指针进行操作  不会出错
			delete tmp; 
		}

	}
	void PushFront(DataType d)
	{
		if (_head == NULL)
		{
			_head = new Node(d);
			_tail = _head;
		}
		else
		{
			Node* str = new Node(d);      //這里我在操作的时候我定义了两个指针指向我要操做的两个对象 
			Node* ptr = _head;                //這样操作对象非常方便   不需要一个一个找 那样容易出错
			_head = str;
			str->_next = ptr;
			ptr->_prev = str;
		}
	
	}
	void PopFront()
	{
		if (_head == NULL)
		{
			cout << "链表为空" << endl;
			return;
		}
		else if (_head->_next == NULL)
		{
			delete _head;
			_head = NULL;
			_tail = NULL;
		}
		else
		{
			Node* str = _head;
			Node* ptr = _head->_next;     //要操作就用两个指针控制住  简单快捷不出错
			_head = ptr;
			ptr->_prev = NULL;
			delete str;
		}
	}
	void Insert(Node* pos, DataType d)      //在我们后面学的数据结构STL中 在pos位置插入都是指的在POS前插入
	{
		assert(pos);
		if (pos == _head)
		{
			PushFront(d);
		}
		else
		{
			Node* ptr = pos;
			Node* str = pos->_prev;
			Node* NewNode = new Node(d);
			str->_next = NewNode;
			NewNode->_next = ptr;
			NewNode->_prev = str;
			ptr->_prev = NewNode;
		}
	
	}

	void Reverse()                    //逆置链表
	{
		/*Node* cur = _head;               //刚开始写前驱指针和后驱指针交换的方法写错了  
		while (cur)                         //不打算用這种方法
		{
			Node* tmp = cur;
			swap(_head,_tail);
			cur = cur->_prev;
		}*/
		Node* n1 = _head;                       //這种方式完全是把内容倒过来放进去 
		Node* n2 = _tail;
		while (!(((n1==n2)||(n1->_next==n2))))
		{
			swap(n1->_data, n2->_data);             //swap函数是std库函数 
			n1 = n1->_next;
			n2 = n2->_prev;                    
		}
	}
	Node* Find(DataType d)
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
	void Print()
	{
		Node* cur = _head;
		while (cur)
		{
			cout << cur->_data << " ";
			cur = cur->_next;
		}
		cout << endl;
	}
	void Clear()
	{
		if (_head->_next == NULL)
		{
			delete _head;
			_head = NULL;
			_tail = NULL;
			cout << "析构" << endl;
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
			_head = NULL;
			_tail = NULL;
		}
	}
	void Erase(Node* pos)
	{
		assert(pos);
		if (_head == NULL)
		{
			cout << "链表为空" << endl;
		}
		else if (pos == _head)
		{
			PopFront();
		}
	    else if (pos == _tail)
		{
			PopBack();  
		}
		else
		{
			Node* ptr = pos->_next;
			Node* str = pos->_prev;
			ptr->_prev = str;
			str->_next = ptr;
		}
	}
	~DList()
	{
		if (_head)
		{
			Clear();
		}
	
	}


};
void test()
{
	DList d1;
	d1.PushBack(1);
	d1.PushBack(2);
	d1.PushBack(3);
	d1.PushBack(4);
	d1.PushBack(5);
	d1.Print();
	d1.PopBack();
	d1.Print();
	d1.PushFront(0);
	d1.Print();
	d1.PopFront();
	d1.Print();
	d1.Insert(d1.Find(4), 8);     //在4前面插入8
	d1.Print();
	d1.Reverse();
	d1.Print();
	d1.Erase(d1.Find(2));
	d1.Print();
	DList d2(d1);
	d2.Print();
	DList d3;
	d3 = d2;
	d3.Print();
}