#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<assert.h>
using namespace std;

class Parent
{
private:
	int _age;
	int _name;
public:
	Parent()
		:_age(0)
		, _name(0)
	{
		cout << "parent" << endl;
	}
};

class Student :public Parent
{ 
private:
	int _num;
public:
	Student()
		:_num(1)
	{
		cout << "Student" << endl;
	}
};
int main()
{	Parent p;
	Student s;
	return 0;
}