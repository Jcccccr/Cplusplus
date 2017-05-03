#define _CRT_SECURE_NO_WARNINGS 1

//STL的使用是非常重要的 ，学习STL的第一阶段就是一定要熟练使用STL
#include<iostream>
#include<vector>
#include<string>
#include<list>
using namespace std;
//1. vector的基本使用

//int main()
//{
//	vector<int> v1;
//	v1.push_back(1);
//	v1.push_back(2);
//	v1.push_back(3);
//	v1.push_back(4);
//	v1.push_back(5);
//	v1.push_back(6);
//	vector<int>::iterator it1 = v1.begin();    //刚开始我想不通过迭代器实现打印vector 后来发现根本没有东西来遍历啊，也就明白迭代器的作用是很重要的
//	while (it1 != v1.end())
//	{
//		cout << *it1 << " ";
//		it1++;
//	}
//	cout << endl;
//	//cout << *(v1.end()-1) << endl;
//	return 0;
//}

//将print函数写在函数外面 ，這样更加方便
//void PrintMyVector(const vector<int>& v)             //当我使用const修饰的时候 vector里面的迭代器也必须要使用const_iterator 不然没法使用
//{
//	vector<int>::const_iterator  it = v.begin();      //const的配套使用很重要
//	while (it != v.end())
//	{
//		cout << *it << " ";
//		it++;
//	}
//	cout << endl;
//}
//template <class T>
//void PrintMyVector(vector<T>& v)                 //对模板的理解和使用   把打印函数定义成模板函数 這样的话打印就更加方便了     
//{
//	vector<T>::iterator  it = v.begin();
//	while (it != v.end())
//	{
//		//*it = 1;             //迭代器的对象能够对vector的元素进行修改
//		cout << *it << " ";
//		it++;
//	}
//	cout << endl;
//}
//再简化一点
template <class T>
void PrintMyVector(T& v)                 
{
	T::iterator  it = v.begin();
	while (it != v.end())
	{
		//*it = 1;            
		cout << *it << " ";
		it++;
	}
	cout << endl;
}
//int main()
//{
//	vector<int> v1;
//	v1.push_back(1);
//	v1.push_back(2);
//	v1.push_back(3);
//	v1.push_back(4);
//	v1.push_back(5);
//	PrintMyVector(v1);
//	vector<string> v2;
//	v2.push_back("hh");
//	v2.push_back("jj");
//	v2.push_back("kk");
//	PrintMyVector(v2);
//	/*vector<int> v2;
//	v2.push_back(4);
//	v2.push_back(5);
//	v2.push_back(6);
//	v2.push_back(7);
//	PrintMyVector(v2);*/
//	return 0;
//}



//2.std::list
//类似于vector
int main()
{
	list<int> l1;
	l1.push_back(1);
	l1.push_back(1);
	l1.push_back(1);
	PrintMyVector(l1);
	return 0;
}