#define _CRT_SECURE_NO_WARNINGS 1
//引用计数+写时拷贝思想的运用      通过[]运算符的重载体会写时拷贝     
#include<iostream>
#include<assert.h>
using namespace std;

class String
{
private:
	char* _str;
	int* _refCount;
public:
	String(const char* str = "")
		:_str(new char[strlen(str) + 1])
		, _refCount(new int(1))             //开辟一块整形空间用指针维护
	{
		strcpy(_str, str);
		cout << "构造" << endl;
	}
	String(const String& s)
		:_str(s._str)
	{
		cout << "拷贝构造" << endl;
		_refCount = s._refCount;
		*(_refCount)++;
	}
	char& operator[](size_t index)             //针对于测试函数里面注释出来的问题 我這里对[]重载进行了写时拷贝 //這里我写错了   要返回一个char&
	{
		if (--(*_refCount) != 0)      //当我要改变的对象所指向的空间还有其他的对象指向的时候 我要更改里面的内容  就要自己重新开辟空间
		{
			                                       //這样就解决了多个对象指向同一个内容的而其中一个要进行改变（而不想影响其他对象的内容）的时候
			char* ptr = _str;
			_str = new char[strlen(ptr) + 1];         //重新开辟空间  不影响其他的对象
			_refCount = new int(1);
			strcpy(_str, ptr);
		}
		assert(index < strlen(_str));
		return _str[index];                         
	}
	const char& operator[](size_t index) const  //我们在利用下标来改变一个对象指向的空间的内容的时候  需要写时拷贝重开空间 
	{                                          //但是這样的话貌似每次使用到[]都会重开空间 我们在读的时候貌似不需要改变字符串的内容
		assert(index < strlen(_str));
		return _str[index];                          //例如cout<<s1[5]<<endl;  我们要读的时候并不需要重新开辟空间存放字符串和引用计数  所以
	}                                               //我们必须要再次重载一个[]函数  专门供读取使用

	String& operator=(const String& s)
	{
		if (this != &s)
		{
			if (--(*_refCount) == 0)              //這里注意：   *_refCount在判断的时候已经改变了  不管进没进去 都改变了  我在练习的时候出现错误
			{
				delete[] _str;
			}
			_str = s._str;
			_refCount = s._refCount;
			*(_refCount)++;
		}
		return *this;
		
	}
	void Print()
	{
		cout << _str << endl;
	}
	~String()
	{
		if (_str)
		{
			if (--(*_refCount) == 0)          //析构的时候会对计数器进行判断
			{
				cout << "析构" << endl;
				delete[] _str;
				_str = NULL;                //注意习惯  防止垂悬指针
			}

		}
	}
};
int main()
{
	String s1("hello");
	s1.Print();
	String s2(s1);
	s2.Print();
	s2[1] = 'E';           //写时拷贝
	s2.Print();
	s1.Print();           //到這里我们发现我原本是想要改变s2对象的内容   但是发现s1也随之改变了  因为s2和s1指向同一块空间 
	s1 = s2;
	s1.Print();
	String s3 = "HELLO";
	String s4 = "HHHHH";
	s4 = s3;
	s4.Print();
	String s5 = "jjjjj";
	s5.Print();
	cout << s5[2] << endl;     //读
	return 0;
}