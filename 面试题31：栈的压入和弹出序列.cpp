#define _CRT_SECURE_NO_WARNINGS 1
//入栈的顺序是12345，   合法的出栈顺序是45321   非法的出栈顺序是43512
#include<iostream>
#include<assert.h>
#include<stack>
using namespace std;
//這道题的难点在于如何判断不是一个弹出序列，就是在所有的数字都压栈了之后依然没有找到下一个弹出的数字，就不是一个正确的序列了
bool PushAndPop(const int* InArr,size_t size1,const int* OutArr,size_t size2)
{
	assert(InArr);
	assert(OutArr);
	stack<int> _s;
	int PushPtr = 0;
	int PopPtr = 0;
	if (size1 != size2)
		return false;
	while (PopPtr != size2)
	{
		if (_s.empty())          //入口发现栈是空的话，就先push一个元素
			_s.push(InArr[PushPtr++]);
		while (PushPtr != size1&&_s.top() != OutArr[PopPtr])
		{
			_s.push(InArr[PushPtr++]);
			if ((PushPtr == size1)&&(_s.top() != OutArr[PopPtr]))
			{
				return false;
			}
		}
		if (PushPtr == size1)                     //這里是出错的关键地方，這里没有加這个判断就导致最后出错
		{
			if (_s.top() != OutArr[PopPtr])
				return false;
		}
		_s.pop();
		PopPtr++;
	}
	if (PopPtr == size2&&_s.empty())
		return true;
	else
		return false;
}
int main()
{
	int arr1[] = { 1, 2, 3, 4, 5 };
	int arr2[] = { 4, 5, 3, 2, 1 };
	//int arr2[] = { 4, 3, 5, 1, 2 };
	cout << PushAndPop(arr1, sizeof(arr1) / sizeof(arr1[0]), arr2, sizeof(arr2) / sizeof(arr2[0]));
	return 0;
}