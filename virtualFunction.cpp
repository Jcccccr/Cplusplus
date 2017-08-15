#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;

//解决菱形继承的二义性和数据冗余  ：虚拟继承

class A
{
public:                     //注意必须是public访问限定，不然在菱形派生类中无法访问该成员
	string _name;
};
class B: virtual public A
{
protected:
	int _num;
};
class C :virtual public A
{
protected:
	int _age;
};
class D :public B, public C
{
protected:
	string _majority;
};
int main()
{
	D dd;
	A* pa = &dd;
	B* pb = &dd;
	C* pc = &dd;
	D* pd = &dd;
	return 0;
}