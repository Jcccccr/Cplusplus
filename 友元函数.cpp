#include<iostream>
using namespace std;
class Date
{
	friend void Display(const Date& d);//用friend 再加上类外定义的一个打印函数那么就成了一个友元函数
private:
	int _year;
	int _month;
	int _day;
public:
	Date(int year=2017,int month=3,int day=14)//构造函数
		: _year(year)
		, _month(month)
		, _day(day)//初始化列表；
	{
		}

};
void Display(const Date& d)//在這里我还是不太明白（const Date& d）的意义 不懂为什么diaplay打印函数在类外定义就得這样写；
{
	cout << d._year << "-" << d._month << "-" << d._day << endl;//注意d.
}
int main()
{
	Date d1;
	Display(d1);//首先可以确定的是Display不是成员函数，那么不能使用d1.Display()来调用里面的成员函数，只能把d1的值放进去硬生生的调用，
	//但是遇到的问题就是d1的算是成员变量，是私有的，类外没法访问，只能构造友元函数，也是导致为啥在上面用引用： void Display(const Date& d) 
	return 0;

}