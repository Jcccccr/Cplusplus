#define _CRT_SECURE_NO_WARNINGS 1

   // 二叉树的线索化以及遍历（非递归）练习
#include<iostream>
#include<assert.h>
#include<string>
using namespace std;


enum PointerType
{
	THREAD,
	LINK
};

template<class T>
struct BinaryTreeNode
{
	T _data;
	BinaryTreeNode<T>* _left;
	BinaryTreeNode<T>* _right;
	PointerType  _leftype;
	PointerType  _rightype;

	BinaryTreeNode(const T& d)
		: _data(d)
		, _left(NULL)
		, _right(NULL)
		, _leftype(LINK)
		, _rightype(LINK)
	{
		cout << "构造二叉树结点"<<endl;
	}
};

template<class T>
class BinaryTree
{
	typedef BinaryTreeNode<T> Node;
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

	void _BinaryTreeThreading(Node* cur, Node*& prev)   //中序线索化  (递归)        //练习的时候忘记了加上引用  &  导致错误  !!!
	{
		if (cur == NULL)
			return;
		_BinaryTreeThreading(cur->_left, prev);
		if (cur->_left == NULL)
		{
			cur->_left = prev;             //一直到最左边的结点，  prev才开始起作用  之前一直都是NULL
			cur->_leftype = THREAD;
		}
		if (prev && prev->_right == NULL)
		{
			prev->_right = cur;
			prev->_rightype = THREAD;
		}
		prev = cur;
		_BinaryTreeThreading(cur->_right, prev);     //子问题
	}

	void _PrevThreading(Node* cur, Node* & prev)   //前序线索化
	{
		if (cur == NULL)
			return;
		if (cur->_left == NULL)
		{
			cur->_left = prev;
			cur->_leftype = THREAD;      //记住要标记
		}
		if (prev && prev->_right == NULL)
		{
			prev->_right = cur;
			prev->_rightype = THREAD;
		}
		prev = cur;

		if (cur->_leftype == LINK)               //线索化的目的就是找闲置指针然后利用他  但是往下走的基础是根据子问题，为了避免无穷递归，這里需要判断，避开被THREAD标记的结点
		{
			_PrevThreading(cur->_left, prev);
		}
		if (cur->_rightype == LINK)           
		{
			_PrevThreading(cur->_right, prev);
		}
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

	void BinaryTreeThreading()       //中序线索化                 （注意：不能既前序线索化又中序线索化）
	{
		Node* prev = NULL;
		_BinaryTreeThreading(_root,prev);
	}
	void BinaryTreeThd()            //中序非递归遍历
	{
		Node* cur = _root;               //对于非递归  1.我们需要有一个结点指针cur指向当前结点，用循环代替递归 
		while (cur)                   //当cur为空时  结束所有的遍历  对于所有的非递归 ，循环的开始就是访问结点的开始
		{
			while (cur->_leftype == LINK)
			{
				cur = cur->_left;
			}
			cout << cur->_data << " ";
			
			while (cur->_rightype == THREAD)    //为什么要用while呢  如果是连续的回跳  就会出错  这一句是让右指针一直跳到有有右子树的根结点处
			{
				cur = cur->_right;
				cout << cur->_data << " ";
			}
			//(if (cur->_right==LINK))
			cur = cur->_right;                         //   非递归也需要能看出来子问题
		}
	}

	void PrevThreading()    //前序线索化
	{
		Node* prev = _root;
		_PrevThreading(_root, prev);
	}

	void PrevThd()    //前序非递归遍历
	{
		Node* cur = _root;
		while (cur)
		{
			while (cur->_leftype == LINK)
			{
				cout << cur->_data << " ";
				cur = cur->_left;
			}
			cout << cur->_data << " ";
			while (cur->_rightype == THREAD)
			{
				cur = cur->_right;
				cout << cur->_data << " ";
			}
			cur = cur->_right;                   //要知道這一句的意义   子问题
		}
	
	}

};



void test()
{
	int arr[] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	BinaryTree<int>  b1(arr, sizeof(arr) / sizeof(arr[0]), '#');
	//b1.BinaryTreeThreading();
	//b1.BinaryTreeThd();
	b1.PrevThreading();
	b1.PrevThd();
}
int main()
{
	test();
	return 0;
}