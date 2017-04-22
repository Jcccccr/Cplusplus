//  目前我所理解的类和对象——  在类的内部有默认成员函数  而這些成员函数其实都是为对象服务
//构造是为了初始化对象  拷贝构造是为了用已有对象初始化新对象  赋值运算符重载是为了一个对象给另一个对象赋值  析构是为了给对象清理空间
// 我们可以在类内部自定义成员函数（接口）供对象调用从而改变成员变量（這里面当然涉及到很多的语法啊注意事项）  
//将成员变量和成员函数封装在一起，元素和方法封装在一起，用這个图纸实例化对象  当然可以实例化无数的对象   每个对象都具有相同的特征（属性）  都可以进行同样的动作和操作
//他们的数据也许不尽相同    每个人都有不同的地方   這就是我目前理解的面向对象  我们的重点并不在于方法如何做到  对象显得更加重要


//那么对于目前的写时拷贝问题  我也有了自己的一些理解，比如说string类  在std::string中 這个东西有很多操作  他很复杂 我们在模拟实现這个类的时候需要些
//构造拷贝构造赋值运算符重载等等， 结合上面  這些成员函数都是为了对象服务  不同的就是服务的方法和途径  在STL中的string的成员函数实际上都是使用的深拷贝
//每个对象（假如成员变量里面存在指针的话）指向的内容都是属于自己的  每次拷贝构造  赋值  都会自己开空间 仅仅自己来管理 就是深拷贝
//而浅拷贝呢？  這个东西是在我们模拟实现string类的一种方法 比如说两个对象 要赋值或者一个拷贝构造另一个 直接让两个对象的指针指向同一个对象而自己不开辟空间
//当然了 这是我们在自己写這些构造啊拷贝构造啊函数的时候的做法  （Linux环境的string类使用的是引用计数的浅拷贝） 這样做自然会出现重复析构的问题  
//于是乎就需要方法来解决   就有了引用计数  偷懒一次记一次   析构的时候看着引用计数析构 ，這样能很好的解决重复析构的问题  
//但是也不仅仅是析构的问题  当我有一个对象想要改变指针指向的内容的时候  另外的对象也会被改变（偷懒需要付出代价）  
//于是乎  我们发现 不能这么做  偷懒需要适当   当我们需要改变一个指针指向的内容的时候 如果這个对象指向的对象没其他对象指向它  那么就是放心大胆改 如果不是這样
//为了不影响其他的对象   还是老老实实自己重开一块空间 放好数据  要改自己改   当然了 這里面肯定是需要引用计数的配合 不然析构就会出现问题
//引用计数+写时拷贝的浅拷贝相比于深拷贝确实是可以提高效率并且节约空间，但是也付出了相应的代价——实现的时候很容易出错  所以像我這种比较马虎的人，
//还是老老实实用深拷贝按部就班，以免出错，引用计数+写时拷贝  在适当的时候用一下装逼就行了 
//下面我写一下C++实现顺序表  也算是对C++最基础部分的总结练习  当然，在顺序表里面的拷贝构造赋值啊什么的成员函数我用的都是深拷贝，主要在于对c++实现顺序表的一个
//框架的认知，对比C和C++实现顺序表的不同


#include<iostream>
#include<assert.h>
using namespace std;
typedef int DataType;
class SeqList
{
private:
	DataType* _str;
	size_t _size;
	size_t _capacity;
public:
	SeqList()
		:_str(NULL)
		, _size(0)
		, _capacity(0)
	{
	}
	SeqList(SeqList& s)       //拷贝构造
	{
		if (s._str)
		{
			_str = new DataType[s._capacity];
			memcpy(_str, s._str, sizeof(DataType)*s._size);
			_size = s._size;
			_capacity = s._capacity;
		}
	}
	SeqList& operator=(SeqList& s)                    //总是忘记返回值
	{
		if (this != &s)
		{
			if (s._str)
			{
				if (_str)
				{
					free(_str);
					_size = 0;
					_capacity = 0;
				}
				_str = new DataType[s._capacity];
				memcpy(_str, s._str, sizeof(DataType)*s._size);
				_size = s._size;
				_capacity = s._capacity;
			}
			else
				_str = NULL;
		}
		return *this;
	}
	void Checkcapacity()
	{
		if (_size == _capacity)
		{
			_capacity = _capacity * 2 + 2;
			_str = (DataType*)realloc(_str,sizeof(DataType)*_capacity);   //注意malloc的里面放的是啥  与new有什么区别
		}
	
	}
	void PushBack(DataType d)
	{
		Checkcapacity();
		_str[_size] = d;
		_size++;
	}
	void PopBack()
	{
		_size--;
	}
	size_t Find(DataType d)
	{
		size_t i = 0;
		for (i = 0; i < _size; i++)
		{
			if (_str[i] == d)
				return i;
		}
		return 0;
	}
	void Print()
	{
		size_t i = 0;
		for (i = 0; i < _size; i++)
		{
			cout << _str[i] << " ";
		}
		cout << endl;
	}
	~SeqList()
	{
		if (_str)
		{
			free(_str);
			_str = NULL;
		}
	}


};
void test()
{
	SeqList s1;
	s1.PushBack(1);
	s1.PushBack(2);
	s1.PushBack(3);
	s1.PushBack(4);
	s1.PushBack(5);
	s1.PopBack();
	s1.Print();
	SeqList s2(s1);
	s2.PushBack(1);
	s2.PushBack(2);
	s2.PushBack(3);
	s2.PushBack(4);
	s2.PushBack(5);
	s2.Print();
	s1 = s2;
	s1.Print();
	cout << s1.Find(3)<<endl;
}
