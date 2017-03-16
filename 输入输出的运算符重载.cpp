#include<iostream>
using namespace std;
class Date 
{  
	friend ostream&  operator<<(ostream& os, const Date& d);
private:
	int _year;
	int _month;
	int _day;
public:
	Date(int year=2017,int month=3,int day=14)
		:_year(year), _month(month), _day(day)
	{
	}
	
	void Display()
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}
};
 ostream&  operator<<(ostream& os,const Date& d)//cout是ostream里面的一个对象，而ostream是一个类，输出类；  os是一个临时对象；//为什么是這种形式我不能很容易的去理解
{                                               //不使用void是为了能够连续输入输出；
	os << d._year << "-" << d._month << "-" << d._day<< endl;
	return os;//必须返回一个值，但是我不太清楚這里面的原理，之前重载+-的时候都是return *this;那又是为什么；
}
int main()
{
	Date d1;
	cout << d1;
	system("pause");
	return 0;
}