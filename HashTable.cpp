#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<vector>
#include<string>
using namespace std;

//哈希表除留余数法（线性探测）  时间复杂度o(1)        针对于各种数据结构的时间复杂度

enum HashState       //插入数据的状态
{
	EXIST,
	EMPTY,
	DELETE
};

template<class K,class V>
struct HashNode
{
	pair<K, V> _kv;
	HashState _state;
	HashNode(const pair<K ,V>& kv=make_pair(0,0))       //刚开始没有给pair的默认值，在最初的vector构造的时候会调vector对象的默认构造函数，就出错了
		: _kv(kv)
		, _state(EMPTY)
	{
		cout << "构造哈希结点" << endl;
	}
};



//使用仿函数
//针对普通类型
template<class K>
struct  _HashFunc
{
	size_t operator()(const K& key,size_t size)    //這里使用一个size
	{
		return key% size;
	}
};
//针对于string
struct _HashFuncstring  
{
	static size_t BKDRHash(const char* str) 
	{
		unsigned int seed = 131;   // 31 131 1313 13131 131313    
		unsigned int hash= 0;    
		while(*str)    
		{        
			hash=hash*seed+ (*str++);   
		}    
		return(hash& 0x7FFFFFFF); 
	}
	size_t operator()(const string str, size_t size)      //這里是C风格字符串,怎么使用c_str()?
	{
		return BKDRHash(str.c_str()) % size;        //注意這里的c_str（）是将C++风格字符串转换为C风格字符串...是不是這样？
	}
};

template<class K,class V,class _Hashfunctype>
class HashTable
{   
	typedef  HashNode<K, V>  HashNode;
	_Hashfunctype _ht;  
private:
	vector<HashNode> _hash;
	size_t _n;
public:
    HashTable()    //這里让vector调默认的构造
		:_n(0)
	{
	}
	bool Insert(const pair<K,V>& kv)     //插入一个pair对象
	{
		_CheckCapacity();
		int  index = _ht(kv.first,_hash.size());     //寻找下标
		//如果空间有值
		while (_hash[index]._state == EXIST)
		{
			if (kv.first == _hash[index]._kv.first)  //防止数据冗余
			{
				return false;
			}
			++index;                          //注意這里为什么把++index放在下面的判断的上面，index的最大值比size小1。
			if (index == _hash.size())       
			{
				index = 0;
			}
		}
		//如果空间没有值或者被删除了
		_hash[index]._kv = kv;
		_hash[index]._state = EXIST;
		_n++;                                 //_n代表数据的个数
		return true;
	}

	HashNode* Find(const K& key)              //查找
	{
		size_t index = _ht(key,_hash.size());            
		while (_hash[index]._state == EXIST)
		{
			if (_hash[index]._kv.first == key)
			{
				return &_hash[index];
			}
			index++;
		}
		return NULL;
	}

	bool Rmove(const K& key)                //删除
	{
		HashNode* tmp = Find(key);
		if (tmp)
		{
			tmp->_state = DELETE;           //实际上不是真正的删除，只是赋予這个数组单元的数据可以被覆盖的权利
			return true;
		}
		else
		{
			return false;
		}
	}

protected:
	rsize_t GetNextPrimeSize(size_t size)               //素数表
	{
		const  int _PrimeSize = 28;
		static const unsigned long _PrimeList[_PrimeSize] = {
			53ul, 97ul, 193ul, 389ul, 769ul,
			1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
			49157ul, 98317ul, 196613ul, 393241ul, 786433ul,
			1572869ul, 3145739ul, 6291469ul, 12582917ul, 25165843ul,
			50331653ul, 100663319ul, 201326611ul, 402653189ul, 805306457ul,
			1610612741ul, 3221225473ul, 4294967291ul
		};
		for (int  i = 0; i < _PrimeSize; i++)
		{
			if (_PrimeList[i]>size)
			{
				return _PrimeList[i];
			}
		}
		return _PrimeList[_PrimeSize - 1];        //以防万一如果值超过了最大，就返回最后那个最大的素数
	}

	//size_t _HashFunc(const K& key)            //求映射出的下标
	//{
	//	return  key % _hash.size();        //除留余数法：除数组的长度，這样就尽量让数据都散开。载荷因子就降低，哈希表的效率就会越高。
	//}

	void _CheckCapacity()
	{
		if (_hash.empty())     //针对于刚开始的时候
		{
			_hash.resize(GetNextPrimeSize(0));
		}
		if (_n * 10 / _hash.size() <= 7)     
		{
			return;
		}
		else               //载荷因子>0.7 开始增容
		{
			HashTable<K, V,_Hashfunctype> newHash;                             //注意這里增容的方式
			size_t newSize = GetNextPrimeSize(_hash.size());
			newHash._hash.resize(newSize);
			for (size_t i = 0; i < _hash.size(); i++)
			{
				if (_hash[i]._state == EXIST)
				{
					int index = _ht(_hash[i]._kv.first ,newHash._hash.size());   
					newHash._hash[index]._kv = _hash[i]._kv;
					newHash._hash[index]._state = EXIST;
				}
			}
			newHash._n = _n;
			_hash.swap(newHash._hash);        //调用vector的swap进行交换
		}
	}
};


void test()
{
	/*HashTable<int, int,_HashFunc<int>> Hasht1;
	Hasht1.Insert(make_pair(7, 1));
	Hasht1.Insert(make_pair(72, 1));
	Hasht1.Insert(make_pair(71, 1));
	Hasht1.Insert(make_pair(34, 1));
	Hasht1.Insert(make_pair(5, 1));
	Hasht1.Insert(make_pair(66, 1));
	cout<<Hasht1.Find(34)<<endl;*/

	HashTable<string, string, _HashFuncstring> Hasht2;
	Hasht2.Insert(make_pair("left", "左边"));
	//Hasht2.Insert(make_pair(string("right"), string("右边")));
	//Hasht2.Insert(make_pair(string("upside"), string("上边")));
	//Hasht2.Insert(make_pair(string("down"), string("下边")));
	//Hasht2.Insert(make_pair(string("inside"), string("里边")));
}
int main()
{
	test();
	return 0;
}