#define _CRT_SECURE_NO_WARNINGS 1


#include<iostream>
#include<string>
#include<assert.h>     //关于assert断言的使用和perror的使用
using namespace std;


template <class T>
struct ListNode
{
	T _data;
	ListNode<T>* _prev;
	ListNode<T>* _next;
	ListNode(const T& d)                         //這里的问题： 为什么d是const修饰的变量 能够给非const修饰的 _data赋值？猜测：這里的d是一个常量
		:_data(d)                           
		, _prev(NULL)
		, _next(NULL)
	{
		cout << "构造结点" << endl;
	}

};

template<class T, class Ref, class Ptr>
struct ListIterator
{
	typedef ListNode<T> Node;
	Node* _node;
	ListIterator(Node* node)      //這里不能用const修饰形参 因为 node给迭代器迭代器需要遍历要往后走，所以肯定要改变啊
		:_node(node)
	{
	}
	Ref operator*()
	{
		return _node->_data;
	}
	Ptr operator->()
	{
		return &(_node->_data);
	}
	bool operator==(ListIterator<T, Ref, Ptr>&li)
	{
		return this->_node == li._node;
	}
	bool operator!=(ListIterator<T, Ref, Ptr>& li)
	{
		return this->_node != li._node;
	}
	ListIterator<T, Ref, Ptr>& operator++()        //++it
	{
		_node = _node->_next;
		return *this;                            //关于this指针
	}
	ListIterator<T, Ref, Ptr> operator++(int)      //it++
	{
		ListIterator<T, Ref, Ptr> tmp = (*this);
		_node = _node->_next;
		return tmp;
	}

};

template<class T>
class List
{

	typedef ListNode<T> Node;         //内嵌类型
public:
	typedef ListIterator<T,T&,T*> Iterator;
	typedef ListIterator<T, const T&, const T*> ConstIterator;
private:
	Node* _head;
public:
	List()
		:_head(new Node(T()))         //构造头结点
	{
		_head->_next = _head;
		_head->_prev = _head;
	}

	List(const List<T>& l)
		:_head(new Node(T()))
	{
		_head->_next = _head;
		_head->_prev = _head;              //粗心把這个忘掉了

		ConstIterator it = l.Begin();
		while (it!=l.End())
		{
			this->PushBack(*it);
			it++;
		}
	}
	void PushBack(const T& d)
	{
		Node* Prev = _head->_prev;
		Node* Newnode = new Node(d);

		Prev->_next = Newnode;
		Newnode->_next = _head;
		Newnode->_prev = Prev;
		_head->_prev = Newnode;
	}
	void PopBack()
	{
		assert(_head->_next != _head);

		Node* Back = _head->_prev;
		Node* Prev = Back->_prev;

		Prev->_next = _head;
		_head->_prev = Prev;

		delete Back;
	}
	void PushFront(const T& d)
	{
		Node* Next = _head->_next;
		Node* NewNode = new Node(d);

		_head->_next = NewNode;
		NewNode->_next = Next;
		Next->_prev = NewNode;
		NewNode->_prev = _head;
	}
	void PopFront()
	{
		assert(_head->_next != _head);

		Node* Front = _head->_next;
		Node* Next = Front->_next;

		_head->_next = Next;
		Next->_prev = _head;

		delete Front;
	}

	Iterator Begin()
	{
		Iterator itbegin(_head->_next);
		return itbegin;
	}

	ConstIterator Begin() const
	{
		ConstIterator itbegin(_head->_next);
		return itbegin;
	}

	Iterator End()
	{
		Iterator itend(_head);
		return itend;
	}

	ConstIterator End() const                 //这里在练习的时候出错了  记得返回值类型是ConstIterator  前面已经改了
	{
		ConstIterator itend(_head);
		return itend;
	}

	Iterator Find(const T& d)
	{
		assert(_head->_next != _head);
		Iterator it = Begin();
		while (it!=End())
		{
			if (*it == d)
				return it;
			it++;
		}
		if (it == End())
			return NULL;               //?
	}

	//在pos之前进行插入
	void Insert(Iterator pos,const T& d)
	{
		assert(pos._node);
		Node* Next = pos._node;
		Node* Prev = pos._node->_prev;
		Node* NewNode = new Node(d);

		Prev->_next = NewNode;
		NewNode->_prev = Prev;
		NewNode->_next = Next;
		Next->_prev = NewNode;
	}
	//删除
	void Erase(Iterator &pos)                    //使用引用配合解决迭代器失效
	{
		assert(pos._node);                       //這里几次出错，assert里面不能放一个对象 不能写成assert(pos) 
		assert(pos._node != _head);

		Node* NowNode = pos._node;
		Node* Prev = NowNode->_prev;
		Node* Next = NowNode->_next;

		Prev->_next = Next;
		Next->_prev = Prev;

		pos._node = NowNode->_prev;              //迭代器失效解决方案
		delete NowNode;
	}
    
	void Destory()
	{
		Iterator it = Begin();
		while (it!=End())
		{
			Node* tmp = it._node;
			it++;
			delete tmp;
		}
	}
	~List()
	{
		cout << "析构" << endl;
		Destory();
		delete _head;
		_head = NULL;
	}
    

};
template<class T>
void PrintList(List<T>& li)
{
	List<T>::Iterator it = li.Begin();
	while (it!=li.End())
	{
		cout << *it << " ";
		it++;
	}
	cout << endl;
}

template<class T>
void constPrintList(const List<T>& li)
{
	List<T>::ConstIterator it = li.Begin();
	while (it != li.End())
	{
		cout << *it << " ";
		it++;
	}
	cout << endl;
}

//---------------测试---------------
void TestList()
{
	List<int>  l1;
	l1.PushBack(1);
	l1.PushBack(2);
	l1.PushBack(3);
	l1.PushBack(4);
	l1.PushBack(5);
	l1.PushBack(6);
	l1.PopBack();
	l1.PopBack();
	l1.PopBack();
	l1.PushFront(9);
	/*List<int>  l2;
	l2.PushFront(1);*/
	l1.PopFront();
	PrintList(l1);
	ListIterator<int,int&,int*> pos = l1.Find(2);
	l1.Insert(pos, 9);
	l1.Erase(pos);
	PrintList(l1);
	constPrintList(l1);

	List<int> l3(l1);
	PrintList(l3);

	//----------------迭代器失效用例------------------------
	//利用迭代器打印所有偶数
	List<int>  l2;
	l2.PushBack(1);
	l2.PushBack(2);
	l2.PushBack(3);
	l2.PushBack(4);
	l2.PushBack(5);
	l2.PushBack(7);
	l2.PushBack(8);
	l2.PushBack(9);
	List<int>::Iterator it = l2.Begin();
	while (it != l2.End())
	{
		if (*it % 2 == 0)
			l2.Erase(it);             //删除结点              
		it++;
	}
	PrintList(l2);
	

}
int main()
{
	TestList();
	return 0;
}