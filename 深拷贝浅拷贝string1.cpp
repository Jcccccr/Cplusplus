//#include<iostream>
//using namespace std;
//class Array
//{private:
//	int _sz;
//	int *_ptr;
//public:
//	Array(int sz=4)
//		 :_sz(sz)
//		 ,_ptr(new int [_sz])//开辟动态空间;
//	{
//		cout << "Array()" << endl;
//	}//构造的主要目的就是给_ptr开辟空间；
//	Array(const Array& arr)
//	{
//		_ptr = arr._ptr;
//		_sz = arr._sz;
//	}//這个是手打的拷贝构造过程，是系统默认调用的拷贝构造函数，浅拷贝；
//	~Array()
//	{
//		cout << "~Array()" << endl;
//		if (_ptr != NULL)
//		{
//			delete[] _ptr;
//		}
//
//	}
//};
//int main()
//{
//	Array arr1;
//	Array arr2(arr1); 
//    system("pause");
//	return 0;
//} 


////以上是一个浅拷贝，运行会卡住；
//



#include<iostream>
using namespace std;
class Array
{
private:
	int _sz;
	int *_ptr;
public:
	Array(int sz = 4)
		:_sz(sz)
		, _ptr(new int[_sz])//开辟动态空间;
	{
		cout << "Array()" << endl;
	}//构造的主要目的就是给_ptr开辟空间；
	
	Array(const Array& arr)
		:_sz( arr._sz)
		, _ptr(new int[_sz]) //目前這里是拷贝可相同大小的空间（是arr2自己的），但是内容没有拷贝；
	
	{
		cout << "Array(const Array& arr)" << endl;
		memcpy(_ptr, arr._ptr, _sz*sizeof(int));//這里拷贝arr1那个数组里面的内容；
	}
	
	~Array()
	{
		cout << "~Array()" << endl;
		if (_ptr != NULL)
		{
			delete[] _ptr;
		}

	}
};
int main()
{
	Array arr1;
	Array arr2(arr1);
	system("pause");
	return 0;
} 