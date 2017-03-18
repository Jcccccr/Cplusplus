#include<iostream>
using namespace std;

class Time
{
	friend class Date;//记住调用关键字class；
private:
	int _hour;
	int _minute;
	int _second;
public:
	Time(int hour, int minute, int second)
		: _hour(hour)
		, _minute(minute)
		, _second(second)
	{
	}

};

class Date
{ private:
	int _year;
	int _month;
	int _day;
	Time _t;//在這里申明一个Time类型的对象_t；
public:
	Date(int year=2017,int month=3, int day=16)
		:_year(year)
		, _month(month)
		, _day(day)
		, _t(1,1,1)//我不知道为什么要在這里赋值；为什么不在其他地方给_t赋值；
	{
	  
	}
	void Display()
	{
		cout << _year << "-" << _month << "-" << _day << endl;
		cout << _t._hour << "-" << _t._minute << "-" << _t._second << endl;//定义为友元之后可以跑到上面去访问Time类
    }
}; 
int main()
{
	Date d1;//這里在初始化对象的时候不仅包括Date还有Time;
	d1.Display();
	return 0;
}