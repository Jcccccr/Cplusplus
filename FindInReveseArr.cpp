#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<assert.h>
#include<string.h>
using namespace std;
//题目描述： 把一个数组中的前若干个元素移动到数组的末尾，就是数组的旋转
//输入一个递增数组的一个旋转，输出旋转数组中的最小数字
//例如： 数组{3,4,5,1,2}就是数组{1,2,3,4,5}的一个旋转，找出其中最小的数字  最小数字为1

//方案：使用二分查找的变形  定义两个指针，每次缩小查找范围的一半


//[***特殊情况***]如果说三数相等，那么没有办法判断并且缩小空间，這样的情况只能遍历
int SpecialStation(const int a[], int begin, int end)
{
	int tmp = a[begin];
	for (size_t i = begin + 1; i <= end; i++)
	{
		if (a[i] < tmp)
		{
			tmp = a[i];
		}
	}
	return tmp;
}
int FindInRevsArr(const int a[],size_t length)
{
	assert(a);
	assert(length);
	int PrevIndex = 0;
	int BackIndex = length - 1;
	//考虑没有旋转的情况
	if (a[0] < a[length - 1])
	{
		return a[0];
	} 
	while (a[PrevIndex] >= a[BackIndex])    //這里的循环的条件，意思就是保证两个指针在前后两个区间
	{
		if (BackIndex - PrevIndex == 1)
			break;
		int MidIndex = PrevIndex + ((BackIndex - PrevIndex) >> 1);  //求平均值（习惯考虑溢出）

		//一定要考虑到特殊情况:  如果三个数相等的时候，注意只有三个数相等才是特里，如果是两个数其中有一个数不一样都是可以在上面的条件里面执行的
		if (a[MidIndex] == a[PrevIndex] && a[MidIndex] == a[BackIndex])
			return SpecialStation(a, PrevIndex, BackIndex);
		//注意点： 先判断上面的都相等的情况，再判断不相等的情况，如果不是就会出现错。

		//每次看中间的元素是属于前面的递增部分还是后面的递增部分
		//如果是前面的，就让前指针后移缩小范围，反之让后指针前移缩小范围，每次缩小一半并且确保前后指针一个属于前面部分一个属于后面
		if (a[MidIndex] >= a[PrevIndex])
			PrevIndex = MidIndex;
		else if (a[MidIndex] <= a[BackIndex])      //這里我的条件是< 而不是<=  上面也是  然后在出现重复数字的时候就出现了错误
			BackIndex = MidIndex;
	}
	return a[BackIndex];
}
void test()
{
	int arr[] = { 1, 1, 1, 0, 1, 1, 1 };
	size_t size = sizeof(arr) / sizeof(arr[0]);
	cout << FindInRevsArr(arr, size) << endl;
}
int main()
{
	test();
	return 0;
}
