#define _CRT_SECURE_NO_WARNINGS 1

#include"RBTree.h"

void test()
{
	RBTree<int, int> R1;
	R1.Insert(7);
	R1.Insert(2);
    R1.Insert(1);
	R1.Insert(4);
	R1.Insert(33);
	R1.Insert(27);
	R1.Insert(3);
	R1.Insert(6);
	R1.Insert(31);
	R1.Insert(0);
	R1.Insert(19);
	R1.Insert(20);
	R1.Insert(25);
	R1.Insert(21);
	R1.Insert(10);
	R1.Insert(13);
	R1.Insert(24);
	R1.Insert(20);
	R1.Insert(8);
	R1.Insert(20);
	R1.Insert(67);
	R1.Insert(5);
	R1.Insert(65);
	R1.Insert(90);
	R1.Insert(14);
	cout<<R1.Insert(2)<<endl;
	R1.InOrderR();                                //中序遍历出来的结果就相当于排了一个序。 对于搜索树来说中序遍历的结果就是从小到大
	cout<<R1.Find(3)<<endl;                       //实际上我比较有疑问的是为什么在搜索树和平衡树里面的查找的返回值是bool，這个和实际的应用有关系吗？
}
int main()
{
	test();
	return 0;
}
