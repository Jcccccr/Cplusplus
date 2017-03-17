#include<iostream>//這部分的练习主要是在强调深拷贝的重要性
using namespace std;
class String
{
	friend ostream& operator<<(ostream& os, String& s);
private:
	 char *_str;//为了改变*_str的值這里不能有const；
public:
	/*String()//如果初始化一个对象没有赋值，那么应该构造无参函数让他调用，但是在后面就会遇到问题。
		:_str(NULL)
	{
		cout << "String()" << endl;
	}*/
	String(const char *str="")//這里使用const 那么上面就要同样使用const修饰
		:_str(new char[strlen(str)+1])
	{
		strcpy (_str, str);//拷贝了str的值；
		cout << "_str" << endl;
	}
	String(const String& s)
		:_str(new char[strlen(s._str)+1])
	    
	{
		cout << "const string& s" << endl;
		strcpy(_str, s._str);//strcpy和memcpy之间有什么差别？；
	}
	String& operator=(const String& s)//=运算符重载//记得要加上判断是否会自赋值；
	{
		cout << "String& operator=(const String& s)" << endl;
		
		if (&s!=this)//判断是否会自赋值；
		{
		delete[] _str;
		_str = new char[strlen(s._str) + 1];
		strcpy(_str, s._str);
		}//传统写法 开辟空间
		
		return *this;//不要忘了返回值;

	}

	~String()//注意析构函数不能忘记；
	{
		if (_str != NULL)
		{
			delete[] _str;//开辟空间之后要记住回收；
		}
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
	cout << s1 << endl;//输出运算符重载
	String s2(s1);//拷贝构造
	String s3;//其实在初始化对象的时候由于调用了构造函数 所以s3=""  是占用空间的;//所以在后面s3自己开辟一块空间的时候這个""是需要释放的。
	s3 = s2;//這里就需要使用到operator=的运算符重载，但是仍然会出现浅拷贝的问题，所以继续让s3开辟一块自己的空间  
    //不管什么情况，在赋值操作之前，都需要把左值内的东西清空
	//如果我们没有写=号的运算符重载，那么這里就是默认浅拷贝，最后出问题


	/*string str1 = ("abcdef");
	cout << str1 << endl;
	str1[4] = 'w';
	cout << str1 << endl;*/
	system("pause");
	
	return 0;
}