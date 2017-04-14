#define _CRT_SECURE_NO_WARNINGS 1
//复数类  运算符重载
#include<iostream>
using namespace std;

class Complex
{
	friend ostream& operator<<(ostream& out, Complex& c);
	friend istream& operator<<(istream& in, Complex& c);
private:
	int _real;
	int _image;
public:
	Complex(int real = 1, int image = 1)
		:_real(real), _image(image)
	{
	}
	Complex(Complex& d)
		:_real(d._real), _image(d._image)
	{
	}
	Complex operator+(Complex& c)
	{
		Complex tmp;
		tmp._real = _real + c._real;
		tmp._image = _image + c._image;
		return tmp;
	}
	Complex& operator=(Complex& c)
	{
		_real = c._real;
		_image = c._image;
		return *this;
	}
	Complex& operator++()   //前置++
	{
		_real++;
		_image++;
		return *this;
	}
	Complex operator++(int)  //后置++
	{
		Complex tmp(*this);
		_real++;
		_image++;
		return tmp;
	}
	~Complex()
	{
	}
	void Display()
	{
		cout << _real << "+" << _image << "j" << endl;
	}
};
ostream& operator<<(ostream& out, Complex& c)
{
	out << c._real << "+" << c._image << "j" << endl;
	return out;
}
istream& operator>>(istream& in, Complex& c)
{ 
	in >> c._real;
	in >> c._image;
	return in;
}
int main()
{
	Complex c1(1, 1);
	Complex c2 = c1;
	Complex c3 = c2 + c1;
	Complex c4;
	Complex c5;
	Complex c6;
	c4 = c3;
	c3++;
	c5 = ++c4;
	c1.Display();
	c2.Display();
	c3.Display();
	c4.Display();
	c5.Display();
	cout << c5 << endl;
	cout >> c6;
	return 0;
}