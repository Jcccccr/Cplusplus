#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<string>
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
	BinaryTreeNode(const T& d)
		:_data(d)
		,_left(NULL)
		, _right(NULL)
	{
		cout << "构造二叉树结点" << endl;
	}
};

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

	void _PrevOrder(Node* root)    //前序遍历
	{
		if (root == NULL)       //返回条件
			return;
		cout << root->_data << " ";
		_PrevOrder(root->_left);
		_PrevOrder(root->_right);
	}

	void _InOrder(Node* root)    //中序遍历
	{
		if (root == NULL)       //返回条件
			return;
		_InOrder(root->_left);             //要把递归看作到了递归的最底层来写代码,這样容易明白逻辑
		cout << root->_data << " ";
		_InOrder(root->_right);
	}

	void _PostOrder(Node* root)   //后序遍历
	{
		if (root == NULL)        //返回条件
			return;
		_PostOrder(root->_left);
		_PostOrder(root->_right);
		cout << root->_data << " ";
	}

	void _LevelOrder(Node* root)     // 层序遍历  使用非递归  使用queue的先进先出原则                                             [*]
	{
		queue<Node*> q;
		if (root)                       //根结点入队
			q.push(root);
		else
			return;
		while (!q.empty())               //队列不为空则循环
		{
			Node* cur = q.front();
			cout << cur->_data << " ";
			if (cur->_left)
				q.push(cur->_left);
			if (cur->_right)
				q.push(cur->_right);
			q.pop();                     //這里实际上是通过pop让树往下走的，完成了类似于递归的作用
		}
		cout << endl;
	}

	size_t _Size(Node* root)         //求结点个数
	{
		if (root == NULL)
			return 0;
		if (root->_left == NULL && root->_right == NULL)    //  在這个递归中的返回条件
			return 1;
		return _Size(root->_left) + _Size(root->_right) + 1;             //這里记得+1   因为有根结点
	
	}

	size_t _LeafSize(Node* root)     //求叶子结点个数
	{
		if (root == NULL)
			return 0;
		if (root->_left == NULL&&root->_right == NULL)
			return 1;
		return _LeafSize(root->_left) + _LeafSize(root->_right);
		
	
	}

	size_t _GetKLevel(Node* root, size_t k)    //求第K层结点个数
	{
		if (root == NULL)
			return 0;                         //注意這里的返回值是size_t，不能光写return，一定要返回一个值0在這个地方
		if (k == 1)
			return 1;
		if (k > 1)
			return _GetKLevel(root->_left, k - 1) + _GetKLevel(root->_right, k - 1);      //尾递归
		else
		{
			cout << "'k' is wrong" << " ";
			return 0;
		}
		  
	}
	//求叶子结点的个数练习: 递归
	size_t GetLevelNumP(Node* root)
	{
		if (root == NULL)         //注意這个条件，针对于只有左子树的或只有右子树的结点
			return 0;
		if (root->_left == NULL && root->_right == NULL)
			return 1;
		return GetLevelNum(root->_left) + GetLevelNum(root->_right);
	}
	//求K层的结点的个数:递归
	size_t GetKLevelNumP(Node* root,int K)
	{
		if (root == NULL)
			return 0;		
		if (K < 1)                   //這个考虑实际上应该有必要
			return 0;
		if (K == 1)
			return 1;

		return GetKLevelNumP(root->_left, K - 1) + GetKLevelNumP(root->_right, K - 1);
	}

	size_t _Depth(Node* root)          //求二叉树的深度
	{
		if (root == NULL)
			return 0;
		if (root->_left == NULL && root->_right == NULL)
			return 1;
		size_t leftdepth = _Depth(root->_left);        //想想为什么我要分两边进行比较
		size_t rightdepth = _Depth(root->_right);
		return leftdepth > rightdepth ? leftdepth + 1 : rightdepth + 1;     //不要忘记+1 根结点
	}

	Node* _Find(Node* root,const T& t) //查找                                                                                     [*]
	{
		/*if (root == NULL)
			return NULL;
		Node* tmp = _Find(root->_left, t);
		if (root->_data == t)
		{
			return root;
		}
		_Find(root->_right, t);*/
		if (root == NULL)
			return NULL;
		if (root->_data == t)
			return root;
		Node* tmp = _Find(root->_left, t);
		if (tmp)
			return tmp;
		return _Find(root->_right, t);         //子问题
	}

	Node* _Copy(Node* root)               //拷贝，实际上就类似于构造 就是方式上不一样而已   二叉树的拷贝函数                           [*]
	{
		if (root == NULL)
			return NULL;
		Node* copyroot = new Node(root->_data);
		copyroot->_left = _Copy(root->_left);
		copyroot->_right = _Copy(root->_right);  
		return copyroot;
	}

	void Destory(Node* root)
	{
		if (root == NULL)
			return;
		Destory(root->_left);
		Destory(root->_right);
		delete root;              //释放当前结点
		root = NULL;
	}
	//判断B是否是A的子树部分
	bool _CheckKidTree(Node* Aroot,Node* Broot)
	{
		if (Broot == NULL)
			return true;
		if (Aroot == NULL&&Broot)
			return false;
		if (Aroot->_data == Broot->_data)
			return _CheckKidTree(Aroot->_left, Broot->_left) && _CheckKidTree(Aroot->_right, Broot->_right);
		else
			return false;
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


	BinaryTree(const BinaryTree<T>& t)                         //拷贝构造
	{
		_root = _Copy(t._root);
	}
	BinaryTree<T>& operator=(const BinaryTree<T>& t)             //赋值运算符重载
	{
		if (_root)
			Destory(_root);
		_root = _Copy(t._root);
		return *this;
	}


	void PrevOrder()                                         //前序遍历
	{
		_PrevOrder(_root);
		cout << endl;
	}
	void InOrder()                                            //中序遍历
	{
		_InOrder(_root);
		cout << endl;
	}
	void  PostOrder()                                        //后序遍历
	{
		_PostOrder(_root);
		cout << endl;
	}
	void LevelOrder()                                         //层序遍历        (這个用不到递归，所以可以不用這样写)
	{
		_LevelOrder(_root);
	}
	size_t Size()                                            //结点个数
	{
		return _Size(_root);
	}
	size_t LeafSize()                                         //叶子结点个数
	{
		return _LeafSize(_root);
	}
	size_t GetKLevel(size_t k)                                 //K层结点
	{
		return _GetKLevel(_root, k);
	}
	size_t Depth()                                            //树的深度
	{
		return _Depth(_root);
	}
	Node* Find(const T& d)                                    //查找
	{
		return _Find(_root, d);
	}

	//寻找很根节点相等的A中的结点,如果找到了就去递归判断是否是子树,如果当前的结点不相等或者当前的结点向下寻找并非是子树
	//那么就需要让A中的结点继续往下递归然后继续找和root根节点相等的结点 然后继续递归判断
	//实际上這里面使用了两层递归
	//刚开始這里的递归没有写返回条件所以错了
	bool CheckKidTree(Node* root1, Node* root2)
	{
		if (root1 == NULL)
			return false;
		bool result = false;
		if (root1->_data == root2->_data)
			result = _CheckKidTree(root1, root2);
		if (!result)
			return CheckKidTree(root1->_left, root2);
		if (!result)
			return CheckKidTree(root1->_right, root2);
		return result;
	}
	bool FindKidTree(const BinaryTree<T>& t)
	{
		if (this->_root == NULL)
			return false;
		if (t._root == NULL)
			return false;
		return CheckKidTree(this->_root, t._root);
	}
	~BinaryTree()                                             //析构
	{
		Destory(_root);
		_root = NULL;
		cout << "析构" << endl;
	}

};



