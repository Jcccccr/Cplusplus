#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<assert.h>
#include<string>
#include<vector>
using namespace std;

bool _GetMagic(string s, int sum, int tmp)
{
	if (tmp == s.size())
		return !sum;
	if (_GetMagic(s, sum - (s[tmp] - '0'), tmp + 1) == false)
	{
		return _GetMagic(s, sum, tmp + 1);
	}
	return true;
}
long long GetSeriousNum(int x)
{
	int Sum = 0;
	string s = to_string(x);
	for (auto c : s)
	{
		Sum += c - '0';
	}
	if (Sum % 2 == 0)
		return _GetMagic(s, Sum / 2, 0);
}
int main()
{
	long long left = 0;
	long long right = 0;
	long long Count = 0;
	for (long long num = left; num <= right; num++)
	{
		if (GetSeriousNum(num))
			Count++;
	}
	cout << Count << endl;
	return 0;
}