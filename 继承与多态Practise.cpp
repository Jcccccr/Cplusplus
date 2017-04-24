#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<string>
using namespace std;
//class Dad                      //父类名 
//{
//protected:
//	string name;
//public:
//	Dad()
//	{
//		cout << "构造函数" << endl;
//		name = "JUXIN";
//	}
//	void Display()
//	{
//		cout << name << endl;
//	}
//
//};
//
//class Son :public Dad               //子类名
//{
//private:
//	int num;                 
//public:
//	void Display()
//	{
//		cout << num << endl;
//		cout << name << endl;
//	}
//
//};
//int main()
//{
//	Son s1;                  //继承关系中  子类内父类的成员会被继承下来  当我实例化一个子类对象的时候实际上调用了父类的构造函数
//	s1.Display();                 //也就是说 我实例化子类对象相当于我先实例化子类对象里面父类的成员 再初始化子类的成员
//}

//存在的疑问是  我上面都是单个对象  单个父类对象和单个子类对象 
//假如是多个呢  怎么继承   子类在实例化的时候只会继承父类的默认值吗？

class Student
{
protected:
	string _name;
public:
	Student(string name="hh")                               //缺省的构造函数  方便子类的对象在构造的时候自动调用
		:_name(name)            //這里调用了string类的构造函数          
	{
		cout << "父类构造" << endl;
	}
	void Display()
	{
		cout << _name << endl;
	}

};
class person:Student
{
private:
	int _num;
public:
	person(int num=10)
		:_num(num)
	{
		cout << "子类构造" << endl;
	}
	void Display()
	{
		cout << _num << endl;
		cout << _name << endl;
	}

};
int main()
{
	Student s1("xiaohong");
	Student s2(s1);
	s1.Display();
	s2.Display();
	person p1;            //当我在实例化一个person对象的时候 要调用p1的构造函数  而在person的构造函数内部又会调用父类的构造函数
	p1.Display();               //而且父类的构造函数肯定是带默认值的  不然没法构造 编译器报错说没有合适的构造函数
	return 0;
}