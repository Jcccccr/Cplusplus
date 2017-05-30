#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
#include<assert.h>
using namespace std;
//非递归实现的AVL树 

template<class K, class V>
struct AVLTreeNode
{
	K _key;
	V _value;
	int _baf;                         //平衡因子
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;
	AVLTreeNode(const K& key, const V& value)
		:_key(key)
		,_value(value)
		,_baf(0)
		,_left(NULL)
		,_right(NULL)
		,_parent(NULL)
	{
		cout << "构造AVL结点" << endl;
	}
};

template<class K,class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
private:  
	Node* _root;
public:
	AVLTree()
		:_root(NULL)
	{
	}
	//插入
	bool Insert(const K& key, const V& value)
	{
        //查找位置进行插入
		//更新平衡因子进行调整
		//旋转调整之后，将parent进行重新连接
		if (_root == NULL)
		{
			_root = new Node(key,value);
			return true;
		}

		Node* cur = _root;
		Node* parent = NULL;
		while (cur)
		{
			if (key < cur->_key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (key>cur->_key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				return false;
			}
		}

		if (key < parent->_key)                //链左
		{
			Node* avlnode = new Node(key,value);
			parent->_left = avlnode;
			avlnode->_parent = parent;
			cur = avlnode;
			(parent->_baf)--;
		}
		else if (key>parent->_key)             //链右
		{
			Node* avlnode = new Node(key,value);
			parent->_right = avlnode;
			avlnode->_parent = parent;
			cur = avlnode;
			(parent->_baf)++;
		}
		//向上判断并且调整平衡因子
		while (parent)               //判断条件对吗？
		{
			//parent为当前父结点
			Node* pParent = parent->_parent;

			if (parent->_baf == 0)      //這里存在一点小小的问题
			{
				break;
			}
			else if (parent->_baf == 1 || parent->_baf == -1)   //向上调整
			{
				if (pParent == NULL)
				    break;
				if (pParent->_left == parent)
			    {
				    (pParent->_baf)--;
				}
				else if (pParent->_right == parent)
			    {
					(pParent->_baf)++;
				}
				if (pParent->_baf == 0)     //這里是不是也可以不写？
					break;
			}

			//旋转调整
			else if (parent->_baf == 2 || parent->_baf == -2)
			{
				if (parent->_baf == 2)                      //   *
				{
					if (parent->_right->_baf == 1)
					{
						_RotateL(parent);
					}
					else
					{
						_RotateRL(parent);
					}
				}
				else if (parent->_baf == -2)
				{
					if (parent->_left->_baf == 1)
					{
						_RotateR(parent);
					}
					else
					{
						_RotateLR(parent);
					}
				}
				break;
			}
			cur = parent;
			parent = parent->_parent;
		}
	}
	bool Remove(const K& key)
	{
	}
	Node* Find(const K& key)
	{
	}
	void InOrder()
	{
		_Inorder(_root);
	}
	bool IsBlanceTree()     //[*]
	{

	}
protected:
	void _RotateL(Node* & parent)   //左单旋    這了parent要使用&的原因？因为要对树的结构进行更改
	{
		Node* SubR = parent->_right;
		Node* subL = SubR->_left;
		Node* ppParent = parent->_parent;    //parent的父节点  先保存起来

		SubR->_left = parent;
		parent->_parent = SubR;

		if (subL)                   //左单旋的第二种情况
		{
			parent->_right = subL;
			subL->_parent = parent;
		}
		//左单旋的第三种考虑：在baf=2這个结点还有没有父节点了
		if (ppParent == NULL)       
		{
			_root = SubR;
		}
		else
		{
			if (ppParent->_left==parent)
			{
				ppParent->_left = SubR;
			}
			else if (ppParent->_right == parent)
			{
				ppParent->_right = SubR;
			}
			SubR->_parent = ppParent;
		}
		//调整平衡因子   //高度降低
		parent->_baf == 0;
		SubR->_baf == 0;
		//在最后的时候我在想我调整完成之后如果它还有父结点，那么父节点的baf也一定会改变，需要向上调整吗？    [*]
	
	}
	void _RotateR(Node* &parent)    //右单旋
	{
		Node* SubL = parent->_left;
		Node* subR = SubL->_right;
		Node* ppParent = parent->_parent;

		SubL->_right = parent;
		parent->_parent = SubL;
		//情况二
		if (subR)
		{
			parent->_left = subR;
			subR->_parent = parent;
		}
		//情况三
		if (ppParent == NULL)
		{
			_root = SubL;
		}
		else
		{
			if (ppParent->_left == parent)
				ppParent->_left = SubL;
			else
				ppParent->_right = SubL;
			SubL->_parent = ppParent;
		}
		//调整此根结点之下的所有结点的平衡因子
		SubL->_baf = 0;
		parent->_baf = 0;
	}
	void _RotateLR(Node* &parent)       //左右双旋   
	{
		_RotateL(parent->_left);
		_RotateR(parent);


	}
	void _RotateRL(Node* &parent)      //右左双旋      先右旋后左旋
	{
		_RotateR(parent->_right);
		_RotateL(parent);
	}
	//中序
	void _Inorder(Node* root)
	{
		if (root == NULL)
			return;
		_Inorder(root->_left);
		cout << root->_key << " ";
		_Inorder(root->_right);
	}
}; 


//-----------测试-------------
void test()
{
	int arr[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	AVLTree<int, int> A1;
	for (size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		A1.Insert(arr[i],0);
	}

}
int main()
{
	test();
	return 0;
}