#define _CRT_SECURE_NO_WARNINGS 1
//   二叉树的线索化
#include<iostream>
#include<queue>
#include<stack>
#include<assert.h>
using namespace std;

enum  PointerTag
{
	THREAD,             //前驱后驱指针标志
	LINK                //指向子树结点指针标志
};



template <class T>
struct  BinaryTreeNodeTD
{
	T  _data;
	BinaryTreeNodeTD<T>* _left;
	BinaryTreeNodeTD<T>* _right;
	PointerTag _leftTag;
	PointerTag _rightTag;

	BinaryTreeNodeTD(const T& d)
		:_data(d)
		, _left(NULL)
		, _right(NULL)
		, _leftTag(LINK)
		, _rightTag(LINK)
	{
		cout << "构造二叉树结点" << endl;
	}

};

template<class T>
struct Iterator               //中序迭代器                                          [*]
{
	typedef BinaryTreeNodeTD<T> Node;
	Node* _node;
	Iterator(Node* node)
		:_node(node)
	{
		cout << "构造一个迭代器对象" << endl;
	}
	T& operator*()     //迭代器可以修改数据
	{
		return _node->_data;
	}
	T* operator->()
	{
		return &_node->_data;
	}
	Iterator<T> operator++()
	{
		if (_node->_rightTag = THREAD)
		{
			_node = _node->_right;
		}
		else
		{
			Node* left = _node->_right;
			while (left && left->_leftTag == LINK)
			{
				left = left->_left;
			}
			_node = left;
		}
		return *this;
	}
	bool operator !=(Iterator<T>& it1)
	{
		return  _node != it1._node;
	}

};
template <class T>
class BinaryTree
{
	typedef BinaryTreeNodeTD<T>  Node;
public:
	typedef Iterator<T> Iterator;
private:
	Node* _root;
protected:
	Node* _CreatrTree(T* a, size_t n, const T& invalid, size_t& index)
	{
		Node* root = NULL;
		if (index < n && a[index] != invalid)                   //子问题
		{
			root = new Node(a[index]);
			root->_left = _CreatrTree(a, n, invalid, ++index);
			root->_right = _CreatrTree(a, n, invalid, ++index);
		}
		return root;                                         //返回条件
	}

	void _PrevOrder(Node* cur)       //递归前序遍历
	{
		if (cur == NULL)
			return;                             //一定注意返回条件  如果不写返回条件会栈溢出
		cout << cur->_data << " ";
		if (cur->_leftTag == LINK)
		{
			_PrevOrder(cur->_left);
		}
		if (cur->_rightTag == LINK)
		{
			_PrevOrder(cur->_right);
		}
	}

	void _InOrderThreading(Node* cur,Node*& prev)          //中序线索化，按照遍历的结果  3 2 4 1 6 5  进行线索化  
	{                                               //這里是递归实现线索化，当时递归打印的时候 前中后的区别cout的位置，這里同样，线索化的代码放在哪里就是哪种线索化
		if (cur == NULL)
			return;
		_InOrderThreading(cur->_left,prev);
		if (cur->_left == NULL)             //  找到最左结点，链接前驱                
		{
			cur->_left = prev;             // prev在什么时候创建呢？？？  对于中序来说  第一个遍历的结点的前驱为NULL
			cur->_leftTag = THREAD;
		}
		if (prev && prev->_right == NULL)    //后驱的链接比较特殊，必须要cur已经在下一个结点的情况下，再创建上一个结点的前驱
		{
			prev->_right = cur;
			prev->_rightTag = THREAD;
		}                  //到這里，上一个节点的线索化完毕 ，可以将prev往下一个结点移动了
		prev = cur; 
		_InOrderThreading(cur->_right,prev);    //子问题
	}


	void _PrevOrderThreading(Node* cur, Node*& prev)     //前序线索化
	{
		if (cur == NULL)
			return;
		if (cur->_left == NULL)
		{
			cur->_left = prev;
			cur->_leftTag = THREAD;
		}
		if (prev && prev->_right == NULL)
		{
			prev->_right = cur;
			prev->_rightTag = THREAD;
		}

		prev = cur;
		if (cur->_leftTag == LINK)    //我的问题：为什么我线索化之后就不能再递归下去了？ 死循环
		{
		    _PrevOrderThreading(cur->_left, prev);    //光写一个這个如果不判断会发现会引起死循环  栈溢出
		}

		if (cur->_rightTag == LINK)               //为什么中序线索化的时候没有遇到死循环的问题？ 因为中序遍历没有构成圈,一直在往后走
		{
		    _PrevOrderThreading(cur->_right, prev);
		}

	}
	

