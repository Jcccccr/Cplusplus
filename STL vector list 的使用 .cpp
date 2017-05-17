#define _CRT_SECURE_NO_WARNINGS 1

//STL的使用是非常重要的 ，学习STL的第一阶段就是一定要熟练使用STL
#include<iostream>
#include<vector>
#include<string>
#include<list>
using namespace std;
//1. vector的基本使用

template<class T>
void Print(vector<T>& v)
{
	vector<T>::iterator itv = v.begin();
	while (itv != v.end())
	{
		cout << *itv << " ";
		itv++;
	}
	cout << endl;

}
int main()
{
	vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);
	v1.push_back(5);
	v1.push_back(6);
	v1.push_back(7);
	v1.push_back(8);
	vector<int>::iterator itv = v1.begin();
	while (itv!=v1.end())
	{
		cout << *itv << " ";
		itv++;
	}
	cout << endl;
	Print(v1);
	cout << v1.capacity() << endl;
	//v1.reserve(10);                       //注意reserve的使用
	//cout << v1.capacity() << endl;
	v1.resize(12);
	Print(v1);
	cout << v1.capacity() << endl;
	v1.resize(5);
	Print(v1);
	cout << v1.capacity() << endl;
	v1.resize(5, 4);                //[*] 这里给值没有反应,意思就是我只有扩大了元素的元素如果其中有没有给值的resize的第二个参数才起作用
	Print(v1);
	v1.resize(12, 6);
	Print(v1);
	v1.reserve(2);      //容量扩大了之后就没法往小了降，这语句是不起作用的。
}



//2.std::list
//类似于vector
//int main()
//{
//	list<int> l1;
//	l1.push_back(1);
//	l1.push_back(1);
//	l1.push_back(1);
//	PrintMyVector(l1);
//	return 0;
//}