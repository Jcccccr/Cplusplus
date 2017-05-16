#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<string>
#include<assert.h>
using namespace std;

struct AA              //构造一个AA类型
{
	int a;
	int b;
};

template<class T>
struct NodeList
{
	T _data;
	NodeList<T>* _next;
	NodeList<T>* _prev;
	NodeList(const T& a)     //为什么這里不加const就是错的   记住常量具有常属性 权限放大是危险的
		:_data(a)          //[*]
		,_next(NULL)
		,_prev(NULL)
	{
		cout << "构造结点" << endl;
	}

};

//      迭代器
template<class T,class ref,class ptr>
struct ListIterator                      //迭代器的目的就是遍历链表 没有必要写析构函数（析构把链表也析构了） 也没有写赋值运算符和拷贝构造，暂时是这么理解的
{
	typedef NodeList<T> Node;
	Node* _node;
	ListIterator(Node* node)
		:_node(node)
	{
		cout << "创建一个迭代器" << endl;
	}
	ref operator*()
	{   
		return _node->_data;         //出了作用域這个变量依然存在 所以返回引用
	}
	ptr operator->()
	{
		return &_node->_data;
	}
	ListIterator<T,ref,ptr>& operator++()    //注意：這里是前置++
	{
		_node = _node->_next;
		return *this;
	}
	ListIterator<T, ref, ptr> operator++(int)      //后置++           问题：虽然知道這里加一个（int）是为了区分前置和后置 ，但是对象怎么知道该调用哪一个？
	{
		ListIterator<T, ref, ptr> tmp = (*this);
		_node = _node->_next;
		return tmp;                              //   注意不能返回临时变量的引用  
	}
	bool operator!=(const ListIterator<T,ref,ptr>& l1)
	{
		return this->_node != l1._node;
	}

};


// 主体
template<class T>
class List
{
	typedef NodeList<T> Node;
private:
	Node* _head;
public:
	typedef ListIterator<T, T&, T*> Iterator;
	typedef ListIterator<T,const T&,const T*> ConstIterator;        //关于这里面的const 我还是不太明白
public:
	List()
		:_head(new Node(T()))           //关于构造匿名对象
	{
		_head->_next = _head;
		_head->_prev = _head;
	}
	void PushBack(const T& d=T())
	{
		Node* tmp = new Node(d);
		Node* cur = _head->_prev;
		cur->_next = tmp;
		tmp->_next = _head;
		tmp->_prev = cur;
	   _head->_prev = tmp;
	}
	void PopBack()
	{
		/*if (_head->_next = _head)
		{
			cout << "没有有效节点" << endl;
			return;
		}
		else
		{
			Node* tail = _head->_prev;     //這样的PopBack有问题
			Node* tmp = tail->_prev;
			tmp->_next = _head;
			_head->_prev = tmp;
			delete tail;  
			tail = NULL;  
		}*/
		Node* tail = _head->_prev;
		Node* prev = tail->_prev;

		delete tail;

		prev->_next = _head;
		_head->_prev = prev; 
	}
	Iterator Find(const T& d)        //通过迭代器来查找
	{
		Iterator it = Begin();
		while (it != End())
		{
			if ((*it) == d)
				return it;
			it++;
		}
		return End();
	}

	//随机位置的插入和删除

	void Insert(Iterator pos, const T& d)     //注意：我这里的插入需要考虑是不是在头节点插入吗？  其实不需要，因为這是一个双向循环链表，并不需要考虑那么多
	{
		assert(pos._node)   //注意断言的使用
		{
		     
		}
	
	}
	ConstIterator Begin() const
	{
		ConstIterator Bit(_head->_next);                  //遍历是遍历有效节点   是从第二个开始的
		return Bit;
	}
	Iterator Begin()
	{
		Iterator Bit(_head->_next);                    
		return Bit;
	}
	ConstIterator End() const      //const修饰的成员函数，可以被const对象调用
	{
		ConstIterator Eit(_head);
		return Eit;
	}
	Iterator End()
	{
		Iterator Eit(_head);
		return Eit;
	}
	void Destory()      
	{
		Iterator it = Begin();
		while (it != End())
		{
			cout << "析构结点" << endl;
			Node* tmp = it._node;
			it++;
			delete tmp;
		}
		_head->_next = _head;
		_head->_prev = _head;
	}
	~List()
	{
		Destory();
		_head = NULL;
	}
};



//   打印   注意：迭代器的意义：1.能让很多容器都使用迭代器，使用同样的方式遍历和修改数据 2.能够在类外打印数据
template <class T>
void PrintList(List<T>& l1)
{
	List<T>::Iterator  it = l1.Begin();   //注意点：這里的l1是非const修饰的对象 非const对象可以调用 const成员函数   
	while (it != l1.End())
	{
		cout << *it << " ";
		it++;
	}
	cout << endl;
}

//template <class T>
//void PrintList(const List<T>& l1)
//{
//	List<T>::ConstIterator  it = l1.Begin();  //const修饰的对象只能调用const成员函数进行操作，所以上面我在没写const修饰的Begin()的时候编译是没法通过的
//	while (it != l1.End())                  //const修饰的对象实际上是不希望对他进行修改，但是实际上這里对象调用的两个接口不会对成员变量进行操作，操作的只有迭代器，所以为了达到我们使用std::list的迭代器那样的效果，
//	{                                      //我们必须重新写一个const迭代器，对迭代器管理的数据进行const约束才能最终达到目的，所以接下来又引出了为什么我自定义的迭代器的模板参数列表需要设置三个参数了（实际上是为了复用）
//		cout << *it << " ";
//		it++;
//	}
//	cout << endl;
//}





//--------------------------------------------------测试------------------------------------------------
void test()
{
	
	//int a = 10;
	//const char& b = a;   //临时变量具有常性，分清楚临时变量和局部变量的区别,分清楚传值的时候实际上那个临时变量只是传值 ，当我们要引用一个具有常属性的变量的时候需要注意是否加上const

	
	//const int& b = 1;      //具有常属性的量必须要赋值给具有常属性的量
	



	List<int> l1;
	int a = 1;
	l1.PushBack(a);
	l1.PushBack(2);
	l1.PushBack(3);
	l1.PushBack(4);
	PrintList(l1);
	List<AA> l2;
	l2.PushBack(AA());
	l2.PushBack(AA());
	l2.PushBack(AA());
	l2.PushBack(AA());
	//PrintList(l2);
	List<AA>::Iterator it = l2.Begin();               //這里的it是指向AA结构体的指针
	while (it != l2.End())
	{
		it->a = 1;
		cout << it->b << " ";                //当是自定义类型的时候对->重载可以让迭代器指针访问结点内的结构体数据。
		it++;
	}
	List<string> l3;
	l3.PushBack("aa");                   //如果不传参  调用缺省参数   string调用构造函数 初始的字符串为空  ""
	l3.PushBack("bb");
	l3.PushBack("cc");
	l3.PushBack("dd");
	l3.PushBack("ee");
	PrintList(l3);
	l3.PopBack();
	PrintList(l3);
	List<string>::Iterator pos = l3.Find("cc");
	List<string>::Iterator bit = l3.Begin();
	//cout << *pos << endl;
	//cout << pos - bit << endl;   //這样根本做不到指针相减得到元素个数  除非重载-号
	
}
int  main()
{
	test();
	return 0;
}