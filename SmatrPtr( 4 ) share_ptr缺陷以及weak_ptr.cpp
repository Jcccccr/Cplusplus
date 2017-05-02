#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<memory>
using namespace std;

//shared_ptr的循环引用问题和解决方式
struct ListNode
{
	int _data;
	weak_ptr<ListNode> _next;        //结点的类型就是ListNode 我這里的结点没有定义成模板类
	weak_ptr<ListNode> _prev;       
	ListNode(int d)
		:_data(d)
	{
		cout << "构造结点" << endl;
	}
	~ListNode()
	{
		cout << "析构结点" << endl;
	}
};


void test()
{
	shared_ptr<ListNode> n1(new ListNode(3));     //自动释放空间  调用listnode的析构函数
	shared_ptr<ListNode> n2(new ListNode(4));          //我创造出两个结点 ，结点里面包含两个指针可以指向对方的指针，n1和n2现在分别控制着两个结点
	//如果只运行上面两行代码 ，发现会析构两次 
	n1->_next = n2;
	n2->_prev = n1;                 //让两个结点互相链接  运行代码 发现代码不析构了

	//当我上面改成weak_ptr之后，就会成功调用两次析构 ，实际上弱指针就是在辅助shared_ptr进行针对這中场景下的问题的析构，除了作用于弱指针自动析构
}
int main()
{
	test();
	return 0;
}



//注意： 弱指针没有构造函数 它完全是依附于shared_ptr存在