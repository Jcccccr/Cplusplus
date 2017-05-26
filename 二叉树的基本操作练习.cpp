#define _CRT_SECURE_NO_WARNINGS 1


//使用递归实现二叉树的构建  三种遍历方式和各种操作
#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<stack>
using namespace std;

template<class T>
struct BinaryTreeNode
{
	T _data;
	BinaryTreeNode<T>* _left;
	BinaryTreeNode<T>* _right;
	BinaryTreeNode(const T& d)
		:_data(d)
		, _left(NULL)
		, _right(NULL)
	{
	
	}
};
template<class T>
class BinaryTree
{
	typedef BinaryTreeNode<T>  Node;
private:
	Node* _root;
public:
	BinaryTree()                                    //无参构造
		:_root(NULL)
	{
	}
	BinaryTree(T*a, size_t n,const T& invalid)         //带参构造
	{
		size_t index = 0;
		_root = _BinaryTree(a, n, invalid, index);
	}
	void PrevOrder()                                 //前序遍历
	{
		_PrevOrder(_root);
		cout << endl;
	}
	void InOrder()                                  //中序遍历
	{
		_InOrder(_root);
		cout << endl;
	}
	void PostOrder()                                //后序遍历
	{
		_PostOrder(_root);
		cout << endl;
	}
	void LevelOrder()                               //层序遍历   借助队列   非递归
	{
		Node* cur = _root;
		if (_root == NULL)
			return;
		queue<Node*> q1;                            //注意這里模板T是什么  我一开始使用了T 
		q1.push(cur);
		while (!q1.empty() && cur)                   //cur！=NULL
		{
			q1.push(cur->_left);
			q1.push(cur->_right);
			cout << (q1.front())->_data << " ";
			q1.pop();
			cur = q1.front();
		}
		cout << endl;
	}
	size_t Size()                 //求结点个数
	{
		return _Size(_root);
	}
	size_t LeafSize()             //求叶子结点个数
	{
		return _LeafSize(_root);
	}
	size_t KLevelSize(const size_t& K)                //求K层的叶子结点数
	{
		return _KLevelSize(_root,K);
	}

	size_t Depth()                           //求树的深度
	{
		return _Depth(_root);
	}
protected:
	Node* _BinaryTree(T* a, size_t n, const T& invalid, size_t& index)                  //如果不用引用，在栈帧销毁返回的时候就会出现问题
	{
		Node* root = NULL;                      //根结点                将数组进行前序递归构建
		if (index < n&&a[index] != invalid)
		{
			root = new Node(a[index]);
			root->_left=_BinaryTree(a, n, invalid, ++index);
			root->_right=_BinaryTree(a, n, invalid, ++index);
		}
		return root;                      //返回条件
	}
	void _PrevOrder(Node* root)
	{
		if (root == NULL)
			return;
		cout << root->_data << " ";
		_PrevOrder(root->_left);
		_PrevOrder(root->_right);
	}
	void _InOrder(Node* root) 
	{
		if (root == NULL)
			return;
		_InOrder(root->_left);
		cout << root->_data << " ";
		_InOrder(root->_right);
	}
	void _PostOrder(Node* root)
	{
		if (root == NULL)
			return;
		_PostOrder(root->_left);
		_PostOrder(root->_right);
		cout << root->_data << " ";
	}
	size_t _Size(Node* root)
	{
		if (root == NULL)
			return 0;                  //返回条件
		else
			return _Size(root->_left) + _Size(root->_right) + 1;
	}
	size_t _LeafSize(Node* root)
	{
		if (root == NULL)              //注意這个条件  练习的时候写错了，這个是针对只有一边是空的时候
			return 0;
		if (root->_left == NULL&&root->_right == NULL)
			return 1;
		else
			return _LeafSize(root->_left) + _LeafSize(root->_right);
	}
	size_t _KLevelSize(Node* root,const size_t& K)    //  這个刚开始错了    [*]
	{
		if (root == NULL)
			return 0;
		if (K == 1)
			return 1;
		if (K > 1)
			return _KLevelSize(root->_left, K - 1) + _KLevelSize(root->_right, K - 1);    
		else
			perror("K is wrong!");
	}
	size_t _Depth(Node* root)                             //這个还是想不到，不会写
	{
		if (root == NULL)
			return 0;
		if (root->_left == NULL&&root->_right == NULL)
			return 1;
		size_t leftDepth = _Depth(root->_left);
		size_t rightDepth = _Depth(root->_right);
		return leftDepth > rightDepth?  leftDepth + 1: rightDepth+1;        //加1是加上根结点     
	}

};



void test()
{
	int arr[] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	BinaryTree<int> b1(arr, sizeof(arr) / sizeof(arr[0]), '#');
	b1.PrevOrder();
	b1.InOrder();
	b1.PostOrder();
	b1.LevelOrder();
	cout<<b1.Size()<<endl;
	cout << b1.LeafSize() << endl;
	cout << b1.KLevelSize(3) << endl;
	cout << b1.Depth() << endl;
}
int main()
{
	test();
	return 0;
}