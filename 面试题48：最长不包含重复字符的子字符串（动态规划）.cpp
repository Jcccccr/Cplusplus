#define _CRT_SECURE_NO_WARNINGS 1
//动态规划：最长不包含重复字符的子字符串的长度和位置

#include<iostream>
#include<string>
#include<assert.h>
using namespace std;

typedef struct GetLongestSubStrFlag
{
	size_t sptr;
	size_t Fsptr;
}GetStr;
GetStr GetLongestSubString(const string& str)      //注意输入的字符串为空字符串
{
	GetStr Get;
	if (str.size() == 0)            //输入空字符串
		perror("输入错误");
	int length = str.size();
	size_t MaxFsptr = 0;           //给一个变量记录曾经的最长值。
	Get.sptr = 0;
	Get.Fsptr = 0;            //以指向的字符作为结尾的最短不重复子串的长度  刚开始给初始值0
	int *ass = new int[26];        //存放26个字符对应的出现在字符串中的下标值
	for (size_t i = 0; i < 26; i++)  
	{
		ass[i] = length;
	}
	for (size_t i = 0; i < length; i++)
	{
		if (str[i] == length)              //该位置之前不曾出现过，添加记录    
		{
			ass[str[i] - 'a'] = i;
			Get.Fsptr++;
			if (Get.Fsptr > MaxFsptr)
				MaxFsptr = Get.Fsptr;
			continue;
		}
		//此位置之前出现过，查看位置计算距离分情况考虑
		else
		{
			int d = i - ass[str[i] - 'a'];      
			if (d <= Get.Fsptr)            //注意等于的情况
			{
				if (Get.Fsptr > MaxFsptr)
					MaxFsptr = Get.Fsptr;
				Get.Fsptr = d;
				Get.sptr = ass[str[i] - 'a'] + 1;              //更新头指的位置
			}
			else
			{
				Get.Fsptr++;
				if (Get.Fsptr > MaxFsptr)
					MaxFsptr = Get.Fsptr;
			}
			ass[str[i] - 'a'] = i;
			continue;
		}
	}
	Get.Fsptr = MaxFsptr;
	return Get;
}
int main()
{
	//string str("arabcacfr");
	//string str("acbadefgaaaaa");
	//string str("aaaaaaaaaaaa");
	string str("a");
	//string str;
	cout << GetLongestSubString(str).Fsptr << endl;      //最长子串的长度
	return 0;
}






