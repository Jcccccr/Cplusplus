#include<iostream>
#include<vector>
using namespace std;
long GetInterval(vector<int>& _v)
{
	if (_v.size() == 0)
		return 0;
	long size = _v.size();
	long count = 0;
	size_t i = 0;
	while (i < size)
	{
		bool IsInter = false;
		if (i == 0 && _v[i] != 0)
		{
			i++;
			continue;
		}
		if (i == 0 && _v[i] == 0)
		{
			i++;
			count++;
			continue;
		}
		if (_v[i] == 0)
		{
			i++;
			count++;
			continue;
		} 
		while (i&&_v[i - 1] == _v[i] && i < size)
		{
			i++;
			IsInter = true;
		}
		if (IsInter)
		{
			count++;
			continue;
		}
		i++;
	}
	return count;
}
int main()
{
	vector<int> _arr;
	long num;
	long n;
	while (cin >> n)
	{
	     
	}
	cout << GetInterval(arr) << endl;
}