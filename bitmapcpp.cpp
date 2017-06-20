#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<vector>
#include<string>
#include<errno.h>
#include<assert.h>
using namespace std;


//位运算存在问题,按位或按位与存在问题
class bitmap
{
private:
	vector<char>  _bimp;
public:
	bitmap()
		:_bimp(NULL)
	{
		cout << "构造位图" << endl;
	}
	void InitBitmap(const size_t& size)
	{
		_bimp.resize(size / 8 + 1, 0);         //传入的要放进去的数的个数，注意這里为什么要+1
	}
	bool Create(const size_t& num)                //构建位图
	{
		size_t index = num / 8;
		size_t pos = num % 8;
		_bimp[index] |= (1 << pos);           //任何数和1或都为任何数
		return true;
	}
	bool Reset(const size_t& num)
	{
		size_t index = num / 8;
		size_t pos = num % 8;
		_bimp[index] &= (~(1 << pos));
		return true;

	}
	bool Find(const size_t& num)
	{
		size_t index = num / 8;
		size_t pos = num % 8;
		if (_bimp[index] & (1 << pos))
		{
			return true;
		}
		else
			return false;
	}
};

//----------------------test-----------------------
void testBitmap()
{
	bitmap _bp;
	_bp.InitBitmap(-1);
	_bp.Create(3);
	_bp.Create(89);
	_bp.Create(56);
	_bp.Create(35);
	_bp.Create(89);
	_bp.Create(44);
	_bp.Create(67);
	_bp.Create(23);
}
int main()
{
	testBitmap();
	return 0;
}