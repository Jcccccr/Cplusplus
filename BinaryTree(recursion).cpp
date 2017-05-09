#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<string>
#include<assert.h>
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
	Node* _CreateTree(T* a, size_t n,const T& invalid, size_t& index)  //這里的index由调用這个函数的那个函数里面给传进来；但是這里出现了问题，还是因为栈帧的原因，在往根节点回的时候，index的值也会返回，這里的解决办法是？  &
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
public:
	BinaryTree()            //无参构造函数
		: _root(NULL)
	{
	}
	BinaryTree(T* a, size_t n, const T& invalid)      //带参的构造函数      //注意：无参的递归是不能写在公有的成员函数里面的想想为什么？
	{
		size_t index = 0;
		_root = _CreateTree(a, n, invalid, index);
	}
	BinaryTree(const BinaryTree<T>& t)
	{}
	BinaryTree<T>& operator=(const BinaryTree<T>& t)
	{
		return *this;
	}
	void PrevOrder() //前序遍历
	{
	}
	void Inorder()   //中序遍历
	{
	}
	void  PostOrder()  //后序遍历
	{
	}
	void LevelOrder()   //层序遍历
	{
	}
	size_t Size()      //结点个数
	{
	}
	size_t LeafSize()   //叶子结点个数
	{
	}
	size_t GetKLevel(size_t k)   //K层结点
	{
	}
	size_t Depth()  //树的深度
	{
	}
	Node* Find(const T& d)  //查找
	{
	}




//  非递归
//1.前序
	//  cur指向当前需要访问的结点 ，分两路执行，使用stack，左路结点依次访问压栈，cur==NULL则左路为空  pop掉访问完毕的结点->  cur->right访问右结点  循环往复
	void PrevOrderN()
	{
		stack<Node*> s1;    
		Node* cur = _root;
		while (cur || !(s1.empty()))
		{
			while (cur)
			{
				cout << cur->_data << " ";
				s1.push(cur);
				cur = cur->_left;
			}
			Node* tmp = s1.top();
			s1.pop();
			cur = tmp->_right;
		}
            
	}

};

void test()
{
	int arr[] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	BinaryTree<int> t1(arr,sizeof(arr)/sizeof(arr[0]),'#');
	t1.PrevOrderN();
}
int main()
{
	test();
	return 0;
}