#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<algorithm>
#include<vector>
#include<assert.h>
using namespace std;

//求N个数中的最小的K个数   注意：建大堆
vector<int> GetLeastNumbers_Solution(vector<int> input, int k)
{
	vector<int> tmpArr;
	if (k>0)
	{
		if (k == input.size())
			return input;
		if (k > input.size())
			return tmpArr;
		for (int i = 0; i<k; i++)
			tmpArr.push_back(input[i]);
		make_heap(tmpArr.begin(), tmpArr.end());
		for (size_t i = k; i < input.size(); i++)
		{
			if (input[i]<tmpArr.front())  //如果小于堆中最大的那个数
			{
				pop_heap(tmpArr.begin(), tmpArr.end());
				tmpArr.pop_back();
				tmpArr.push_back(input[i]);
				push_heap(tmpArr.begin(), tmpArr.end());
			}
		}
	}
	return tmpArr;
}
int main()
{
	////关于heap接口的使用练习
	//int arr[] = { 4, 5, 1, 6, 2, 7, 3, 8 };
	//vector<int> v(arr, arr + 8);
	//make_heap(v.begin(), v.end());          //底层就是建堆
	//////如果不先使用make_heap，那么低下的接口都是无法使用的，都会报错，任何会影响這个接口之后效果的，都是非法的输入
	////pop_heap(v.begin(), v.end());           //這个接口是把最大的那个数放到数组的最后了
	////pop_heap(v.begin(), v.end());           //第二次pop_heap( )就挂掉了，说明這个接口的前提必须是一个堆
	////v.pop_back();
	////v.push_back(10);                        //数组尾插10
	////push_heap(v.begin(), v.end());           //這个本质上是一个向上调整的过程，這个接口的前提可以不是堆
	////sort_heap(v.begin(), v.end());           //同样，這个接口的前提是必须要先使用make_heap建一个堆
	//vector<int>::iterator vit = v.begin();
	//while (vit != v.end())
	//{
	//	cout << *vit << " ";
	//	vit++;
	//}
	//cout << endl;
	//总结： 除了make_heap()，除了push_heap()接口，其他的接口必须是建立在是一个堆之上的。
	return 0;
}


