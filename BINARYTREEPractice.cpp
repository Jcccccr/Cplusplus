#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<assert.h>
#include<stack>
#include<queue>
using namespace std;

template<class T>
struct BinaryTreeNode
{
	T _data;
	BinaryTreeNode<T>* _left;
	BinaryTreeNode<T>* _right;
	BinaryTreeNode(const T& data)
		:_data(data)
		, _left(NULL)
		, _right(NULL)
	{
	}
};
template<class T>
class BinaryTree
{
	typedef BinaryTreeNode<T> Node;
private:
	Node* _root;
public:
	BinaryTree()
		:_root(NULL)
	{
	}
	BinaryTree(int* arr, size_t size, int invalid)
	{
		int index = 0;
		_root = _CreateBinaryTree(arr, size, invalid, index);
	}
	void PrevOrder()
	{
		_PrevOrder(_root);
	}
	//非递归前序遍历
	void PrevOrderNR()
	{
		if (_root == NULL)
			return;
		stack<Node*> _s;
		Node* cur = _root;
		while (!_s.empty() || cur)
		{
			while (cur)
			{
				_s.push(cur);
				cout << cur->_data << " ";
				cur = cur->_left;
			}
			Node* tmp = _s.top();
			_s.pop();
			cur = tmp->_right;
		}
		cout << endl;
	}
	//非递归中序遍历
	void InOrderNR()
	{
		if (_root == NULL)
			return;
		stack<Node*> _s;
		Node* cur = _root;
		while (cur || !_s.empty())
		{
			while (cur)
			{
				_s.push(cur);
				cur = cur->_left;
			}
			Node* tmp = _s.top();
			_s.pop();
			cout << tmp->_data << " ";
			cur = tmp->_right;
		}
	}
	//非递归后序遍历
	void PostOrderNR()
	{
		if (root == NULL)
			return;
		stack<int> _s;
		Node* cur = _root;
		Node* prev = NULL;
		while (cur || !_s.empty())
		{
			_s.push(cur);
			cur = cur->_left;
		}
		Node* tmp = _s.top();
		if (cur->_right == NULL || cur->_right == prev)
		{
			cout << cur->_data << " ";
			prev = tmp;
			_s.pop();
		}
		cur = tmp->_right;        //子问题
	}
	//层序遍历
	void LevelOrder()
	{
		if (_root == NULL)
			return;
		queue<Node* > _q;
		Node* cur = _root;
		_q.push(cur);
		while (!_q.empty())     //這样的写法是不需要考虑cur不是空但是队列为空的情况的，所以只需要一个条件就可以
		{
			if (cur->_left)
				_q.push(cur->_left);
			if (cur->_right)
				_q.push(cur->_right);
			cout << _q.front()->_data << " ";
			_q.pop();
			if (!_q.empty())
				cur = _q.front();
		}
		cout << endl;
	}
	//求二叉树的高度
	size_t Length()
	{
		if (_root == NULL)
			return 0;
		return _length(_root);
	}
	//求叶子结点的个数
	size_t GetLevelNode()
	{
		if (_root == NULL)
			return 0;
		return _GetLevelNode(_root);
	}

	~BinaryTree()
	{

	}
protected:
	Node* _CreateBinaryTree(int* arr,size_t size,int invalid,int& index)
	{
		Node* root = NULL;                                  //注意先初始化为NULL;
		if (index < size&&arr[index] != invalid)
		{
			root = new Node(arr[index]);
			root->_left = _CreateBinaryTree(arr, size, invalid, ++index);        //前置++
			root->_right = _CreateBinaryTree(arr, size, invalid, ++index);
		}
		return root;
	}
	void _PrevOrder(Node* root)
	{
		if (root == NULL)
			return;
		cout << root->_data << " ";
		_PrevOrder(root->_left);
		_PrevOrder(root->_right);
	}
	//求二叉树的高度
	size_t _length(Node* root)
	{
		if (root == NULL)
			return 0;
		size_t LeftLength = _length(root->_left);
		size_t RightLength = _length(root->_right); 
		return LeftLength > RightLength ? LeftLength + 1 : RightLength + 1;
	}
	//求叶子结点的个数
	size_t _GetLevelNode(Node* root)
	{
		if (root == NULL)                                //经常会缺漏只有左子树但是没有右子树的情况，這样的情况不会增加计数，所以是返回0
			return 0;
		if (root->_left == NULL&&root->_right == NULL)         
			return 1;
		return _GetLevelNode(root->_left) + _GetLevelNode(root->_right);
	}
};

int main()
{
	int arr[] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	BinaryTree<int> B1(arr, sizeof(arr) / sizeof(arr[0]), '#');
	//B1.PrevOrder();
	//B1.PrevOrderNR();
	//B1.InOrderNR();
	//B1.LevelOrder();
	//cout << B1.Length() << endl; 
	cout << B1.GetLevelNode() << endl;
	return 0;
}
