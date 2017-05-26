#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
using namespace std;
//K结构的二叉搜索树       树形数据结构从這里开始涉及到增删查改的

template<class K>
struct SearchBinaryTreeNode
{
	K _data;
	SearchBinaryTreeNode<K>* _left;
	SearchBinaryTreeNode<K>* _right;
	SearchBinaryTreeNode(const K& d)
		:_data(d)
		, _left(NULL)
		, _right(NULL)
	{
	}

};
template<class K>
class SearchBinaryTree
{
	typedef SearchBinaryTreeNode<K> Node;
private:
	Node* _root;
public:
	SearchBinaryTree()
		:_root(NULL)
	{
	}

	//非递归
	//bool Insert(const K& d)             //注意：尾端插入（這不是随机位置插入）            //這里使用bool值也是由于這棵树的性质  防止数据冗余
	//{                                   //对于二叉搜索树来说有一个有点，可以通过结点的键值比较来判断是左结点还是右结点
	//	if (_root == NULL)
	//	{
	//		_root = new Node(d);
	//		return true;
	//	}
	//		Node* parent = NULL;
	//		Node* cur = _root;
	//		while (cur)
	//		{
	//			if (d < cur->_data)
	//			{
	//				parent = cur;
	//				cur = cur->_left;
	//			}
	//			else if (d > cur->_data)
	//			{
	//				parent = cur;
	//				cur = cur->_right;
	//			}
	//			else
	//			{
	//				return false;
	//			}
	//		}
	//		if (d > parent->_data)
	//		{
	//			parent->_right = new Node(d);
	//			return true;
	//		}
	//		else
	//		{
	//			parent->_left = new Node(d);
	//			return true;
	//		}
	//}
	//递归
	bool InsertR(const K& d)
	{
		return _InsertR(_root, d);
	}
	bool FindR(const K& d)
	{
	    return _FindR(_root, d);
	}
	
	bool RemovR(const K& d)                 //[*]
	{
		return _RemovR(_root, d);
	}
	//bool Find(const K& d)               //注意：对于K结构的二叉搜索树查找是不允许修改值的，如果修改了则整棵树都可能改变
	//{
	//	if (_root == NULL)
	//	{
	//		return false;
	//	}
	//	Node* cur = _root;
	//	while (cur)
	//	{
	//		if (d < cur->_data)
	//		{
	//			cur = cur->_left;
	//		}
	//		else if (d > cur->_data)
	//		{
	//			cur = cur->_right;
	//		}
	//		else
	//		{
	//			return true;
	//		}
	//	}
	//	return false;
	//}
	void Remove(const K& d)                 //注意：分情况
	{
		if (_root == NULL)
			return;
		if (Find(d) == 0)
		{
			cout << "未找到" << endl;
			return;
		}
		else
		{
			Node* parent = NULL;
			Node* cur = _root;
			while (cur)
			{
				if (d < cur->_data)
				{
					parent = cur;
					cur = cur->_left;
				}
				else if (d > cur->_data)
				{
					parent = cur;
					cur = cur->_right;
				}
				else     // 找到了键值为d的结点      开始进行移除
				{
					//1. 若为叶子结点
					if (cur->_left == NULL&&cur->_right == NULL)
					{
						if (parent == NULL)                          //這中情况：当删除到最后一个结点的时候
						{
							delete cur;
							cur = NULL;
							_root = NULL;   //记得根结点置空
							cout << "移除成功" << endl;
							return;
						}
						else if (cur->_data < parent->_data)          //左叶子结点
						{
							parent->_left = NULL;
							delete cur;
							cout << "移除成功" << endl;
							return;
						}
						else                                     //右叶子结点
						{
							parent->_right = NULL;
							delete cur;
							cout << "移除成功" << endl;
							return;
						}
					}
					//2. 若：结点左为空  [*]   注意根结点
					else if (cur->_left == NULL)
					{
						if (parent == NULL)                          //当树只剩下右半边的时候
						{
							_root = cur->_right;
							delete cur;
							cout << "移除成功" << endl;
							return;
						}
						if (cur->_data < parent->_data)
						{
							parent->_left = cur->_right;
							delete cur;
							cout << "移除成功" << endl;
							return;
						}
						else
						{
							parent->_right = cur->_right;
							delete cur;
							cout << "移除成功" << endl;
							return;
						}
					}

					// 若：结点右为空        注意根结点
					else if (cur->_right == NULL)
					{

						if (parent == NULL)                              //当树只剩左半边的时候
						{
							_root = cur->_left;
							delete cur;
							cout << "移除成功" << endl;
							return;
						}
						if (cur->_data < parent->_data)
						{
							parent->_left = cur->_left;
							delete cur;
							cout << "移除成功" << endl;
							return;
						}
						else
						{
							parent->_right = cur->_left;
							delete cur;
						}
					}

				    //3. 若结点左右都不为空  ：[*]替换法  （找以它为根结点的左子树的最右结点或者右子树的最左节点）
					else
					{
						Node* parent = NULL;
						Node* tmp = cur->_left;        //tmp为左子树根结点
						if (tmp->_right == NULL)
						{
							swap(tmp->_data, cur->_data);
							cur->_left = tmp->_left;
							delete tmp;
							cout << "移除成功" << endl;
							return;
						}
						else
						{
							while (tmp->_right)        //找左子树的最右结点
							{
								parent = tmp;
								tmp = tmp->_right;
							}
							if (tmp->_left == NULL)
							{
								swap(cur->_data, tmp->_data);
								parent->_right = NULL;
								delete tmp;
								cout << "移除成功" << endl;
								return;
							}
							else
							{
								parent->_right = tmp->_left;
								delete tmp;
								cout << "移除成功" << endl;
								return;
							}
						}
					}
				}
			}
		}
	}
	void InOrder()                           //发现二叉搜索树的中序遍历的键值从小到大
	{
		_inOrder(_root);
		cout << endl;
	}
protected:
	//递归插入
	bool _InsertR(Node*& root, const K& d)
	{
		if (root == NULL)
		{
			root = new Node(d);
			return true;
		}
		if (d < root->_data)
		{
			_InsertR(root->_left, d);
		}
		else if (d>root->_data)
		{
			_InsertR(root->_right, d);
		}
		else
		{
			return false;
		}
	}

