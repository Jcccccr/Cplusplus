#define _CRT_SECURE_NO_WARNINGS 1

//堆本质上是一种算法    （可以把他看成一个动词）
#include<iostream>
#include<string>
#include<vector>
#include<assert.h>
using namespace std;



template<class T>
struct LessThan                                  //使用仿函数  实现大堆小堆的创建复用同一段代码  写一个比较类
{
	T left;
	T right;
	bool operator()(const T& left, const T& right)             
	{
		return left < right;
	}
};

template<class T>
struct MoreThan
{
	T left;
	T right;                                        //這里的成员变量不写也没什么  类里面也可以只有成员函数完成一定的操作，不一定要有成员变量
	bool operator()(const T& left, const T& right)
	{
		return left > right;
	}
};


template<class T,class Compare=MoreThan<T>>
class Heap
{
private:
	vector<T> _a;                 //堆的本质实际上是对vector的操作
public:
	Heap()     //无参构造函数 实例化对象vector自己调用缺省的构造函数
	{
	}
	Heap( T* a, size_t n)    //构造函数，把数组的值一一给vector
	{
		_a.reserve(n);
		for (size_t i = 0; i < n; i++)
		{
			_a.push_back(a[i]);
		}
       
		//    建堆     //不论是建大堆还是建小堆， 都是使用向下调整算法  只是向下调的比较不一样而已
		for (int i = (_a.size() - 2) / 2; i >= 0; i--)     //大堆  从底下往上循环进行向下调整算法
		{
			AdjustDown(i);  //向下调整算法  
		}
		
	}
	 
	void AdjustDown(int  root)          //[*]  向下调整算法，参数是当前结点的下标，把這个结点看成跟结点，从這个结点开始从上到下由大到小
	{
		Compare con;
		int parent = root;
		int child = parent * 2 + 1;     //进入比较循环的都是左结点
		while (child<_a.size())                  //如果child是最后一个元素  -> child=_a.size()-1     注意：size（）是  个数不是下标
		{
			//先和兄弟比较大小 选出大的
			if (child != _a.size() - 1 && con(_a[child + 1] , _a[child]))
			{
				child++;
			}

			if (con(_a[child] , _a[parent]))
			{
				swap(_a[parent], _a[child]);
				parent = child;
				child = child * 2 + 1;
			}
			else
			{
				break;
			}

		}

	}

	void AdjustUp(int root)   //向上调整，针对于尾部插入一个数据，调整为大堆 (针对于尾部插入)
	{
		int child = root;
		int parent = (child - 1) / 2;                //不论是左子树还是右子树，（子树-1）/2就是等于跟结点 我一开始以为（左子树-1）/2的值和左子树/2是一样的 都是父结点，以为对于右子树也是一样，但是发现如果（右子树/2）答案不是跟结点
		while (parent >= 0)
		{
			if (_a[child] > _a[parent])
			{
				swap(_a[child], _a[parent]);
				child = parent;
				parent = (parent - 1) / 2;
			}
			else
				break;
		}
	}


	void Push(const T& d)
	{
		_a.push_back(d);
		AdjustUp(_a.size()-1);              //把最后一个结点进行向上调整
	    
	}
	
	void Pop()         //删除最顶上结点
	{
		swap(_a[_a.size() - 1], _a[0]);
		_a.pop_back();
		AdjustDown(0);
	}

	bool IsHeap()                 //判断是否是大堆
	{
		for (size_t i = 0; i <= (_a.size() - 2) / 2; i++)
		{
			if (_a[i] < _a[i * 2 + 1] || _a[i] < _a[i * 2 + 2])
			{
				return false;
			}
		}
		return true;
	
	}

	


	void PrintHeap()
	{
		for (size_t i = 0; i < _a.size(); i++)                 //问题：vector自己也有自己的迭代器
		{
			cout << _a[i] << " ";
		}
		cout << endl;
		
	}

};


void test()
{
	int a[] = { 10, 11, 13, 12, 16, 18, 15, 17, 14, 19 };
	Heap<int> h1(a, sizeof(a) / sizeof(a[0]));          //不给比较类的模板参数就会自动生成缺省的模板参数
	h1.PrintHeap();
	Heap<int, LessThan<int>>h2(a, sizeof(a) / sizeof(a[0]));
	h2.PrintHeap();
	/*h1.Push(20);
	h1.PrintHeap();
	h1.Pop();
	h1.PrintHeap();*/


}
int main()
{
	test();
	return 0;
}