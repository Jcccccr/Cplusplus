//#define _CRT_SECURE_NO_WARNINGS 1
//
//class A
//{
//private:
//	int _a;
//	int _b;
//	int _c;
//public:
//	void SetA();
//	void SetB();
//	void SetC();
//};
//
//void A::SetA()           //类内声明  类外定义
//{
//
//}
//void A::SetB()
//{
//
//}
//void A::SetC()
//{
//
//}
//int main()
//{
//	A a;
//	a.SetA();
//	a.SetB();
//	a.SetC();
//	return 0;
//}
#include<iostream>
using namespace std;
//class Date
//{
//private:
//	int _year;
//	int _month;
//	int _day;
//public:
//	void SetDate(int year,int month,int day)
//	{
//		_year = year;
//		_month = month;
//		_day = day;
//	}
//	//void Display()
//	//{
//	//	cout <<_year << "-" << _month << "-" << _day << endl;
//	//	cout << this->_year << endl;
//	//}
//	void Display()
//	{
//		cout << this << endl;
//	}
//
//};
//int main()
//{
//	Date A;
//	/*A.SetDate(2017, 4, 13);*/
//	cout << &A << endl;
//	A.Display();                                 //這个this指针实际上是這个类实例化的一个对象的地址
//	return 0;
//}

class Date
{
private:
	int _year;
	int _month;
	int _day;
public:
	Date(int year=1999, int month=10, int day=10)                     //构造函数   初始化对象
	{
		_year = year;
		_month = month;
		_day = day;
		cout << _year << "-" << _month << "-" << _day << endl;
	}

	void Display()
	{
		;
	}
	~Date()
	{
		cout << "析构函数" << endl;
	}
};
int main()
{                               //构造函数在创建一个对象的时候自动调用一次
	Date A(2017,4,13);
	Date B;                   //调用缺省构造函数（构造函数内有了初始化的值）
	return 0;
}

  



