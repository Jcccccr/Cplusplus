#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
#include<vector>
#include<assert.h>
using namespace std;
//二维数组的查找
//一个二维数组中，每一行都按照从左到右递增，每一列从上到下递增，实现一个函数输入一个二维数组和一个整数，
//判断数是否在数组里面

//方案一： 暴力解，整个二维数组遍历一遍： 时间复杂度：o（N*N） 空间复杂度：o（1）

//方案二：走一步判断一步 导航法  时间复杂度：o（N）  空间复杂度：o（1） 不采纳 实现复杂可能只是第一种的优化方案

//方案三：利用矩阵右上角的元素值 逐渐减少搜索范围   虽不是二分查找但是思想于二分查找一致 
bool SearchInDarry(int a[][4],int rows,int lines,int num)
{
	assert(a);
	assert(rows);
	assert(lines);
	int row = 0;                        //注意右上角，第一维的元素是从0上限是行数。
	while (row<rows && lines >= 0)
	{
		if (a[row][lines - 1] > num)
		{
			lines--;
			continue;                   //注意這里的continue  
		}
		if (a[row][lines - 1] < num)
			row++;
		else
			return true;
	}
	return false;
}

//-------------------test------------------------------
void test()
{
	int arr[][4] = { 
		{ 1, 2, 8, 9 }, 
	    { 2, 4, 9, 12 }, 
	    { 4, 7, 10, 13 }, 
	    { 6, 8, 11, 15 } };
	cout << SearchInDarry(arr, 4, 4, 1);
	cout << SearchInDarry(arr, 4, 4, 2);
	cout << SearchInDarry(arr, 4, 4, 9);
	cout << SearchInDarry(arr, 4, 4, 6);
	cout << SearchInDarry(arr, 4, 4, 13);
	cout << SearchInDarry(arr, 4, 4, 15);
	cout << SearchInDarry(arr, 4, 4, -1);
	cout << SearchInDarry(arr, 4, 4, -1);
	cout << SearchInDarry(arr, 4, 4, 3);
	cout << SearchInDarry(arr, 4, 4, 20);
	cout << SearchInDarry(arr, 4, 4, 14);
}
int main()
{
	test();
	return 0;
}