#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<string>
#include<assert.h>

using namespace std;


//红黑树
//遵守的规则和实现原理
//增删查时间复杂度
//旋转的各种情况分析
#define RED  1
#define BLACK  0

//在這里面实现旋转的时候我并没有将叔叔结点为黑和叔叔结点不存在放在一起考虑，当不存在叔叔结点的时候我又另外写了旋转因为在第一次写完之后挂掉了，发现对于不存在叔叔结点的情况旋转是需要特殊考虑的，所以就重新写了旋转
template<class K,class V>
struct RBTreeNode
{
	K _key;
	V _value;
	int _colour;
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;
	RBTreeNode(const K& key)
		: _key(key)
		, _value(0)
		, _colour(RED)                        //默认为红色的原因
		, _left(NULL)
		, _right(NULL)
		, _parent(NULL)
	{
		cout << "构造RB结点" << endl;
	}
};

template<class K,class V>
class RBTree
{
	typedef RBTreeNode<K, V>  Node;
private:
	Node* _root;
public:
	RBTree()
		:_root(NULL)
	{
	}
	bool Insert(const K& key)
	{
		//确保根结点为BLACK
		//寻找位置插入结点
		//分情况旋转变色，回溯
		//-----------------------------------------------------------------------------
		if (_root == NULL)
		{
			_root = new Node(key);
			_root->_colour = BLACK;
			return true;
		}
		//插入结点
		Node* cur = _root;
		Node* parent = NULL;
		while (cur)             //搜索树的插入永远都是插入叶子结点，這是搜索树的特性
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
		cur = new Node(key);
		cur->_parent = parent;
		if (parent->_key > cur->_key)
		{
			parent->_left = cur;
		}
		else if (parent->_key < cur->_key)
		{
			parent->_right = cur;
		}
		//插入完毕开始调整
		Node* Gparent = parent->_parent;
		if (parent->_colour == BLACK)
		{
			return true;
		}
		while (parent->_colour == RED&&Gparent)      //如果上层结点是黑色或者跟结点的话，就不需要向上调整了，实际上這个循环是为了那个不需要旋转的情况考虑的
		{
			if (parent->_key < Gparent->_key)     //p在左 u在右
			{
				Node* Uparent = Gparent->_right;   //找到叔叔结点
				if (Uparent&&Uparent->_colour == RED)  //叔叔存在且为红
				{
					parent->_colour = BLACK;
					Uparent->_colour = BLACK;
					Gparent->_colour = RED;
					cur = Gparent;
					Gparent = Gparent->_parent;             //向上调整
				}
				else if (Uparent&&Uparent->_colour == BLACK)  //叔叔存在且为黑 要旋转+考虑cur和parent的相对位置
				{
					if (cur->_key < parent->_key)     //cur在parent的左边  则右单旋+变色
						SubR(Gparent);
					else if (cur->_key>parent->_key)  //cur在parent的右边，左右双旋+变色
						SubLR(Gparent);
					return true;               //此次调整完毕后直接return，不需要循环
				}
				else                               //叔叔不存在   和上面一样
				{
					if (cur->_key < parent->_key)
						NusubR(Gparent);
					else if (cur->_key>parent->_key)
						NusubLR(Gparent);
					return true;
				}
			}
			else if (parent->_key > Gparent->_key)   //p在右边，u在左边
			{
				Node* Uparent = Gparent->_left;
				if (Uparent&&Uparent->_colour == RED)  //叔叔存在且为红
				{
					parent->_colour = BLACK;
					Uparent->_colour = BLACK;
					Gparent->_colour = RED;
					cur = Gparent;
					Gparent = Gparent->_parent;             //向上调整
				}
				else if (Uparent&&Uparent->_colour == BLACK)  //叔叔存在且为黑 
				{
					if (cur->_key > parent->_key)
						SubL(Gparent);                         //左单旋        
					else if (cur->_key<parent->_key)
						SubRL(Gparent);                         //右左双旋
					return true;
				}
				else                               //叔叔不存在   和上面一样
				{
					if (cur->_key > parent->_key)
						NusubL(Gparent);
					else if (cur->_key < parent->_key)
						NusubRL(Gparent);
					return true;
				}
			}
		}
		_root->_colour = BLACK;
		return true;
	}
	bool Remove(const K& key)  //删除
	{
	}
	bool Find(const K& key)     //查找
	{
		return _Find(_root, key);
	}
	bool IsRBTree()   //[*]        刚开始我在想這里为什么我不像AVL树一样实现一下判断平衡，但是实际上不需要，只需要判断这个树是否满足规则，如果满足规则
    {                           //如果满足规则，自然就能保证树的平衡（最长路径不超过最短路径的两倍）
         //需要满足的要求： 1. 根结点为黑
		 //                 2. 不能出现连续的红色结点
		 //                 3. 对每个节点，从该节点到其所有后代叶节点的简单路径上，均包含相同数目的黑色节点
		if (root == NULL)
			return false;
		if (_root&&_root->_colour == RED)  //根结点为红色，直接pass
			return false;
		return _IsRBTree(_root);           //用递归判断下面的两个条件是否成立
	}
	void InOrderR()
	{
		_InOrderR(_root);
		cout << endl;
	}
protected:
	void _InOrderR(Node* root)
	{
		if (root == NULL)
			return;
		_InOrderR(root->_left);
		cout << root->_key <<" ";
		_InOrderR(root->_right);
	}
	
