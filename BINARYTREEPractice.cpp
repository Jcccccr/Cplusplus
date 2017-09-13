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
	//求第K层的结点的个数
	size_t GetKLevelNode(int k)
	{
		if (_root == NULL)
			return 0;
		return _GetKLevelNode(_root, k);
	}
	//判断一个结点是否在一个二叉树中
	bool NodeInTree(Node* node)
	{
		if (_root == NULL || node == NULL)
			return false;
		return _NodeInTree(_root,node);
	}
	//判断一棵树是否是平衡二叉树
	bool IsBalance()
	{
		if (_root == NULL)
			return false;
		int LeftDep = _length(_root->_left);           //使用的方案就是利用求树的高度，求左右子树的高度然后求高度差。
		int rightDep = _length(_root->_right);
		if (LeftDep - rightDep < 2)
			return true;
		else
			return false;
	}
	//二叉树的镜像
	void Mirror()
	{
		if (_root == NULL)
			return;
		_Mirror(_root);
	}
	//递归拷贝一棵树
	Node* CopyTree()
	{
		if (_root == NULL)
			return NULL;
		_Copy(_root);
	}

	//判断一棵树是否是完全二叉树  :使用层序遍历
	bool IsFullTree()
	{
		if (_root == NULL)
			return false;
		bool IsFullTree = true;
		queue<Node*> _q;
		Node* cur = _root;
		_q.push(cur);
		while (!_q.empty())
		{
			if (cur->_left)
				_q.push(cur->_left);
			else                         //左为空，右必定为空
			{
				if (cur->_right)
					IsFullTree = false;
			}
			if (cur->_right)
				_q.push(cur->_right);
			else                         // 右为空，不可有下一层
			{
				while (!_q.empty())       //右为空就将下面一层的结点全部排查一遍，如果都是叶子结点就说明是完全二叉树。
				{
					_q.pop();
					if (!_q.empty())
					{
						Node* tmp = _q.front();
						if (tmp->_left || tmp->_right)
						{
							IsFullTree = false;
							return IsFullTree;
						}
					}
				}
				IsFullTree = true;
				return IsFullTree;
			}
			_q.pop();
			if (!_q.empty())                
				cur = _q.front();        
		}
		return IsFullTree;
	}

	~BinaryTree()              //如果是写的递归的话，注意别再这里面delete一次了  递归函数中已经delete了
	{
		_Delete(_root);
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
	//求第K层结点的个数
	size_t _GetKLevelNode(Node* root,int k)
	{
		if (root == NULL)          //不管是不是第K层结点，只要是遇到了NULL，计数就是0
			return 0;
		if (k == 1)
			return 1;
		return _GetKLevelNode(root->_left, k - 1) + _GetKLevelNode(root->_right, k - 1);
	}
	//求一个结点是否在一棵二叉树中
	bool _NodeInTree(Node* root,Node* node)
	{
		if (root == NULL)
			return false;
		if (root == node)
			return true;
		bool tmp = _NodeInTree(root->_left, node);   //在寻找到之后就会返回的情况就需要在一边递归之后返回
		if (tmp)
			return true;
		return _Node(root->_right, node);
	}
	//二叉树的镜像
	void _Mirror(Node* root)
	{
		if (root == NULL)
			return;
		_Mirror(root->_left);
		_Mirror(root->_right);
		swap(root->_left, root->_right);           //后序翻转
	}
	//递归销毁一棵二叉树
	void _Delete(Node* root)
	{
		if (root == NULL)
			return;
		_Delete(root->_left);
		_Delete(root->_right);
		delete root;
		root = NULL;
	}
	//递归拷贝一棵树
	Node* _Copy(Node* root)
	{
		if (root == NULL)
			return NULL;
		Node* newNode = new Node(root->_data);
		newNode->_left = _Copy(root->_left);
		newNode->_left = _Copy(root->_right);
		return newNode;
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
	//cout << B1.GetLevelNode() << endl;
	//cout << B1.GetKLevelNode(3) << endl;
	//cout << B1.IsBalance() << endl;
	//B1.Mirror();
	//B1.LevelOrder();
	cout<<B1.IsFullTree();
	return 0;
}