	void Destory(Node* root)       //注意释放空间的形式
	{
		if (root == NULL)
			return;
		if (root->_leftTag == LINK)
		{
			Destory(root->_left);
		}
		
		if (root->_rightTag == LINK)
		{
			Destory(root->_right);
		}
		delete root;
		root = NULL;
	}

public:
	BinaryTree()
		:_root(NULL)
	{
		cout << "无参构造" << endl;
	}

	BinaryTree(T* a, size_t n, const T& invalid)
	{
		size_t index = 0;
		_root = _CreatrTree(a, n, invalid, index);
	}

	void PrevOrder()
	{
		_PrevOrder(_root);
	}

	void InOrderThreading()
	{
		Node* prev =NULL;             //用prev记录上一个走过的结点
		_InOrderThreading(_root,prev);
		if (prev)
			prev->_rightTag = THREAD;            //线索化完整
	}

	void PrevOrderThreading()
	{
		Node* prev = _root;
		_PrevOrderThreading(_root, prev);
	}



	void InOrderThd()      //非递归中序遍历
	{
		Node* cur = _root;
		while (cur)              //cur肯定不为空 已经是线索化之后的 空的结点指针都被利用了（注意：最后一个访问的结点的右为空）
		{
			while (cur->_leftTag == LINK)
			{
				cur = cur->_left;
			}
			cout << cur->_data << " ";

			while (cur->_rightTag == THREAD)        //這里就是借助线索化的后驱 直接跳回  所以不在依赖于栈返回父结点
			{
				cur = cur->_right;
				cout << cur->_data << " ";
			}

		    cur = cur->_right;
	   }
		cout << endl;
	}

	void PrevOrderThd()           //非递归前序遍历   记住：线索化之后除了最后一个结点的右节点指针，其他的结点指针都不为空 要么是指向子树要么是指向该遍历方式的下一个结点
	{                                                                    //那么LINK 和THREAD就可以用来标志分开为两种情况 ，是往下跳还按照结点走下去
		Node* cur = _root;
		while (cur)
		{
			while (cur->_leftTag == LINK)
			{
				cout << cur->_data << " ";
				cur = cur->_left;
			}
			cout << cur->_data << " ";
			while (cur->_rightTag == THREAD)
			{
				cur = cur->_right;
				cout << cur->_data << " ";
			}
				cur = cur->_right;             //子问题
		}
		cout << endl;
	
	}


	Iterator Begin()          //這个是错的  应该是最左结点 ，需要循环找到
	{
		Iterator itb(_root);
		return itb;
	}
	Iterator End()
	{
		Iterator enit(NULL);    //最后一个就是空
		return enit;
	}

	~BinaryTree()
	{
		Destory(_root);
		cout << "析构" << endl;
	}

};

//————————————用迭代器访问——————————————————————————————————————————————————
template<class T>
void PrintBinaryTree(BinaryTree<T>& b1)        //注意打印函数在类外写，带来的一些问题，iterator要公有，打印函数要传类的对象
{
	BinaryTree<T>::Iterator it = b1.Begin();
	while (it != b1.End())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

}
//————————————————————————————————————————————————————————————————
void test()
{
	int arr[] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	BinaryTree<int>  b1(arr, sizeof(arr) / sizeof(arr[0]), '#');
	//b1.InOrderThreading();
	//b1.InOrderThd();
	b1.PrevOrderThreading();
	b1.PrevOrderThd();
	b1.PrevOrder();
	PrintBinaryTree(b1);
}

int main()
{
	test();
	return 0;
}


int main()
{
	
	int a = 1;
	int b = 1;
	int c = 1;
	int i = 0;
	int n = 20;
	for (i = 2; i < n; i++)
	{
		c = a + b;
		a = b;
		b = c;
	}

	printf("%d\n", c);
	return 0;
}