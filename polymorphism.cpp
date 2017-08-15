#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
using namespace std;


class Parent
{
public:
	virtual void func1()
	{
		cout << "P::func1" << endl;
	}
	virtual void func2()
    {
		cout << "P::func2" << endl;
	}
private:
	int _parent;
};
class Student : public Parent
{
public:
	virtual void func1()
	{
		cout << "S::func1" << endl;
	}
	virtual void func2()
	{
		cout << "S::func2" << endl;
	}
private:
	int _student;
};

int main()
{
	Parent p1;
	Student s1;
	Parent* ptr = &p1;
	ptr->func1();
	//Student* str = &s1;
	ptr = &s1;
	ptr->func1();
	//str->funct1();


	return 0;
}