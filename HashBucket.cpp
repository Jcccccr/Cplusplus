#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<string>
#include<vector>
#include<assert.h>
using namespace std;


//哈希桶   （哈希表 拉链法解决哈希冲突）
//桶结点里面不需要状态，想一想原因，桶也是旨在解决哈希冲突,但是最主要的在于插入的方式相去甚远

template<class K,class V>
struct HashNode
{
	pair<K, V> _kv;
	HashNode<K, V>* _next;
	HashNode(const pair<K,V>& kv)
		:_kv(kv) 
		,_next(NULL)
	{
		cout << "构造哈希结点" << endl;
	}
};

//注意這下面的申明
template<class K, class V>
class HashBucket;

//迭代器[*]
template<class K, class V>
struct HashBucketIterator
{
	typedef HashNode<K, V> Node;
	typedef HashBucketIterator<K, V>  Iterator;
	//注意下面
	Node* _node;
	HashBucket<K, V>* _Hash;         //注意這里为什么要传进来一个哈希桶对象指针，有什么用？可不可以传一个对象上去，不传指针，也可以但是浪费空间
	//构造;
	HashBucketIterator(Node* node,HashBucket<K,V>* Hash)
		:_node(node)
		, _Hash(Hash)
	{
	}
	//拷贝构造
	HashBucketIterator(const Iterator& it)
	{
		_node = it._node;
		_Hash = it._Hash;
	}
	K& operator*()
	{
		return _node->_kv.first;
	}
	K* operator->()
	{
		return &_node->_kv.first;
	}
	//[*]
	Iterator& operator++()
	{
		size_t Nowindex = _node->_kv.first % _Hash->_hash.size();      //這里实际上是在类外访问了类内数据，需要定义友元
		if (_node->_next)
		{
			_node = _node->_next;
		}
		else    //回到数组让下标往后跳
		{
			Nowindex++;
			while (Nowindex < _Hash->_hash.size() && _Hash->_hash[Nowindex] == NULL)
			{
				Nowindex++;
				if (Nowindex == _Hash->_hash.size())      //判断已经到达最后。
				{
					_node = NULL;
					return *this;
				}
			}
			_node = _Hash->_hash[Nowindex];
		}
		return *this;                               
	}
	//Iterator& operator--()     //如果链表设计成双向，迭代器--可以实现
	//{
	//	;
	//}
	bool operator==(const Iterator& it)
	{
		return (_node == it._node) && (_Hash == it._Hash);
	}
	bool operator!=(const Iterator& it)
	{
		return _node != it._node;
	}
	
};

template<class K ,class V>
class HashBucket
{
	typedef HashNode<K, V> Node;
	friend struct HashBucketIterator<K, V>;            //注意這里定义友元的目的，因为這个迭代器有些特殊，所以刚开始就一直编不过
public:
	typedef HashBucketIterator<K, V>  Iterator;        
private:
	vector<Node*> _hash;
	size_t _n;
public:
	HashBucket()                                        //默认的构造
		:_n(0)
	{
	}
	bool Insert(const pair<K, V>& kv)         //哈希桶的键值冗余是什么情况
	{
		_CheckCapacity();
		size_t index = _HashFunc(kv.first, _hash.size());
		Node* prev = _hash[index];
		while (prev)                       //防止键值冗余
		{
			if (prev->_kv.first == kv.first)
			{
				return false;
			}
			prev = prev->_next;
		}

		Node* tmp = new Node(kv);
		Node* cur = _hash[index];
		_hash[index] = tmp;
		tmp->_next = cur;

		_n++;
	}
	Node* Find(const K& key)                         //查找是如何体现出高效的
	{
		size_t index = _HashFunc(key, _hash.size());
		Node* cur = _hash[index];
		while (cur)
		{
			if (cur->_kv.first == key)
			{
				return cur;
			}
			cur = cur->_next;
		}
		return NULL;
	}

	bool Remove(const K& key)     //思考位什么這里的Remove不能使用上面的Find确定位置？
	{
		size_t index = _HashFunc(key, _hash.size());
		Node* prev = NULL;
		Node* cur = _hash[index];
		while (cur)
		{
			if (cur->_kv.first == key)
			{
				if (prev == NULL)           //如果删头结点
				{
					_hash[index] = cur->_next;
				}
				else                       //删中间结点或者尾结点
				{
					prev->_next = cur->_next;
				}
				delete cur;
				_n--;
				return true;
			}
			prev = cur;
			cur = cur->_next;
		}
		return false;
	}

	void Resize(const size_t& size)                      //思考为什么需要這个？？ 从效率上考虑這个很有必要
	{
		_hash.resize(GetNextPrimeSize(size));
	}

	size_t HashSize()
	{
		return _hash.size();
	}
	size_t HashNum()
	{
		return _n;
	}

