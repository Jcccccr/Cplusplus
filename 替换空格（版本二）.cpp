#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
#include<vector>
using namespace std;

//替换字符串中的空格为$$$。要求时间复杂度为O(N)
//例如：将"talk is cheap show me the code"替换。为"talk$$$is$$$cheap$$$show$$$me$$$the$$$code"。


//Soultion No.1
void ReplaceBlank(char*& p)
{
	size_t i = 0;
	vector<char>  _v;
	while (p[i] != '\0')
	{
		if (p[i] == ' ')
		{
			_v.push_back('$');
			_v.push_back('$');
			_v.push_back('$');
			i++;
			continue;
		}
		_v.push_back(p[i]);
		i++;
	}
	_v.push_back('\0');
	char* tmp = new char[_v.size()];
	for (size_t i = 0; i < _v.size(); i++)
	{
		tmp[i] = _v[i];
	}
	p = tmp;
}
//方案二：  使用string  最后想将字符指针赋值但是没有办法将string的首字符的地址赋值
//void ReplaceBlank1(char*& p)
//{
//	size_t i = 0;
//	string s1;
//	while (p[i] != '\0')
//	{
//		if (p[i] == ' ')
//		{
//			s1.push_back('$');
//			s1.push_back('$');
//			s1.push_back('$');
//			i++;
//			continue;
//		}
//		s1.push_back(p[i]);
//		i++;
//	}
//	char* tmp = new char[s1.length + 1];
//	 
//}

int main()
{
	char *p = "talk is cheap show me the code";
	ReplaceBlank(p);
	cout << p << endl;
	return 0;
}