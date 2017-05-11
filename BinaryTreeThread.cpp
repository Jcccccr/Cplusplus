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
	BinaryTreeNodeTD(const T& d)
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
	typedef BinaryTreeNodeTD<T>  Node;
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
	void _InOrderThreading(Node* root,Node*& prev)          //中序线索化，按照遍历的结果  3 2 4 1 6 5  进行线索化  
	{                                               //這里是递归实现线索化，当时递归打印的时候 前中后的区别cout的位置，這里同样，线索化的代码放在哪里就是哪种线索化
		if (root == NULL)
			return;
		_InOrderThreading(root->_left,root);
		if (root->_left == NULL)                     
		{
			root->_left = prev;      //左树指针若为空就指向前驱，右孩子为空则指向后驱
		}
		_InOrderThreading(root->_right,root);    //左树前驱线索化完毕 ，跳转至右子树进行前驱的中序线索化
	}

	/*void Destory(Node* root)
	{
		if (root == NULL)
			return;
		Destory(root->_left);
		Destory(root->_right);
		delete root;
		root = NULL;
	}*/
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
	void InOrderThreading()
	{
		Node* prev = _root;             //用prev记录上一个走过的结点
		_InOrderThreading(_root,prev);
	}
	/*~BinaryTree()
	{
		Destory(_root);
		cout << "析构" << endl;
	}*/

};

void test()
{
	int arr[] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	BinaryTree<int>  b1(arr, sizeof(arr) / sizeof(arr[0]), '#');
	b1.InOrderThreading();
}

int main()
{
	test();
	return 0;
}