	//迭代器部分
	Iterator Begin()
	{
		for (size_t i = 0; i < _hash.size(); i++)
		{
			if (_hash[i] != NULL)
			{
				Iterator itbegin(_hash[i],this);      //注意這个传this  刚开始我怎么都想不到在类的内部怎么把自己传上去 
				return itbegin;
			}
		}

		return Iterator(NULL, this);
	}
	Iterator End()
	{
		Iterator itend(NULL, this);
		return itend;
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
		for (int i = 0; i < _PrimeSize; i++)
		{
			if (_PrimeList[i]>size)
			{
				return _PrimeList[i];
			}
		}
		return _PrimeList[_PrimeSize - 1];        
	}
	//计算下标
	size_t _HashFunc(const K& key, size_t size)  
	{
		return key % size;
	}
	void _CheckCapacity()                            //增容
	{
		if (_hash.empty())
		{
			_hash.resize(GetNextPrimeSize(0));
		}

		if (_hash.size() == _n)                          //哈希桶的载荷因子是可以控制到1的，但是我觉的很奇怪，实际上我超过1也是可以的。载荷因子和效率到底是怎样的关系
		{
		    size_t newSize = GetNextPrimeSize(_hash.size());
			HashBucket<K, V> newBucket;                //创建新表
			newBucket._hash.resize(newSize);
			for (size_t i = 0; i < _hash.size(); i++)   //遍历原表 ,怎么遍历原表的，怎么把原表换到新表的？ 每一次增容都要重新布置位置，比较麻烦但是却必须！
			{
				Node* cur = _hash[i];
				while (cur)
				{
					Node* next = cur->_next;   //先做保留
					//获取到所有的结点然后头插新表，不创建新结点
					size_t index = _HashFunc(cur->_kv.first, newBucket._hash.size());
					cur->_next = newBucket._hash[i];
					newBucket._hash[i] = cur;
					//原桶中下一个结点
					cur = next;
				}
				_hash[i] = NULL;                   //這里一定要置空，不然在析构原表的时候就会出现问题
			}
			_hash.swap(newBucket._hash);             //问题：這里的数组调用swap会把原来的vector析构掉吗？  问题。
		}
	}
};

//迭代器使用
template<class K,class V>
void PrintHashBucket(HashBucket<K,V>& Hb)
{
	HashBucket<K, V>::Iterator it = Hb.Begin();
	while (it != Hb.End())
	{
		cout << *it <<" ";
		++it;
	}
	cout << endl;
}


//-------------------------------测试-----------------------
void test()
{
	HashBucket<int, int> Hb1;
	//insert
	Hb1.Insert(make_pair(rand(), 3));
	Hb1.Insert(make_pair(rand(), 3));
	Hb1.Insert(make_pair(rand(), 3));
	Hb1.Insert(make_pair(rand(), 3));
	Hb1.Insert(make_pair(rand(), 3));
	Hb1.Insert(make_pair(rand(), 3));
	Hb1.Insert(make_pair(rand(), 3));
	Hb1.Insert(make_pair(rand(), 3));
	Hb1.Insert(make_pair(rand(), 3));
	Hb1.Insert(make_pair(rand(), 3));
	Hb1.Insert(make_pair(rand(), 3));
	Hb1.Insert(make_pair(rand(), 3));
	Hb1.Insert(make_pair(rand(), 3));
	Hb1.Insert(make_pair(rand(), 3));
	Hb1.Insert(make_pair(rand(), 3));
	Hb1.Insert(make_pair(rand(), 3));
	Hb1.Insert(make_pair(rand(), 3));
	Hb1.Insert(make_pair(rand(), 3));
	Hb1.Insert(make_pair(rand(), 4));
	Hb1.Insert(make_pair(rand(), 4));
	Hb1.Insert(make_pair(rand(), 4));
	Hb1.Insert(make_pair(rand(), 4));
	Hb1.Insert(make_pair(rand(), 4));
	Hb1.Insert(make_pair(rand(), 4));

	//find
	cout << Hb1.Find(1124) << endl;
	cout << Hb1.Find(11942) << endl;
	cout << Hb1.Find(491) << endl;
	cout << Hb1.Find(67) << endl;
	cout << Hb1.Find(89) << endl;
	cout << Hb1.Find(52) << endl;
	//remove
	cout<<Hb1.Remove(11942)<<endl;
	cout << Hb1.Remove(491) << endl;
	//resize                                   //实际上這里的resize是存在的问题的，如果resie不是在最刚开始的时候使用，那么单纯的扩容而并没有将数据在哈希表中重新布局。
	Hb1.Resize(100000);
	cout << Hb1.HashSize() << endl;
	Hb1.Resize(200000);
	cout << Hb1.HashSize() << endl;


	HashBucket<int, int> Hb2;
	Hb2.Insert(make_pair(rand(), 3));
	Hb2.Insert(make_pair(rand(), 3));
	Hb2.Insert(make_pair(rand(), 3));
	Hb2.Insert(make_pair(rand(), 3));
	Hb2.Insert(make_pair(rand(), 3));
	Hb2.Insert(make_pair(rand(), 3));
	Hb2.Insert(make_pair(rand(), 3));
	Hb2.Insert(make_pair(rand(), 3));
	Hb2.Insert(make_pair(rand(), 3));
	//Hb2.Insert(make_pair(rand(), 3));
	//Hb2.Insert(make_pair(rand(), 3));
	//Hb2.Insert(make_pair(rand(), 3));
	//Hb2.Insert(make_pair(rand(), 3));
	//Hb2.Insert(make_pair(rand(), 3));
	//Hb2.Insert(make_pair(rand(), 3));
	//Hb2.Insert(make_pair(rand(), 3));
	//Hb2.Insert(make_pair(rand(), 3));
	//Hb2.Insert(make_pair(rand(), 3));
	//Hb2.Insert(make_pair(rand(), 3));

	//迭代器测试
	//PrintHashBucket(Hb1);              //因为resize的原因，這里就存在很大的问题
	PrintHashBucket(Hb2);
}
int main()
{
	test();
	return 0;
}