
//   类型萃取
struct TrueType
{
	bool get()
	{
		return true;
	}
};

struct FalseType
{
	bool get()
	{
		return false;
	}
};

//----------------------------------------------------------------
template<class T>
struct TypeTarits
{
	typedef FalseType IspodType;    //无关紧要的类型
};

template<>
struct TypeTarits<int>
{
	typedef TrueType IspodType;
};

template<>
struct TypeTarits<char>
{
	typedef TrueType IspodType;
};

template<>
struct TypeTarits<float>
{
	typedef TrueType IspodType;
};

template<class T>
struct TypeTarits<T*>
{
	typedef TrueType IspodType;
};