void test()                                                   //———————— 测试 ——————————
{
	int arr[] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	int arr2[] = { 2, 6, '#', '#', 4, '#' };
	BinaryTree<int> t1(arr, sizeof(arr) / sizeof(arr[0]), '#');
	BinaryTree<int> t2(arr2, sizeof(arr2) / sizeof(arr2[0]), '#');
	t1.PrevOrder(); 
	t2.PrevOrder();
	cout << t1.FindKidTree(t2);
	/*t1.InOrder();
	t1.PostOrder();
	t1.LevelOrder();
	cout << t1.Size() << endl;
	cout << t1.LeafSize() << endl;
	cout<<t1.GetKLevel(3)<<endl;
	cout << t1.Find(3) << endl;

	BinaryTree<int> t2(t1);
	t2.PrevOrder();
	t2.InOrder();
	t2.PostOrder();
	t2.LevelOrder();
	cout << t2.Size() << endl;
	cout << t2.LeafSize() << endl;
	cout << t2.GetKLevel(3) << endl;
	cout << t2.Find(3) << endl;

	BinaryTree<int> t3;
	t3 = t1;
	t3.PrevOrder();
	t3.InOrder();
	t3.PostOrder();
	t3.LevelOrder();*/
}
int main()
{
	test();
	return 0;
}