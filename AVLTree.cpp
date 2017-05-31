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
			_root = new Node(key, value);
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
			Node* avlnode = new Node(key, value);
			parent->_left = avlnode;
			avlnode->_parent = parent;
			cur = avlnode;
			(parent->_baf)--;
		}
		else if (key>parent->_key)             //链右
		{
			Node* avlnode = new Node(key, value);
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
			}

			//旋转调整
			else if (parent->_baf == 2 || parent->_baf == -2)
			{
				if (parent->_baf == 2)                     
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
					if (parent->_left->_baf == -1)
					{
						_RotateR(parent);
					}
					else
					{
						_RotateLR(parent);
					}
				}
				break;                                //当我把结点的平衡因子绝对值为2的结点调整完毕之后，还需要往上调整吗？实际上是不需要的，原因和我整体插入的过程有关系
			}
			cur = parent;
			parent = parent->_parent;
		}
	}
	bool Remove(const K& key)        //注意：AVL树的增删查的效率都是 O(lg(N))
	{
	}
	bool  Find(const K& key)
	{
		return _Find(_root, key);
	}
	void InOrder()
	{
		_Inorder(_root);
		cout << endl;
	}
	bool IsBalanceTree()     //判断树是否平衡
	{
		return _IsBalanceTree(_root);
	}
protected:
	void _RotateL(Node* & parent)   //左单旋    這了parent要使用&的原因？因为要对树的结构进行更改
	{
		Node* tmp = parent;
		Node* SubR = parent->_right;
		Node* subL = SubR->_left;
		Node* ppParent = parent->_parent;    //parent的父节点  先保存起来

		SubR->_left = parent;
		parent->_parent = SubR;
		parent->_right = NULL;

		if (subL)                           //左单旋的第二种情况
		{
			parent->_right = subL;
			subL->_parent = parent;
		}
		//左单旋的第三种考虑：在baf=2這个结点还有没有父节点了
		if (ppParent == NULL)       
		{
			_root = SubR;
			SubR->_parent = NULL;
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
		tmp->_baf = 0;
		SubR->_baf = 0;
		//在最后的时候我在想我调整完成之后如果它还有父结点，那么父节点的baf也一定会改变，需要向上调整吗？    [*]
	
	}
	void _RotateR(Node* &parent)    //右单旋
	{
		Node* tmp = parent;
		Node* SubL = parent->_left;
		Node* subR = SubL->_right;
		Node* ppParent = parent->_parent;

		SubL->_right = parent;
		parent->_parent = SubL;
		parent->_left = NULL;
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
			SubL->_parent = NULL;
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
		tmp->_baf = 0;
	}
	void _RotateLR(Node* &parent)       //左右双旋    思考为什么我们双旋的时候需要保存一些结点进行平衡因子的更改？
	{
		Node* Cur = parent;
		Node* CurL = parent->_left;
		Node* Curr = CurL->_right;

		_RotateL(parent->_left);
		_RotateR(parent);

		if (Curr->_baf == 1)
		{
			CurL->_baf = -1;
		}
		else if (Curr->_baf == -1)
		{
			Cur->_baf = 1;
		}
		else 
		    Cur = CurL = Curr = 0;

	}
	void _RotateRL(Node* &parent)      //右左双旋      先右旋后左旋
	{
		Node* Cur = parent;
		Node* CurR = parent->_right;
		Node* Curl = CurR->_left;

		_RotateR(parent->_right);
		_RotateL(parent);
        
		if (Curl->_baf == 1)
		{
			CurR->_baf = 1;
		}
		else if (Curl->_baf == -1)
		{
			Cur->_baf = -1;
		}
		else 
		   Cur = CurR = Curl = 0;

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
	int Depth(Node* root)          //求树的深度  [*]
	{
		if (root == NULL)
			return 0;
		if (root->_left == NULL&&root->_right == NULL)
			return 1;
		int leftDepth = Depth(root->_left);
		int rightDepth = Depth(root->_right);

		return leftDepth > rightDepth ? leftDepth + 1 : rightDepth + 1;
	}


	bool _IsBalanceTree(Node* root)     //判断树是否平衡   [*]  
		//這是一种O（n^2）算法，从上到下递归，然后从最底下向上判断是否平衡
	{
		if (root == NULL)
			return true;
		int left = Depth(root->_left);
		int right = Depth(root->_right);

		if (right - left != root->_baf)
		{
			cout << root->_key << ":结点平衡因子错误，结点平衡因子是：" << root->_baf << endl;
		}

		return abs(left - right) < 2 &&_IsBalanceTree(root->_left) && _IsBalanceTree(root->_right);
		
	}

	bool _Find(Node* root ,const K& key)
	{
		if (root == NULL)
			return false;
		if (key < root->_key)
		{
			_Find(root->_left,key);
		}
		else if (key>root->_key)
		{
			_Find(root->_right, key);
		}
		else
		{
			return true;
		}
	}
}; 


//-----------测试-------------
void test()
{


	/*int arr[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	AVLTree<int, int> A1;
	for (size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		A1.Insert(arr[i], 0);
	}
	A1.InOrder();
	A1.InOrder();
	A1.IsBalanceTree();
	cout << A1.IsBalanceTree() << endl;
	cout << A1.Find(2) << endl;*/

	
	//对于存在特殊情况，实际上我们再左旋或者右旋的平衡因子的处理并非完善，再双旋的情况下需要加以特殊情况的调整
	int arr[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	AVLTree<int, int> A1;
	for (size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		A1.Insert(arr[i],0);
	}

	A1.InOrder();
	A1.IsBalanceTree();
	cout << A1.IsBalanceTree()<<endl;
	cout<<A1.Find(2)<<endl;
	cout << A1.Find(9) << endl;
	A1.InOrder();

}
int main()
{
	test();
	return 0;
}