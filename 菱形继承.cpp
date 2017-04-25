#define _CRT_SECURE_NO_WARNINGS 1


//#include <iostream>
//using namespace std;
//
//class A
//{
//public:
//	int _a;
//};
//
//class B : A
//{
//public:
//	int _b;
//};
//
//
// // public is-a
// // private has-a
//int main()
//{
//	A aa;
//	aa._a = 1;
//	B bb;
//	//bb._a = 2;
//	bb._b = 3;
//
//	aa = bb;
//	//A* p = &bb;
//	//A& r = bb;
//	//r._a = 10;
//
//	return 0;
//}

//
//#include <iostream>
//using namespace std;
//
//int a = 10;
//
//class AA
//{
//public:
//	int f(int a)
//	{
//		cout<<"AA::f()"<<endl;
//		return 0;
//	}
//
//	int a;
//};
//
//class BB : public AA
//{
//public:
//	void f(double a)
//	{
//		cout<<"BB::f()"<<endl;
//	}
//
//	int a;
//	int b;
//};
//
//// 隐藏
//int main()
//{
//	BB bb;
//	bb.a = 10;
//	bb.AA::a = 20;
//
//	bb.f(1);
//	//bb.AA::f(1);
//
//	return 0;
//}

#include <iostream>
#include <string>
using namespace std;
//
//class Person
//{
//public:
//	Person(char* name = "小黑")
//		:_name(name)
//	{
//		cout<<"Person()"<<endl;
//	}
//
//	Person(const Person& p)
//		:_name(p._name)
//	{
//		cout<<"Person(const Person& p)"<<endl;
//	}
//
//	Person& operator=(const Person& p)
//	{
//		cout<<"Person& operator=(const Person& p)"<<endl;
//		if (this != &p)
//		{
//			_name = p._name;
//
//		}
//		return *this;
//	}
//
//	~Person()
//	{
//		cout<<"~Person()"<<endl;
//	}
//
//protected:
//	string _name;
//};
//
//class Student : public Person
//{
//public:
//	Student(char* name, int num)
//		:Person(name)
//		,_num(num)
//	{
//		cout<<"Student()"<<endl;
//	}
//
//	Student(const Student& s)
//		:Person(s)
//		,_num(s._num)
//	{
//		cout<<"Student(const Student& s)"<<endl;
//	}
//
//	Student& operator=(const Student& s)
//	{
//		if (this != &s)
//		{
//			Person::operator=(s);
//			_num = s._num;
//		}
//
//		cout<<"Student& operator=(const Student& s)"<<endl;
//
//		return *this;
//	}
//
//	~Student()
//	{
//		cout<<"~Student()"<<endl;
//		//Person::~Person();
//	}
//
//protected:
//	int _num; // 学号
//};

//class Person
//{
//public:
//string  _name;   //姓名
//};
//
//class Student: virtual public Person
//{
//protected:
//	 int _num;   //学号
// };
//
//class Teacher: virtual public Person
//{
// protected:
//	 int _id;    //职工编号
//};
//
//class Assistant: public Teacher, public Student
//{
//protected:
//   string _majorCourse;    //主修课程
//};
//
//int main()
//{
//	Assistant a;
//	a.Student::_name = "11";
//	a.Teacher::_name = "22";
//
//	return 0;
//}
//

class A
{
public:
	int _a;
};

class B : virtual public A
{
public:
	int _b;
};

class C : virtual public A
{
public:
	int _c;
};

class D : public C, public B
{
public:
	int _d;
};

int main()
{
	D dd;
	cout << sizeof(dd) << endl;

	dd.B::_a = 1;
	dd._b = 3;

	dd.C::_a = 2;
	dd._c = 4;

	dd._d = 5;

	B bb;
	C cc;
	//cout<<sizeof(bb)<<endl;

	//bb = dd; // 切片
	//cc = dd;

	A* pa = &dd;
	B* pb = &dd;
	C* pc = &dd;
	D* pd = &dd;

	A.都相等	  B.pa跟pb相等
		C.pd跟pb相等  D.都不想等

		return 0;
}
