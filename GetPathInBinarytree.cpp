#define _CRT_SECURE_NO_WARNINGS 1


//求二叉树中和为某一值的路径
#include<iostream>
#include<queue>
#include<stack>
#include<vector>
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
	void PrintList()
	{
		_PrintList(_root);
		cout << endl;
	}


	void FindPath(const size_t targe)
	{
		vector<T> _a;
		size_t sum = 0;
		_FindPath(_a, _root, targe, sum);
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
	void _PrintList(Node* root)
	{
		if (root == NULL)
			return;
		cout << root->_data << " ";
		_PrintList(root->_left);
		_PrintList(root->_right);
	}

	//打印存储路径的数组  问题： 为什么我们不实用栈呢？ 
	//实际上因题目要求我们需要打印出来路径，如果放栈的话不方便打印
	void PrintVector(vector<T> a)
	{
		for (size_t i = 0; i < a.size(); i++)
		{
			cout << a[i] << " ";
		}
		cout << endl;
	}
	//寻找并且打印路径
	void _FindPath(vector<T>& a, Node* root, const size_t targe, size_t sum)
	{
		//返回条件: 到叶子结点且当前数字的总和等于目标数
		if (root == NULL)
		{
			if (targe == sum)
				PrintVector(a);
			return;
		}
		//没到叶子结点
		a.push_back(root->_data);
		sum += root->_data;
		//递归左右
		_FindPath(a, root->_left, targe, sum);
		_FindPath(a, root->_right, targe, sum);
		a.pop_back();
	}
};
void test()
{
	int arr[] = { 10, 5, 4, '#', '#', 7, '#', '#', 12, '#', '#' };
	BinaryTree<int> t1(arr, sizeof(arr) / sizeof(arr[0]), '#');
	t1.PrintList();
	t1.FindPath(22);
}
int main()
{
	test();
	return 0;
}

