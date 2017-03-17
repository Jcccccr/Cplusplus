#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
using namespace std;
class String
{
	friend ostream& operator<<(ostream& os, String& s);
private:
	 char* _str;
public:
	String(const char* str="")//一定要清楚为啥我们在构造函数的时候就要开辟空间；
		:_str(new char[strlen(str)+1])
	{
		strcpy(_str, str);
		cout << "构造函数" << endl;
		cout << _str << endl;
	}
	String(const String& s)
		:_str(new char[strlen(s._str)+1])
	{
		strcpy(_str, s._str);
		cout << "拷贝构造函数" << endl;
		
	}
	String& operator=(const String& s)//赋值运算符的重载；
	{
		if (&s != this)
		{ 
			delete[] _str;
			_str=new char[strlen(s._str) + 1];//这个不是初始化列表
			strcpy(_str, s._str);
		} 
		return *this;
	}
	~String()
	{   
		if (_str != NULL)//是地址不为空
		{  
			delete[] _str;
			_str = NULL;
		}
		
		cout << "析构函数" << endl;
	}
};
ostream& operator<<(ostream& os, String& s)
{
	os << s._str;
	return os;
}
int main()
{
	String s1("Fighting!");
	String s2(s1);
	cout << s2 << endl;
	String s3("JUXIN");
	s2 = s3;//這里就需要一个operator=的赋值运算符的重载了；注意在重载的时候需要释放咱们在最前面构造函数的""空字符串占用的空间哦
	//s1[4] = 'T';//我们想要实现更改里面的某个字母就必须要进行[]的运算符重载；

	

	system("pause");
	return 0;
}