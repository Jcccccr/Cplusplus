//数据结构
#include<iostream>
using namespace std;
class String
{ private:
	char* _str;
public:
	String(char* str="")
		:_str(new char[strlen(str)+1])
	{
		strcpy(_str, str);
	}
	~String()
	{
		delete[] _str;
		_str = NULL;
	
	}
};
void TestString（）
{
	String s1("Hello!");
	String s2;
	cout << s1 << endl;
	cout << s2 << endl;

}
int main()
{
	
	TestString();
	return 0;
}