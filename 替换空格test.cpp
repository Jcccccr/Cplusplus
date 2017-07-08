#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
#include<vector>
using namespace std;

//牛客刷题，此解法应该不是很好
void replaceSpace(char* &str, int length)   //题目的形参没有给引用，如果不是引用就很难写下去。
{
	/*int i = 0;
	vector<char> _arr;
	while (i<length)
	{
		if (str[i] != ' ')
		{
			_arr.push_back(str[i]);
		}
		else
		{
			_arr.push_back('%');
			_arr.push_back('2');
			_arr.push_back('0');
		}
		i++;
	}
	_arr.push_back('\0');
	str = new char[_arr.size()];
	for (size_t i = 0; i < _arr.size(); i++)
	{
		str[i] = _arr[i];
	}*/

	//方法2：但是這种方法存在问题。
	char* _str = new char[strlen(str) + 1];
	strcpy(_str, str);
	//首先空间是要增大的，但是至于要增加多大，需要经过计算。
	str = _str;
}

int main()
{
	char* str = "Hello World!";
	replaceSpace(str, strlen(str));
	cout << str << endl;
}