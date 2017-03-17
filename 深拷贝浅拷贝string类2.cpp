//
////内置的string类型
//#include<iostream>
//using namespace std;
//#include<string>
//int main()
//{
//	string str1("hello world.");
//	string str2(str1);//這里调用的是拷贝构造函数；
//	string str3=str2;//這里调用的是operator=的运算符重载；
//	cout << str1 << endl;
//	cout << str2 << endl;
//	cout << str3 << endl;
//	system("pause");
//	return 0;
//}
////這个是一个内置类型的string
////下面自定义一个string类来完成上面那个程序的功能；


#include<iostream>
using namespace std;
class String
{
	friend ostream& operator<<(ostream& os, String& s);
 private:
	 const char *_str;
public:
	String(const char *str)//這里使用const 那么上面就要同样使用const修饰
		:_str(str)
	{
		cout << "_str" << endl;
	}

};
 ostream& operator<<(ostream& os, String& s)
{
	os << s._str;
	return os;
}
int main()
{
	String s1("abcdef");
	cout << s1;

	return 0;
}