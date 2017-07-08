#define _CRT_SECURE_NO_WARNINGS 1

//布隆过滤器基本实现

#include"Bloom.h"

template<class T>
struct _HashFunc1
{
	size_t BKDRHash(const T?*str)
	{
		register size_t hash  = 0;
		while (size_t ch  = (size_t)*str++)
		{
			hash?= hash*131 + ch;
		}
		return hash;
	}
};
struct _HashFunc2
{

};
struct _HashFunc3
{

};
struct _HashFunc4
{

};
struct _HashFunc5
{

};

template<class K,class _HashFunc1 = _HashFunc1,
               class _HashFunc2 = _HashFunc2, 
               class _HashFunc3 = _HashFunc3, 
               class _HashFunc4 = _HashFunc4, 
               class _HashFunc5 = _HashFunc5>
class BloomFilter
{
private:
	bitmap  _bloomf;
public:
	//BloomFilter()       //构造
	//{
	//	cout << "构造布隆" << endl;
	//}
	BloomFilter(const int& size)
		:_bloomf(size)
	{
		cout << "构造" << endl;
	}
	void Setbloom()
	{

	}
	void Resetbloom()
	{

	}
	void Find()
	{
	}
protected:
	size_t HashStr()
	{

	}
};
void  testBloomFilter()
{
    
}
int main()
{
	testBloomFilter();
	return 0;
}