	//递归查找
	bool _FindR(Node* root, const K& d)
	{
		if (root == NULL)
		{
			return false;
		}
		if (d < root->_data)
		{
			_FindR(root->_left, d);
		}
		else if (d>root->_data)
		{
			_FindR(root->_right, d);
		}
		else
		{
			return true;
		}
	}

	//递归删除
	bool _RemoveR(Node*& root, const K& d)
	{
		if (root == NULL)
		{
			return false;
		}
		if (d < root->_data)
		{
			_RemoveR(root->_left, d);
		}
		else if (d < root->_data)
		{
			_RemoveR(root->_right, d);
		}
		else                                //找到
		{
			if (root->_left == NULL)
			{
				Node* cur = root;
				root = root->_right;
				delete cur;
				cur = NULL;
				cout << "移除成功" << endl;
			}
			else if (root->_right == NULL)
			{
				Node* cur = root;
				root = root->_left;
				delete cur;
				cur = NULL;
				cout << "移除成功" << endl;
			}
			else       //左右子树都不为空
			{
				

				
			}
		}

	}

	void _inOrder(Node* root)
	{
		if (root == NULL)
			return;
		_inOrder(root->_left);
		cout << root->_data<<" ";
		_inOrder(root->_right);
	}
};

void test()
{
	SearchBinaryTree<int> s1;
	int arr[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	for (size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		s1.InsertR(arr[i]);
	}
	s1.InOrder();
	cout<<s1.FindR(3)<<endl;
	//s1.Remove(0);
	//s1.InOrder();
	//s1.Remove(1);
	//s1.InOrder();
	//s1.Remove(2);
	//s1.InOrder();
	//s1.Remove(3);
	//s1.InOrder();
	//s1.Remove(4);
	//s1.InOrder();
	//s1.Remove(5);              //程序从這里开始挂掉了     這个时候树只剩下一半 parent==NULL 
	//s1.InOrder();
	//s1.Remove(6);
	//s1.InOrder();
	//s1.Remove(7);
	//s1.InOrder();
	//s1.Remove(8);
	//s1.InOrder();
	//s1.Remove(9);             //当只剩下最后一个结点的时候 如果前面不改一下也会挂掉
	//s1.InOrder();


}
int main()
{
	test();
	return 0;
}