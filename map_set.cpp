#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<string>
#include<assert.h>    //记住加上.h
#include<map>
#include<set>
#include<stack>

using namespace std;


void testmap()
{
	////map<string, int> m1;
	////m1.insert(make_pair("haha", 3));
	////m1.insert(make_pair("hehe", 4));
	////m1.insert(make_pair("xixi", 3));         //两种方式是一样的。  pair是一个类型 ，這里实际上
	////m1.insert(make_pair("hiahia", 3));
	////m1.insert(make_pair("huohuo", 3));
	////map<string, int>::iterator it1 = m1.begin();                 //为啥std::map中的迭代器实现的是const的
	////while (it1 != m1.end())
	////{
	////	cout << it1->first << endl;
	////	it1++;   
	////}
	//////cout << endl;

	////如何使用insert统计出现的各个水果出现的次数？
	////insert的插入：不容许键值的冗余，也就是插入map中存在的key值的结点就会失败。
	//string str[] = { "西瓜", "橘子", "苹果", "草莓", "葡萄", "西瓜", "榴莲" };
	//map<string, int> mp1;
	//for (size_t i = 0; i < sizeof(str) / sizeof(str[0]); i++)
	//{
	//	//mp1.insert(make_pair(str[i], 1));       //直接的插入消除了key值的冗余

	//	//map<string, int>::iterator it = mp1.find(str[i]);      //這里会先遍历
	//	//if (it != mp1.end())
	//	//{
	//	//	it->second++;
	//	//}
	//	//else
	//	//{
	//	//	mp1.insert(make_pair(str[i], 1));           //這里会再次遍历
	//	//}

	//	  //第二种方法
	//	  pair<map<string, int>::iterator, bool> bit;     //充分利用這里的insert 实际上insert返回的是一个pair结构体，里面的东西自己看。
	//	  bit = mp1.insert(make_pair(str[i], 1));
	//	  if (bit.second == false)
	//	  {
	//		  bit.first->second++;
	//	  }
	//}
 //   
	//mp1.insert(make_pair("苹果", 6));             //发现這里就会插入失败
	//
	////第三种方法
	//mp1["苹果"]++;      //注意這个东西实际上是second
	//mp1["苹果"]++;
	//mp1["苹果"]++;
	//mp1["苹果"]++;
	//mp1["苹果"]++;
	//mp1["苹果"]++;
	//mp1["苹果"]++;
	//mp1["苹果"]++;
	////這里实现的operator[]实际上并不算是随机位置的插入，实际上是一种利用key值返回value的运算符重载。

	//mp1["橘子"];
	//mp1["榴莲"];      //实际上已经插入了“榴莲”
	//mp1["榴莲"] = 100;  

	//
	//map<string, int>::iterator it = mp1.begin();
	//while (it != mp1.end())
	//{
	//	cout << it->first << ":" << it->second << endl;
	//	it++;
	//}
	////erase使用
	//size_t num = mp1.erase("苹果");
	//cout << "删除元素个数:" << num << endl;
	//map<string, int>::iterator it1 = mp1.erase(mp1.find("橘子"));
	////cout << it1->first << endl;    挂掉


	//-----------------------------------------------multimap---------------------------------------
	/*multimap<string, string> multmp;
	multmp.insert(make_pair("oringe", "橘子"));
	multmp.insert(make_pair("apple", "苹果"));
	multmp.insert(make_pair("pipche", "桃子"));
	multmp.insert(make_pair("left", "左边"));
	multmp.insert(make_pair("banana", "香蕉"));
	multmp.insert(make_pair("strowbreey", "草莓"));
	multmp.insert(make_pair("left", "剩余"));
	multmp.insert(make_pair("left", "剩余"));
	multmp.insert(make_pair("left", "剩余"));
	multmp.insert(make_pair("left", "剩余"));
*/

	//有序
	/*multimap<int, int> multmp1;
	multmp1.insert(make_pair(1, 1));
	multmp1.insert(make_pair(2, 1));
	multmp1.insert(make_pair(5, 1));
	multmp1.insert(make_pair(3, 1));
	multmp1.insert(make_pair(4, 1));
	multmp1.insert(make_pair(7, 1));
	multmp1.insert(make_pair(6, 1));
	
	multimap<int, int>::iterator it = multmp1.begin();
	while (it != multmp1.end())
	{
		cout << it->first <<":"<<it->second<< endl;
		it++;
	}*/


    //统计出现次数最多的前K个水果 
     string str[] = { "西瓜", "橘子", "苹果", "草莓", "葡萄", "西瓜", "榴莲", 
                "西瓜", "橘子", "苹果", "草莓", "葡萄", "西瓜", "榴莲", 
				"西瓜", "橘子", "苹果", "草莓", "葡萄", "西瓜", "榴莲", "桃子", "猕猴桃", "香蕉", "火龙果", 
				"黄瓜", "苹果", "草莓", "葡萄", "西瓜", "榴莲", "桃子", "猕猴桃", "香蕉", "火龙果", "黄瓜",
				"草莓", "葡萄", "西瓜", "榴莲", "橘子", "苹果", "橘子", "苹果", "橘子", "苹果", "橘子", "苹果",
				"猕猴桃", "香蕉", "火龙果", "猕猴桃", "香蕉", "火龙果" ,"猕猴桃", "香蕉", "火龙果", "猕猴桃", "香蕉", 
				"火龙果", "西瓜", "橘子","西瓜", "橘子","西瓜", "橘子","西瓜", "橘子","西瓜", "橘子","西瓜", "橘子",
				"桑枣","桑枣","栗子","梨子",
				"桑枣", "栗子" ,"桑枣", "栗子" ,"桑枣", "栗子" ,"香瓜","香瓜"};
    map<string, int>  mp;
	for(size_t i = 0; i < sizeof(str) / sizeof(str[0]); i++)
	{
		map<string, int>::iterator it = mp.find(str[i]);
		if (it != mp.end())
		{
			mp[str[i]]++;
		}
		else
		{
			mp.insert(make_pair((str[i]), 1));
		}
	}
	map<string, int>::iterator it = mp.begin();
	while (it != mp.end())
	{
		cout << it->first << " : " << it->second << endl;
		it++;
	}
}
void testset()
{
	set<int> st;
	st.insert(1);
	st.insert(2);
	st.insert(1);
	st.insert(6);
	st.insert(8);
	st.insert(9);
	st.insert(3);
	st.insert(5);
	st.insert(7);
	st.insert(7);
	st.insert(7);
	st.insert(2);
	st.insert(5);
	st.insert(5);
	st.insert(5);
	st.insert(5);

	set<int>::iterator sit = st.begin();
	while (sit != st.end())
	{
		cout << *sit << " ";
		sit++;
	}
	cout << endl;
}
int main()
{
	testmap();
	//testset();
	return 0;
}
