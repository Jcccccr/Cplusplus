#define _CRT_SECURE_NO_WARNINGS 1

//问题：什么叫做配置器模式？
//   什么是容器？
// 栈和队列這两种数据结构的特点各是什么？


//#include"List.h"
////   队列
//template<class T,class Container>     //Container在這里是容器
//class Queue                         //队列 先进先出
//{
//private:
//	Container _con;
//public:
//	void Push(const T& s)
//	{
//		_con.PushBack(s);
//	}
//	void Pop()
//	{
//		_con.PopFront();
//	}
//	size_t Size()
//	{
//		return _con.Size();             //如果這个函数起的作用是一个值，一定要记住要返回值
//	}
//	const T& Top()
//	{
//		return _con.Front();             //  记住要返回值  刚开始我就写了一个 _con.Front();
//		
//	}
//	void Print()
//	{
//		//List<T>::Node* tmp = List<T>::_head;
//		while (_con.Empty() == 0)
//		{
//			cout<<Top()<<" ";
//			Pop();                             //這是一个要付出代价的查看
//		}
//		//List<T>::_head = tmp;
//		cout << endl;
//	}
//};
//
//
//void test()
//{
//	Queue<int,List<int>> q1;
//	q1.Push(1);
//	q1.Push(2);
//	q1.Push(3);
//	q1.Push(4);
//	//q1.Print();
//	//q1.Pop();                   //就在這里的时候出现了问题  当我之前在Print的时候  就把数据pop光了  也就是我要看整个队列有啥 是要付出代价的
//	//q1.Pop();
//	//q1.Pop();
//	//q1.Print();
//	cout<<q1.Size()<<endl;
//
//
//}
//int main()
//{
//	test();
//	return 0;
//}


//Stack  堆
#include"SeqList.h"
#include"List.h"
//template<class T,class Container=SeqList<int>>     //带默认参数的模板参数列表
//class Stack
//{
//private:
//	Container _con;
//public:
//	void Push(const T& d)      //压栈
//	{
//		_con.PushBack(d);
//	}
//	void Pop()                //出栈
//	{
//		_con.PopBack();
//	}
//	const T& Top()            //栈顶
//	{
//		return _con.Back();
//	}
//	void Print()              //打印
//	{
//		while (_con.Empty()==0)
//		{
//			cout << Top() << " ";
//			Pop();                       //由于栈只能对栈顶进行操作  所以這里打印是逆序打印
//		}
//	}
//
//};

//模板的模板参数：写法
template<class T, template<class>class Container>   //這里面有一个template<class>就是说在這个模板参数列表里有一个参数是模板 Container是一个容器模板，放在這里就是作为Stack的模板参数
class Stack
{
private:
	Container<T> _con;                         //与上面不同，這里要這样写
public:
	void Push(const T& d)      //压栈
	{
		_con.PushBack(d);
	}
	void Pop()                //出栈
	{
		_con.PopBack();
	}
	const T& Top()            //栈顶
	{
		return _con.Back();
	}
	void Print()              //打印
	{
		while (_con.Empty() == 0)
		{
			cout << Top() << " ";
			Pop();                       //由于栈只能对栈顶进行操作  所以這里打印是逆序打印
		}
	}

};
void test()
{
	Stack < int, List>s1;              //在這里就可以不写成List<int>這样了  這样就避免了在实例化的时候写出Stack<int , List<char>>這样的代码引起麻烦
	s1.Push(1);
	s1.Push(2);
	s1.Push(3);
	s1.Push(4);
	s1.Push(5);
	s1.Pop();
	/*s1.Print();*/      //這里依然存在问题  就是打印需要牺牲数据  后续的操作无法完成，想要保留数据该怎么做            
	cout << s1.Top() << endl;
}
int main()
{
	test();
	return 0;
}