#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
using namespace std;
//class Date
//{
//private:
//	int _year;
//	int _month;
//	int _day;
//public:
//	Date(int year=2017, int month=10, int day=1)
//		:_year(year), _month(month), _day(day)
//	{
//	}
//	Date(Date& d)
//		:_year(d._year), _month(d._month), _day(d._day)
//	{
//	}
//	~Date()
//	{
//	}
//	void Test();
//	void Display(Date &d)  
//	{
//		Test();
//		cout << d._month << endl;
//		/*_year = 2018;*/
//		cout << _year << "-" << _month << "-" << _day << endl;
//	}
//	
//};
//
//inline void Date::Test()                                                      //在类外定义内联成员函数
//{
//	cout << _year << endl;
//}
//int main()
//{
//	Date d(2017, 4, 14);
//	Date d2 = d;
//    Date d3;
//	d3.Display(d2);
//	d.Display(d);
//	d2.Display(d);
//	return 0;
//}

//class Complex
//{
//private:
//	int _real;
//	int _image;
//public:
//	Complex(int real=1,int image=0)
//		:_real(real), _image(image)
//	{
//	}
//	Complex(Complex& d)
//		:_real(d._real), _image(d._image)
//	{
//	}
//	Complex operator+(Complex& c)
//	{
//		Complex temp;
//		temp._real = _real + c._real;
//		temp._image = _image + c._image;
//		return temp;                                      //這里注意  return 這里做了很多的事情 拷贝构造 然后析构然后再回来结束之這个函数
//	}                                                       //一定要清楚這里的过程  你就能明白以前我们说的为什么我们不能返回一个临时变量的引用了
//	void operator<<(ostream& out)
//	{
//		out << _real << "+" << _image << "j" << endl;
//	}
//	~Complex()
//	{
//	}
//
//	void Display()
//	{
//		cout << _real << "+" << _image << "j"<<endl;
//	}
//};
//int main()
//{
//	Complex c1(1, 1);
//	Complex c2 = c1;
//	Complex c3 = c2 + c1;
//	Complex c4;
//	c1.Display();
//	c2.Display();
//	c3.Display();
//	c3 << cout;                                //当我们再类内对输入输出运算符进行重载的时候，就产生了一些很别扭的问题 如何解决问题？
//	return 0;
//}



//下面我写一下让输入输出运算符重载能正常的解决方案（将重载函数定义为友元）
//class Date
//{
//	friend void Display(Date& d);    //友元
//	friend ostream& operator<<(ostream& out, Date& d);
//	friend istream& operator>>(istream& in, Date& d);
//private:
//	int _year;
//	int _month;
//	int _day;
//public:
//	Date(int year=2000,int month=10,int day=1)
//		:_year(year), _month(month), _day(day)
//	{	
//	}
//	Date(Date& d)
//		:_year(d._year), _month(d._month), _day(d._day)
//	{
//	}
//	~Date()
//	{
//	}
//};
//void Display(Date& d)
//{
//	cout << d._year << "-" << d._month << "-" << d._day << endl;
//}
//
//istream&  operator>>(istream& in, Date& d)
//{
//	in >> d._year;
//	in >> d._month;
//	in >> d._day;
//	return in;
//}
//
//
//ostream& operator<<(ostream& out, Date& d)                //为什么我们要定义为友元呢？从目的来看 我们想要达成正常的输出的形式，
//                                                            //自然是cout要去调用<<操作符重载函数，而d2则是运算符重载函数中的参数，但是我们在类中
//{                                                             //的成员函数自然是对象去调用 必须d2在前 只能尴尬下去
//	out << d._year << "-" << d._month << "-" << d._day << endl;       //那么我们想是不是可以自己写一个 不在类里面写了 把顺序摆正就行  
//	return out;
//}  
//                                                                //但是我们遇到了一个问题：如果我们在类外定义一个函数，怎么才能访问到
//int main()                                                 //类内的成员呢，   這里就需要在类中声明为友元  
//{
//	Date d1;                                               //类外的函数在类内声明为友元  就可访问类中的所有成员 公保私
//	Date d2 = d1;
//	Display(d2);
//	cout << d2 << d1 << endl;
//	Date d3;
//	Date d4;
//		cin >> d3 >> d4;
//		cout << d3 << d4;                             //输入输出运算符重载的注意:在写函数的时候用ostream& 作为返回值 
//	return 0;                                        //這样可以实现连续输入输出；
//}


