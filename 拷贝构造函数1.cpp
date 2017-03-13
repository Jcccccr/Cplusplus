#include<iostream>
using namespace std;
class Complex
{
private:
	double _real;
	double _image;
public:
	Complex(double real = 0.0, double image = 0.0)
	{
		cout << "Complex()" << endl;
		real = _real;
		image = _image;
	}
	Complex& operator=(Complex& c)//使用Complex的返回值类型而不使用void类型是因为void不能实现连等
	{
		cout << "赋值运算符重载" << endl;
		if (this != &c)//這里的if是在做什么？检测自己是否给自己赋值了
		{
			this->_real = c._real;
			_image = c._image;
		}
		return *this;
	}

	~Complex()
	{
		cout << "~Complex()" << endl;
	}
	void Display()
	{
		cout << _real << "+" << _image << "i" << endl;
	}
};
int main()
{
	Complex c1(1.0, 1.0);
	Complex c2(2.0, 2.0);
	c2 = c1;
	c2.Display();
	return 0;
}