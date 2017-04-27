#define _CRT_SECURE_NO_WARNINGS 1

//问题：什么叫做配置器模式？
//   什么是容器？
// 栈和队列這两种数据结构的特点各是什么？


#include"List.h"

template<class T,class Container>     //Container在這里是容器
class Queue                         //队列 先进先出
{
private:
	Container _con;
public:
	void Push(const T& s);
	void Pop();
	size_t Size();
	void Print();
};

template<class T,class Container>
void Queue<T, List<T>>::Push(const T& s)
{
	_con.PushBack(s);
}

template<class T, class Container>
void Queue<T, List<T>>::Print()
{
	_con.Print();
}
void test()
{
	Queue<int,List<int>> q1;
	

}
int main()
{
	test();
	return 0;
}