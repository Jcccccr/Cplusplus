#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<assert.h>
using namespace std;


class String
{
	friend ostream& operator<<(ostream& out, String& s);
private:
	char* _str;
	size_t _size;
	size_t _capacity;
public:
	String(const  char* str = "")
		:_str(new char[strlen(str) + 1])
		, _size(strlen(str))
		, _capacity(_size)
	{
		cout << "构造" << endl;
		strcpy(_str, str);
	}
	String(const String& s)
		:_str(new char[strlen(s._str)+1])
		, _size(strlen(s._str))
		, _capacity(_size)
	{
		strcpy(_str, s._str);
		cout << "拷贝构造" << endl;
	}
	String& operator=(const String& s)
	{
		delete[] _str;
		_size = 0;
		_capacity = 0;
		_str = new char[strlen(s._str) + 1];
		strcpy(_str, s._str);
		_size = s._size;
		_capacity = s._capacity;
		return *this;
	}
	char& operator[](size_t index)
	{
		assert(index < _size);
		return _str[index];
	}
	bool operator<(const String& s)
	{
	}
	bool operator>(const String& s)
	{
	}
	bool operator<=(const String& s)
	{
	}
	bool operator>=(const String& s)
	{
	}
	bool operator!=(const String& s)
	{
	}


	//********************************************************************************************
	void Expend(size_t n)                   //   增容
	{
		assert(n > _capacity)
		{

		}
	}
	~String()
	{
		if (_str != NULL)
		{
			cout << "析构" << endl;
			delete[] _str;
			_str = NULL;
			_size = 0;
			_capacity = 0;
		}
	}

};
ostream& operator<<(ostream& out, String& s)
{
	cout << s._str << endl;
	cout << s._size << endl;
	cout << s._capacity << endl;
	return out;
}
void test()
{
	String s1("Hello");
	String s2(s1);
	String s3;
	s3 = s2;
	cout << s3;
	s1[4] = '0';
	cout << s1;
	return;
}