#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<string>
#include<vector>
#include<assert.h>

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
		cout << "构造二叉树结点" << endl;
	}
};


//递归建立一个二叉树
template<class T>
class BinaryTree
{
	typedef BinaryTreeNode<T> Node;
private:
	Node* _root;
protected:
	Node* _CreateTree(T* a, size_t n, const T& invalid, size_t& index)  //這里的index由调用這个函数的那个函数里面给传进来；但是這里出现了问题，还是因为栈帧的原因，在往根节点回的时候，index的值也会返回，這里的解决办法是？  &
	{
		//index = 0;  //注意：這里千万不能给下标一个初值，递归会出现问题
		Node* root = NULL;
		if (index < n && a[index] != invalid)
		{
			root = new Node(a[index]);
			root->_left = _CreateTree(a, n, invalid, ++index);    //出现的问题：  我一开始写的是index++，但是出现了无限循环，注意创建的新的栈帧就会产生新的index
			root->_right = _CreateTree(a, n, invalid, ++index);
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
	void _MirrorTree(Node* root)
	{
		if (root == NULL)
			return;
		swap(root->_left, root->_right);    //左子树和右子树交换
		_MirrorTree(root->_left);
		_MirrorTree(root->_right);
	}
	//二叉树的查找：不是那么好写  时间复杂度：o（N*N）
	bool _FindParent(Node* root, Node* _node)
	{
		if (root == NULL)
			return false;
		if (root->_data == _node->_data)
			return true;
		bool tmp = _FindParent(root->_left, _node);
		if (tmp == true)
			return true;
		_FindParent(root->_right, _node);
	}

public:
	BinaryTree()                                             //无参构造函数
		: _root(NULL)
	{
	}
	BinaryTree(T* a, size_t n, const T& invalid)                 //带参的构造函数      //注意：无参的递归是不能写在公有的成员函数里面的想想为什么？
	{
		size_t index = 0;                                     //注意這里为什么我们把index单独拿出来给初始化0
		_root = _CreateTree(a, n, invalid, index);
	}
	//中序遍历
	void PrevOrder()
	{
		_PrevOrder(_root);
		cout << endl;
	}
	//题目一： 二叉树的镜像
	void MirrorTree()
	{
		_MirrorTree(_root);
	}
	//找公共的祖先节点 
	//方案一：   使用两个数组
	//时间复杂度o（N*N）
	Node*  FindParent(Node* node1, Node* node2)
	{
		assert(node1);
		assert(node2);
		vector<Node*> _arr1;
		vector<Node*> _arr2;
		while (node1 != _root)
		{
			_arr1.push_back(node1);
			node1 = node1->parent;
		}
		_arr1.pop_back(_root);        //在我這里写的循环条件下需要最后将_root放入数组
		while (node2 != _root)
		{
			_arr2.push_back(node2);
			node2 = node2->parent;
		}
		_arr2.pop_back(_root);
		for (size_t i = 0; i < _arr1.size(); i++)
		{
			for (size_t j = 0; j < _arr2.size(); j++)
			{
				if (_arr1[j] = _arr2[i]);
				return _arr[j];
			}
		}
		cout << "查找错误" << endl;
		return NULL;
	}

	//方案二：
	//遍历  
	//时间复杂度：好像是o（N*N*N）
	Node* FindParent2(Node* _node1, Node* _node2)
	{
		assert(_node1);
		assert(_node2);
		while (_node1 != NULL)
		{
			bool tmp = _FindParent(_node1, _node2);
			if (tmp == true)
				return _node1;
			_node1 = _node1->parent;
		}
		return NULL;
	}
};
//如果二叉树是搜索二叉树
Node* _FindParent(Node* root, Node* node1, Node* node2)
{
	if (root == NULL)
		return;
	if ()
}
Node FindPublicParent(Node* node1, Node* node2)
{
	assert(node1);
	assert(node2);
	return _FindParent(_root, node1, node2);
}


int main()
{
	int arr[] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	BinaryTree<int> t1(arr, sizeof(arr) / sizeof(arr[0]), '#');
	t1.PrevOrder();
	t1.MirrorTree();
	t1.PrevOrder();
	return 0;
}
