#define _CRT_SECURE_NO_WARNINGS 1


//這道题注意测试用例  如果所有的字符都是重复的怎么办  使用标志位
#include<iostream>
#include<string>
using namespace std;
char GetTheFirstChrInString(const string& str)
{
	if (str.size() == 0)
		perror("errorinput");
	int* ass = new int[26];
	for (size_t i = 0; i < 26; i++)
	{
		ass[i] = -1;
	}
	int length = str.size();
	for (size_t i = 0; i < length; i++)
	{
		if (ass[str[i] - 'a'] == -1)     //首次出现
			ass[str[i] - 'a'] = i;
		else                           //重复出现
			ass[str[i] - 'a'] = -1;
	}
	int Min = 0;
	int MinIndex = 0;
	bool JusOnce = false;                //注意這里,刚开始没有考虑到输入的没有只出现一次的
	for (size_t i = 0; i < 26; i++)
	{
		if (ass[i] != -1)
		{
			Min = ass[i];
			MinIndex = i;
			JusOnce = true;           //只出现了一次
			break;
		}
	}
	if (!JusOnce)
		return '\0';                  //不存在只出现了一次的字符
	for (size_t i = 0; i < 26; i++)
	{
		if (ass[i] != -1)
		{
			if (ass[i] < Min)
			{
				Min = ass[i];
				MinIndex = i;
			}
		}
	}
	return MinIndex + 'a';
}
//  TEST
int main()
{
	//string str("abaccdeff");
	//string str("aaaaaaaa");
	//string str("awertyu");
	//string str("kwertyu");
	string str;
	cout << GetTheFirstChrInString(str) << endl;
	return 0;
}