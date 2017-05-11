#define _CRT_SECURE_NO_WARNINGS 1
//二叉树的非递归遍历（前序 中序 后序）
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
		cout << "构造二叉树结点" << endl;
	}

};
template <class T>
class BinaryTree
{
	typedef BinaryTreeNode<T>  Node;
private:
	Node* _root;
protected:
	Node* _CreatrTree(T* a,size_t n, const T& invalid, size_t& index)
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

	void Destory(Node* root)
	{
		if (root == NULL)
			return;
		Destory(root->_left);
		Destory(root->_right);
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
	void PrevOrderNRe()           //前序
	{
		stack<Node* >  s1;
		Node* cur = _root;
		while (cur || !s1.empty())
		{
			while (cur)
			{
				s1.push(cur);
				cout << cur->_data << " ";
				cur = cur->_left;
			}
			
			Node* tmp = s1.top();
			s1.pop();
			

			cur = tmp->_right;       //這个可以看作是子问题的一个入口啦
		}
		cout << endl;
	}

	void InOrderNRe()               //中序
	{
		stack<Node* >  s1;
		Node* cur = _root;
		while (cur || !s1.empty())
		{
			while (cur)
			{
				s1.push(cur);
				cur = cur->_left;
			}

			Node* tmp = s1.top();   //保留top的值，将他输出
			s1.pop();
			cout << tmp->_data << " ";

			cur = tmp->_right;       //這个可以看作是子问题的一个入口啦
		}
		cout << endl;
	}

	void PostOrder()                    //后序            不太理解
	{
		stack<Node* >  s1;
		Node* cur = _root;
		Node* prev = NULL;
		while (cur || !s1.empty())
		{
			while (cur)
			{
				s1.push(cur);
				cur = cur->_left;
			}

			Node* front = s1.top();
			if (front->_right == NULL || front->_right == prev)
			{
				cout << front->_data << " ";
				prev = front;
				s1.pop();
			}
			else
				cur = front->_right;
		}
		cout << endl;
	}
	~BinaryTree()
	{
		Destory(_root);
		cout << "析构" << endl;
	}


};
void test()
{
	int arr[] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	BinaryTree<int>  b1(arr, sizeof(arr) / sizeof(arr[0]), '#');
	b1.PrevOrderNRe();
	b1.InOrderNRe();
	b1.PostOrder();
}
int main()
{
	test();
	return 0;
}

