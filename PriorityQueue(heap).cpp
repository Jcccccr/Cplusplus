#define _CRT_SECURE_NO_WARNINGS 1

#include"heap.h"

//优先级队列   在STL中是是用适配器模式的堆  
//模板的分离编译概念模糊  ，编译链接概念不深入    模板类模板函数不支持分离编译，定义和声明只能在一个文件hpp内 
//但是這下面的不是用适配器模式实现的堆（队列），只是样子像  ，适配器模式的模板参数列表里面有容器模板参数 而且成员变量是一个容器模板不是具体的容器
template<class T ,class Compare=MoreThan<T>>
class PriorityQueue
{
private:
	Heap<T, Compare> _h;
public:
	PriorityQueue()               //无参构造函数
	{
	}
	PriorityQueue(T* a,size_t n)             //带参构造函数
	{
		for (size_t i = 0; i < n; i++)
		{
			_h.Push(a[i]);
		}
	}
	void Push(const T& p)                   //入队
	{
		_h.Push(p);
	}
	void Pop()                             //出队
	{
		_h.Pop();
	}
	void Print()                                //队的打印
	{
		while (!(_h.Empty()))
		{
			cout << _h.Front()<<" ";
			Pop();
		}
		cout << endl;
	}
};




--------------------------------------------------测试————————————————————————
void test()
{
	int a[] = { 10, 11, 13, 12, 16, 18, 15, 17, 14, 19 };
	PriorityQueue<int,MoreThan<int>> pQ (a, sizeof(a) / sizeof(a[0]));
	//pQ.Print();
	pQ.Push(20);
	//pQ.Print();
	//pQ.Pop();
	pQ.Print();
}
int main()
{
	test();
	return 0;
}
