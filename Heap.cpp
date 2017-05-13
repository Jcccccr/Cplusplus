#define _CRT_SECURE_NO_WARNINGS 1

//堆本质上是一种算法    （可以把他看成一个动词）
#include<iostream>
#include<string>
#include<vector>
#include<assert.h>
using namespace std;


template<class T>
class Heap
{
private:
	vector<T> _a;                 //堆的本质实际上是vector 
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
       
		//建大堆
		for (int i = (_a.size() - 2) / 2; i >= 0; i--)     //大堆  从底下往上进行向上调整算法
		{
			AdjustDown(i);
		}
	}
	 
	


	void AdjustDown(int  root)          //[*]  向下调整算法，参数是当前结点的下标，把這个结点看成跟结点，从這个结点从上到下由大到小
	{
		int parent = root;
		int child = parent * 2 + 1;     //进入比较循环的都是左结点
		while (child<_a.size())                  //如果child是最后一个元素  -> child=_a.size()-1     注意：size（）是个数不是下标
		{
			//先和兄弟比较大小 选出大的
			if (child != _a.size()-1 && _a[child + 1] > _a[child])
			{
				child++;
			}

			if (_a[parent] > _a[child])
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



};
void test()
{
	int a[] = { 10, 11, 13, 12, 16, 18, 15, 17, 14, 19 };
	Heap<int> h1(a, sizeof(a) / sizeof(a[0]));


}
int main()
{
	test();
	return 0;
}