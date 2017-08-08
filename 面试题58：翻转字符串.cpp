#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
#include<assert.h>
using namespace std;
//字符串的翻转问题
//举例子： 输出"I am a student ." 输出"student .a am I"
//方案：非常简单：两次翻转

//翻转一个单词  
void ReverseWords(char* str,int begin,int end)
{
	assert(str);
	char tmp = 0;
	while (begin != end)
	{
		tmp = str[begin];
		str[begin] = str[end];
		str[end] = tmp;
		begin++;
		end--;
	}
}
void ReverseAll(char* str, int size)
{
	assert(str);
	assert(size);
	int begin = 0;
	int end = size - 2;
	char tmp = 0;
	while (begin != end)
	{
		tmp = str[begin];
		str[begin] = str[end];
		str[end] = tmp;
		begin++;
		end--;
	}
	//前后指针法，确定需要翻转的字符串的长度
	int head = 0;
	int tail = 0;  
	while (str[head] != '\0')
	{
		head++;
		while (head != ' ')
		{
			if (str[head] == '\0')
				break;
			head++;
		}
		ReverseWords(str, tail, head - 1);
		tail = head;
	}
}
void test(void)
{
	char str[] = "I am a student.";
	ReverseAll(str, strlen(str) + 1);
	cout << str << endl;
}
int main()
{
	test();
	return 0;
}