	bool _IsRBTree(Node* root)   //递归判断平衡
	{
		if (root == NULL)
			return true;
		if ((root->_colour == RED) && (root->_parent->_colour == RED))
			return false;
		return _IsRBTree(root->_left) && _IsRBTree(root->_right);

		//判断黑色结点数目


	}
	void SubR(Node* Gparent)    //右单旋   
	{
		Node* Rparent = Gparent->_parent;         //Gparent 的父结点
		Node* parent = Gparent->_left;
		Node* cur = parent->_right;
		//链接的时候注意三叉链
		if (Rparent)                 //如果Gparent不是根结点
		{
			if (Rparent->_left == Gparent)
			{
				parent->_parent = Rparent;
				Rparent->_left = parent;
			}
			else if (Rparent->_right == Gparent)
			{
				parent->_parent = Rparent;
				Rparent->_right = parent;
			}
		}
		else if (Rparent == NULL)           //如果Gparent就是根结点，就需要进行根结点的交接  這个情况特别容易忽略
		{
			_root = parent;
		}

		Gparent->_left = cur;
		cur->_parent = Gparent;

		parent->_right = Gparent;
		Gparent->_parent = parent;

		//变色
		parent->_colour = BLACK;
		Gparent->_colour = RED;
	}
	void NusubR(Node* Gparent)          //for no nucle subR
	{
		Node* Rparent = Gparent->_parent;
		Node* parent = Gparent->_left;

		if (Rparent)
		{
			if (Rparent->_left == Gparent)
			{
				Rparent->_left = parent;
				parent->_parent = Rparent;
			}
			else if (Rparent->_right == Gparent)
			{
				Rparent->_right = parent;
				parent->_parent = Rparent;
			}
		}
		else
		{
			_root = parent;
		}
		parent->_right = Gparent;
		Gparent->_parent = parent;
		Gparent->_left = NULL;      //[*]

		//变色
		parent->_colour = BLACK;
		Gparent->_colour = RED;
	}

	void SubL(Node* Gparent)               //左单旋
	{
		Node* Rparent = Gparent->_parent;
		Node* parent = Gparent->_right;
		Node* cur = parent->_left;

		if (Rparent)                   //Gparent非根结点
		{
			if (Rparent->_left == Gparent)
			{
				parent->_parent = Rparent;
				Rparent->_left = parent;
			}
			else if (Rparent->_right == Gparent)
			{
				parent->_parent = Rparent;
				Rparent->_right = parent;
			}
		}
		else                           //Gparent为根结点
		{
			_root = parent;
		}

		Gparent->_right = cur;
		cur->_parent = Gparent;

		parent->_left = Gparent;
		Gparent->_parent = parent;
		//变色
		Gparent->_colour = RED;
		parent->_colour = BLACK;
	}
	void NusubL(Node* Gparent)                        //for no uncle subL 
	{
		Node* Rparent = Gparent->_parent;
		Node* parent = Gparent->_right;

		if (Rparent)
		{
			if (Rparent->_left == Gparent)
			{
				Rparent->_left = parent;
				parent->_parent = Rparent;
			}
			else if (Rparent->_right == Gparent)
			{
				Rparent->_right = parent;
				parent->_parent = Rparent;
			}
		}
		else
		{
			_root = parent;
		}
		parent->_left = Gparent;
		Gparent->_parent = parent;
		Gparent->_right = NULL;
		//变色
		parent->_colour = BLACK;
		Gparent->_colour = RED;
	}
	void SubLR(Node* Gparent)        //小左旋+右旋
	{
		Node* Pparent = Gparent->_left;
		Node* parent = Pparent->_right;
		Node* curL = parent->_left;
		//小左旋
		Pparent->_right = curL;     //（這种情况下curL是必定存在的，而且为黑）
		curL->_parent = Pparent;

		parent->_left = Pparent;
		Pparent->_parent = parent;

		Gparent->_left = parent;
		parent->_parent = Gparent;

		//右旋
		SubR(Gparent);
	}
	void NusubLR(Node* Gparent)
	{
		Node* parent = Gparent->_left;
		Node* cur = parent->_right;

		Gparent->_left = cur;
		cur->_parent = Gparent;
		cur->_left = parent;
		parent->_parent = cur;
		parent->_right = NULL;
		//右旋
		NusubR(Gparent);

	}
	void SubRL(Node* Gparent)        //小右旋+左旋
	{
		Node* Pparent = Gparent->_right;
		Node* parent = Pparent->_left;
		Node* curR = parent->_right;

		//小右旋
		Pparent->_left = curR;
		curR->_parent = Pparent;

		parent->_right = Pparent;
		Pparent->_parent = parent;

		Gparent->_right = parent;
		parent->_parent = Gparent;

		//左旋
		SubL(Gparent);
	}
	void NusubRL(Node* Gparent)
	{
		Node* parent = Gparent->_right;
		Node* cur = parent->_left;

		Gparent->_right = cur;
		cur->_parent = Gparent;
		cur->_right = parent;
		parent->_parent = cur;
		parent->_left = NULL;
		//左旋
		NusubL(Gparent);
	}

	//旋转小结：每一种旋转对应的是一种情况，刚开始在担心我旋转完了之后我的p g u三个的位置都变了，我需要把位置带回去吗，后来发现我的旋转只负责旋转就行了因为、
	//因为需要旋转的情况都是调整完了就直接返回的不再向上调整的（向上调整需要位置信息）（就像AVL中需要旋转的都是平衡因子绝对指为2的，而這样的结点调整完毕就是旋转完毕了之后
	//就直接结束所有调整），所以说我既然旋转，就只管旋转好了，更改好了位置就结束，还有一点：旋转是需要更改颜色的，更改颜色在旋转函数内部和旋转一并完成。

	bool _Find(Node* root,const K& key)
	{
		if (root == NULL)
			return false;
		if (root->_key > key)
		{
			_Find(root->_left, key);
		}
		else if (root->_key < key)
		{
			_Find(root->_right, key);
		}
		else
			return true;
	}
};