//友元类
//在一个类中可以访问另一个类中的所有成员
//class Time
//{
//	friend class Date;
//private:
//	int _hour;
//	int _minute;
//	int _second;
//public:
//	Time(int hour=12, int minute=0, int second=0)
//		:_hour(hour), _minute(minute), _second(second)
//	{
//	}
//	Time(Time& t)
//	{
//		_hour = t._hour;
//		_minute = t._minute;
//		_second = t._second;
//	}
//	~Time()
//	{
//	}
//
//};
//class Date
//{
//private:
//	Time _t;
//	int _year;
//	int _month;
//	int _day;
//
//public:
//	Date(Time t, int year = 2010, int month = 10, int day = 1)
//		:_t(t),_year(year), _month(month), _day(day)
//	{
//	}
//	Date(Date& d)
//	{ 
//		_t = d._t;
//		_year = d._year;
//		_month = d._month;
//		_day = d._day;
//	}
//	void Display()
//	{
//		cout << _year << "-" << _month << "-" << _day << "-" << _t._hour << ":" << _t._minute << ":" << _t._second << endl;
//	}
//
//};
//int main()
//{
//	Time t1(23, 59, 59);
//	Date d1(t1,2017,10,01);
//	d1.Display();
//	Date d2 = d1;
//	d2.Display();
//	return 0;
//}





//类的静态成员变量 和静态成员函数
//class A
//{
//private:
//	 static int _count;          // 当成员变量为一个静态变量时   初始化就不能在初始化列表中初始化 也不能在构造函数内部 反正是不能在类内了
//	 int num;
//public:
//	A()
//	{   
//		num = 10;
//		_count++;
//	}
//	~A()
//	{
//	}
//	void Display()
//	{
//		cout << _count << endl;
//	}
//	 void SDisplay()
//	{   
//		/*cout << num << endl;*/
//		 cout << _count << endl;
//		cout << "静态成员函数" << endl;               //静态成员函数可以在类内进行定义， 但是请注意他在调用时的语法
//	}
//};
//   int A::_count = 0;       //成员变量是一个静态变量的时候 我们在类外进行初始化，初始化方式，
//int main()
//{
//	A a1;
//	A a2;
//	/*a1.SDisplay();*/    //這种访问方式是不对的  静态成员函数是共有的 不能被某个对象所调用 要调用只能类来调用
//	a1.SDisplay();      //静态成员函数必须要用這样的调用方式；
//	a1.Display();
//	a2.Display();      //输出结构是2 2  思考为什么  ：静态成员变量放在数据段  他不属于某个对象 
//	return 0;           //静态成员是每一个类的对象所共有的  不论哪个对象去改变它 他都是改变后的值 不会因为换了一个对象就置初值
//}

//注意：静态成员函数没有隐含的this指针
//  静态成员函数是不可以访问非静态成员的
// 非静态成员函数是可以访问静态成员的






//前置++   后置++的重载
//class Complex
//{
//private:
//	int _real;
//	int _image;
//public:
//	Complex(int real=1,int image=0)
//		:_real(real), _image(image)
//	{
//	}
//	Complex(Complex& c)
//		:_real(c._real), _image(c._image)
//	{
//	}
//	Complex operator++(int)   //后置++    这里的int只是为了将前置和后置区分
//	{
//		Complex tmp(*this);     //這里调用了拷贝构造
//		_real++;
//		_image++;
//		return tmp;
//	
//	}
//	Complex& operator++()  //前置++
//	{
//		_real++;
//		_image++;
//		return *this;
//	}
//	void Display()
//	{
//		cout << _real << "+" << _image << "j" << endl;
//	}
//	~Complex()
//	{
//	}
//
//
//};
//int main()
//{
//	Complex c1;
//	c1.Display();
//	c1++;
//	Complex c2;
//	++c2;
//	c2.Display();
//	return 0;
//}



