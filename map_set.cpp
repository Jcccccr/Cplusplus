#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<string>
#include<assert.h>    //记住加上.h
#include<map>
#include<set>

using namespace std;


void test()
{
	map<string, int> m1;
	m1.insert(make_pair("haha", 3));
	m1.insert(make_pair("hehe", 3));
	m1.insert(pair<string,int>("xixi", 3));         //两种方式是一样的。  pair是一个类型 ，這里实际上
	m1.insert(make_pair("hiahia", 3));
	m1.insert(make_pair("huohuo", 3));
	map<string, int>::const_iterator it1 = m1.begin();                 //为啥std::map中的迭代器实现的是const的
	while (it1 != m1.end())
	{
		cout << it1->first << endl;
		it1++;   
	}
	//cout << endl;

}
int main()
{
	test();
	return 0;
}