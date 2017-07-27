#define _CRT_SECURE_NO_WARNINGS 1

//判断子树的问题：  判断B树是否是A树的子树问题

//寻找很根节点相等的A中的结点,如果找到了就去递归判断是否是子树,如果当前的结点不相等或者当前的结点向下寻找并非是子树
//那么就需要让A中的结点继续往下递归然后继续找和root根节点相等的结点 然后继续递归判断
//实际上這里面使用了两层递归
//刚开始這里的递归没有写返回条件所以错了



//判断B是否是A的子树部分
bool _CheckKidTree(Node* Aroot, Node* Broot)s
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


void test()                                                   //———————— 测试 ——————————
{
	int arr[] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	int arr2[] = { 2, 6, '#', '#', 4, '#' };
	BinaryTree<int> t1(arr, sizeof(arr) / sizeof(arr[0]), '#');
	BinaryTree<int> t2(arr2, sizeof(arr2) / sizeof(arr2[0]), '#');
	t1.PrevOrder();
	t2.PrevOrder();
	cout << t1.FindKidTree(t2);
}
int main()
{
	test();
	return 0;
}