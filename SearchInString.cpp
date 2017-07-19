#define _CRT_SECURE_NO_WARNINGS 1

//查找一个字符串中第一个只出现两次的字符。
//比如：“abcdefabcdefabc”中第一个只出现两次为‘d’，要求时间复杂度为O(N)，空间复杂度为O(1)

//方案一：使用一个26个字母的数组，数组中单元的位置上放置出现的字母的个数，然后像文件压缩那样，遇到一个字母就找相应的数组的位置然后+1，
//当加完了之后检查一下数组中的值，如果是2 直接退出完成查找。

#include<iostream>
#include<string>

using namespace std;

char  str[26] = { 0 };
char SearchInString(char *p)
{
	size_t i = 0;
	while (p[i] != '\0')
	{
		str[p[i] - 'a']++;
		if (str[p[i] - 'a'] == 2)
		{
			return p[i];
		}
		++i;
	}
	return 'a';
}
void test()
{
	char*  p = "abcdefabcdefabc";
	cout<<SearchInString(p);
}
int main()
{
	test();
	return 0;
}
