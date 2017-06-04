#define _CRT_SECURE_NO_WARNINGS 1

//引用计数+写时拷贝的练习     []运算符的重载
#include<iostream>
#include<assert.h>
using namespace std;
class String
{
	friend ostream& operator<<(ostream& out, String& s);
private:
	char* _str;
	int* _refCount;
public:
	String(const char* str = "")   //构造函数
		:_str(new char[strlen(str)+1])
		, _refCount(new int(1))
	{
		cout << "构造" << endl;
		strcpy(_str, str);
	}
	String(String& s)              //拷贝构造
	{
		cout << "拷贝构造" << endl;
		_str = s._str;
		_refCount = s._refCount;
		++(*_refCount);
	}
	String& operator=(String& s)    //赋值运算符重载
	{
		if (this != &s)
		{
			if (--(*_refCount) == 0)
			{
				delete[] _str;
				delete _refCount;
			}
			_str = s._str;
			_refCount = s._refCount;
			++(*_refCount);
		}
		return *this;                       //记得返回值
	}
	char& operator[](size_t index)
	{
		assert(index < strlen(_str));                 //這样的写法是存在错误的
		return _str[index];
	}

	~String()
	{
		if (NULL != _str)
		{
			if (--(*_refCount) == 0)            //這里判断自己指向的空间有没有其他对象指向
			{
                cout << "析构" << endl;
				delete[] _str;
				delete _refCount;
				_str = NULL;
			}
		}
	}

};
ostream& operator<<(ostream& out, String& s)
{
	out << s._str;
	/*cout << s._refCount;*/
	return out;
}
int main()
{
	String s1("hello\n");
	cout << s1;
	String s2(s1);
	cout << s2;
	String s3(s2);
	String s4(s3);
	cout << s4;
	String s5("BIT\n");
	s4 = s5;
	cout << s4;
	s5[1] = '0';
	cout << s5;
	return 0;
}