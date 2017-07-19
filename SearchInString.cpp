#define _CRT_SECURE_NO_WARNINGS 1

//查找一个字符串中第一个只出现两次的字符。
//比如：“abcdefabcdefabc”中第一个只出现两次为‘d’，要求时间复杂度为O(N)，空间复杂度为O(1)

//方案一：使用一个26个字母的数组，数组中单元的位置上放置出现的字母的个数，然后像文件压缩那样，遇到一个字母就找相应的数组的位置然后+1，
//遍历一遍之后就得到了所有出现的字母的次数统计，然后注意了： 遍历原来的字符串，检查每一个字符出现的次数，要是是2个就返回
#include<iostream>
#include<string>
#include<assert.h>

using namespace std;
char  str[26] = { 0 };
char SearchInString(char *p)
{
	assert(p);
	size_t i = 0;
	while (p[i] != '\0')
	{
		str[p[i] - 'a']++;
		++i;
	}
	size_t j = 0;
	while (p[j] != '\0')
	{
		if (str[p[j] - 'a'] == 2)
		{
			return p[j];
		}
		j++;
	}
	printf("没有只出现两次的字母\n");
	return 0;
}
void test()
{
	//char*  p = "abjcmkdjefjabcdefakbcm";
	//char*  p = "akbjbkbjsudni";
	char*  p = "";
	cout << SearchInString(p) << endl;
}
int main()
{
	test();
	return 0;
}
