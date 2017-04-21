#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<assert.h>
using namespace std;


//class String
//{
//	friend ostream& operator<<(ostream& out, String& s);
//private:
//	char* _str;
//	size_t _size;               //_size的含义： 下标    字符串的长度
//	size_t _capacity;
//public:
//	String(const  char* str = "")               //const修饰的指针变量是不可以赋给另一个指针变量的這样导致权限放大      
//		:_str(new char[strlen(str) + 1])
//		, _size(strlen(str))
//		, _capacity(_size)
//	{
//		cout << "构造" << endl;
//		strcpy(_str, str);
//	}
//	String(const String& s)
//		:_str(new char[strlen(s._str)+1])
//		, _size(strlen(s._str))
//		, _capacity(_size)
//	{
//		strcpy(_str, s._str);
//		cout << "拷贝构造" << endl;
//	}
//	String& operator=(const String& s)
//	{
//		delete[] _str;
//		_size = 0;
//		_capacity = 0;
//		_str = new char[strlen(s._str) + 1];
//		strcpy(_str, s._str);
//		_size = s._size;
//		_capacity = s._capacity;
//		return *this;
//	}
//	char& operator[](size_t index)
//	{
//		assert(index < _size);
//		return _str[index];
//	}
//	bool operator<(const String& s)            //     <运算符的重载    使用bool值
//	{
//		char* str = this->_str;
//		char* src = s._str;
//		while (*str && *src)           //两个字符串都每到'\0'
//		{
//			if (*str < *src)
//			{
//				return true;    //1          C++中引入了bool类型   0为假  非0为真（一般是1）
//			}
//			else if (*str > *src)
//			{
//				return false;      //0
//			}
//			else
//			{
//				str++;
//				src++;
//			}
//		}
//		if (*src != 0)
//		{
//			return true;
//		}
//		else
//			return false;
//	}
//
//	bool operator==(const String& s)
//	{
//		char* str = this->_str;
//		char* src = s._str;
//		while (*str && *src)
//		{
//			if (*str != *src)
//			{
//				return false;
//			}
//			else
//			 str++;
//			 src++;
//		}
//		if ((*str || *src) == 0)
//			return true;
//		else
//			return false;
//	}
//
//	bool operator>(const String& s)  
//	{
//		/*return !((_str < s._str) || (_str == s._str));*/     //這中方式比较的是首地址   直接拿两个对象去比较  *this就是指的对象
//		return !((*this < s) || (*this == s));
//	}
//	bool operator<=(const String& s)
//	{
//		return (*this < s) || (*this == s);
//	}
//	bool operator>=(const String& s)
//	{
//		return (*this > s) || (*this == s);
//	}
//	bool operator!=(const String& s)
//	{
//		return !(*this == s);
//	}
//
//
//	//******************************************************************************************************JX********************
//	void Expend(size_t n)                   //   增容
//	{
//		assert(n > _capacity);
//		_str = (char*)realloc(_str, n + 1);   //重新开辟空间    //当然這里這样写有些漏洞 没有考虑开辟空间失败的情况  
//		_capacity = n;
//	
//	}
//	void PushBack(char ch)      //后插字符
//	{
//		if (_size == _capacity)
//		{
//			Expend(_size * 2);
//		}
//		_str[_size] = ch;
//		_str[_size + 1] = '\0';
//		_size++;
//	}
//	void Insert(size_t pos,const char ch)    //任意位置插入字符
//	{
//		assert(pos < _size);                 
//		if (_size == _capacity)
//		{
//			Expend(_size * 2);
//		}
//		int end = (int)_size;
//		while (end >= (int)pos)
//		{
//			_str[end + 1] = _str[end];
//			end--;
//		}
//		_str[pos] = ch;
//		_size++;
//	}
//	void Insert(size_t pos, const char* ptr)    //任意位置插入字符串     Insert函数的重载
//	{
//		assert(pos < _size);
//		size_t len = strlen(ptr);
//		int  end = (int)_size;                   //我在這里int强转是想要解决底下那个死循环的bug  但是好像這样做没有效果
//		if (_size + len >  _capacity)
//		{
//			Expend(_size + len);
//		}
//		while (end >= (int)pos)                   //思考为什么我這里pos前面要强转   pos原来是无符号整形  但是我转换成int就可以避免我想在第一个位置插入的时候出错
//		{
//			_str[end + len] = _str[end];
//			end--;
//		}
//		size_t i = 0;
//		for (i = 0; i < len; i++)
//		{
//			_str[pos + i] = ptr[i];
//		}
//		_size += len;
//	}
//
//	void Insert(size_t pos, const String& s)      //将一个对象指向的字符串插入到另一个对象指向的字符串中去
//	{
//		    Insert(pos, s._str);
//	}
//
//	void Erase(size_t pos, size_t len)               //移除
//	{
//		assert(pos < _size);
//		if (pos + len>_size-1)               //考虑這里为什么需要_size-1;
//		{
//			_str[pos] = '\0';
//			_size = pos;
//		}
//		char* dest = _str + pos;                         //字符串操作函数  都会在'\0'停下来；
//		char* src = _str + pos + len;
//		strcpy(dest, src);
//		_size -= len;
//	}
//	int Find(char ch)                   //查找字符
//	{
//		int i = 0;
//		for(i = 0; i < _size; i++)
//		{
//			if (_str[i] == ch)
//				return 1 ;
//		}
//		return 0;
//	}
//	char* Find(const char* ptr)          //查找子串
//	{   
//		char* p=strstr(_str, ptr);
//		if (p != NULL)
//		{
//			return p;
//		}
//		return NULL;
//	       
//	}
//	~String()
//	{
//		if (_str != NULL)
//		{
//			cout << "析构" << endl;
//			delete[] _str;
//			_str = NULL;
//			_size = 0;
//			_capacity = 0;
//		}
//	}
//
//};
//ostream& operator<<(ostream& out, String& s)
//{
//	cout << s._str << endl;
//	cout << s._size << endl;
//	cout << s._capacity << endl;
//	return out;
//}
//void test()
//{
//	
//	String s1("Hello");
//	cout << s1;
//	/*s1.PushBack('o');
//	cout << s1;
//	printf("%p\n", &s1);
//	s1.Insert(1, 'E');
//	cout << s1;
//	printf("%p\n", &s1);
//	s1.Insert(1, "ABCDF");
//	cout << s1;
//	printf("%p\n", &s1);*/
//	String s2("Fjuxin");
//	cout << s2;
//	s2.Insert(0, s1);    //有BUG   pos不能是0             //我這里发现我不能在第一个位置插入  也就是pos能用0传过去  不过我想在插入字符串函数内部end也是size_t类型
//	cout << s2;                                              // 我不管执行多少次end--  都是>pos的 也就是无限循环  所以没法出结果 
//	int i=s2.Find('x');
//	cout << i << endl;                                             //对于内置类型  這里可以直接用   我们所谓的函数重载是重载一个函数达到我们自己创造的类型的运算需求
//	char* src=s2.Find("xin");
//	printf("%p\n", src);
//	cout << (s1 < s2) << endl;
//	return;
//}



