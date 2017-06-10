#define _CRT_SECURE_NO_WARNINGS 1

//二叉树的非递归遍历训练
//借助栈
#include<iostream>
#include<queue>
#include<stack>
#include<assert.h>
using namespace std;

template <class T>
struct  BinaryTreeNode
{
	T  _data;
	BinaryTreeNode<T>* _left;
	BinaryTreeNode<T>* _right;
	BinaryTreeNode(const T& d)
		:_data(d)
		, _left(NULL)
		, _right(NULL)
	{
	}
};

template <class T>
class BinaryTree
{
	typedef BinaryTreeNode<T>  Node;
private:
	Node* _root;
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
	~BinaryTree()
	{
		_Destory(_root);
		cout << "析构" << endl;
	}

	void PrevOrderNR()                      //前序遍历
	{
		stack<Node*> s1;
		if (_root == NULL)
			return;
		Node* cur = _root;
		while (cur || !s1.empty())
		{
			while (cur)
			{
				s1.push(cur);
				cout << cur->_data << " ";
				cur = cur->_left;
			}

			Node* tmp = s1.top();                   //练习的时候就是這里出错，应该定义一个变量保存栈顶的值  每次循环都会变一次
			s1.pop();

			cur = tmp->_right;
		}
		cout << endl;
	}

	void InOrderNR()                      //中序遍历
	{
		stack<Node*> s1;
		if (_root == NULL)
			return;
		Node* cur = _root;
		while (cur || !s1.empty())
		{
			while (cur)
			{
				s1.push(cur);
				cur = cur->_left;
			}

			Node* tmp = s1.top(); 
			cout << tmp->_data << " ";
			s1.pop();

			cur = tmp->_right;                 //跳转至右边结点
		}
		cout << endl;
	}

	void PostOrder()                           //[*]  后序  
	{
		stack<Node*>  s1;
		Node* cur = _root;
		Node* prev = NULL;
		while (cur||!s1.empty())    
		{
			while (cur)
			{
				s1.push(cur);
				cur = cur->_left;
			}
			Node* tmp = s1.top();

			//针对栈顶的操作
			if (tmp->_right == NULL || tmp->_right == prev)
			{
				cout << tmp->_data << " ";
				prev = tmp;
				s1.pop();
			}
			else
				cur = tmp->_right;
		}
		cout << endl;
	}
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
	void _Destory(Node* root)
	{
		if (root == NULL)
			return;
		_Destory(root->_left);
		_Destory(root->_right);
		delete root;
		root = NULL;
	}

};
void test()
{
	int arr[] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	BinaryTree<int>  b1(arr, sizeof(arr) / sizeof(arr[0]), '#');
	b1.PrevOrderNR();
	b1.InOrderNR();
	b1.PostOrder();
}
int main()
{
	test();
	return 0;
}