//在String的一些操作的模拟实现的过程中所出现的问题：   1.const修饰的函数形参  他到底起到什么样的限制 或者从底层 我是怎么约束這个变量的  我想要改变一个const修饰的变量也是可以的使用一个指针是吗？
//在這里面  我们使用了_size 和_capacity 其实他们都是下标（实质上）   但是就是是因为是下标  在一些操作范围的选定的时候就带了一些问题（非常细节）
//這里面我碰到了bug  pos的问题  就是因为pos声明的时候就是无符号整形  所以在走起来的时候碰到了死循环  后来强转就行了 但是我不太清楚啥意思
//这写代码写下来我也更加明白了C++类和对象   运算符重载的深层内涵   其实内置类型运算符随便用（运用内置类型的运算符创造自定义类型的运算）  但是我们在创造一个类的对象之后 很多操作都需要我们去创造 
//给我们更灵活的空间去发挥   
//這个程序里面是对于字符串的操作  也让我体会到 我们应该重视'\0';  有的时候也应该灵活利用'\0'

//整体来看  有些问题我确实没解决好  比如const    我觉得我还得再多看看字符串這方面的内容  我觉得用的蛮多（后来我把我的问题解决了）

//最后   写时拷贝 string里面引入這东西之后我就没明白   就是我要创建一个对象或者改变一个对象所指向的内容的时候   我们就需要用到写时拷贝 其实是为了提高效率  
//我想知道   就這段代码里面  运用的都是写时拷贝思想吗？    而且[]运算符重载没有重新开辟空间啊  我没看出来他哪里写时拷贝了

//


//关于字符串常量和字符数组的一些重新理解
void test()
{
	//char* p = "abcdef";                       //這里是字符串常量（静态区） 用指针P指向他 可以通过p看到他  但是我发现我不能通过p改变他
	//char* str=new char[strlen(p)+1];           //我只有自己开一段空间  用一个指针指向他   我就能通过這个指针维护他
	//strcpy(str, p);
	//printf("%s\n", str);
	//char* ptr = NULL;
	//ptr = str;                             //我以前一直以为我把一个指针变量赋值给另一个指针变量  那么那个指针变量是不可以改变原来指针指向的空间的值的
	//printf("%s\n", ptr);                    //但是通过实验我发现不是的   只要一个指针指向一块空间 那么這个指针就可以维护這个空间 可以更改内容 关键问题就是這个空间让不让人改（常量）
	//ptr[1] = 'A';
	//printf("%s\n", ptr);
	//delete[] str;
	char p[] = "abcdef";                 //這里可以用p直接更改是因为p开辟的是一个字符数组  包括'\0'在内   关键就是這个数组放在栈里面 p可以操纵他
	printf("%s\n", p);
	p[1] = 'A';
	printf("%s\n", p);
	printf("%d\n", sizeof(p));

}  //這样我也就明白了为什么const修饰的指针是不可以传给非const修饰的指针了    因为const修饰了之后指针指向的对象是不能被改变的 给另一个很浪的指针之后他把内容改变了岂不是很尴尬