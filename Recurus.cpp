#define _CRT_SECURE_NO_WARNINGS 1

//void foo(int arr[],int a,int b,int* out1,int* out2)
//{
//	if (b - a <= 1)
//	{
//		if (arr[a] < arr[b])
//		{
//			*out1 = arr[b];
//			*out2 = arr[a];
//		}
//		else
//		{
//			*out1 = arr[a];
//			*out2 = arr[b];
//		}
//		return;
//	}
//	int l1, l2, r1, r2;
//	foo(arr, a, a + (b - a) / 2, &l1, &l2);
//	foo(arr, a + (b - a) / 2 + 1, b, &r1, &r2);
//	if (l1 > r1)
//		*out1 = l1;
//	else
//		*out1 = r1;
//	if (l2<r2)
//		*out2 = l2;
//	else
//		*out2 = r2;
//}

//int func(int N)
//{
//	int max = N;
//	for (int i = 1; i <= N - 1; i++)
//	{
//		int s = i*func(N - i);
//		if (s > max)
//			max = s;
//	}
//	return max;
//}
//int g(unsigned int  x)
//{
//	unsigned int a = 1;
//	unsigned int b = (x >> 5) + 8;
//	if (b > 65535)
//		b = 65535;
//	while (b >= a)
//	{
//		unsigned int m = (a + b) >> 1;
//		if (m*m > x)
//			b = m - 1;
//		else
//			a = m + 1;
//	}
//	return a - 1;
//}
//int foo(int nums[], int size, int k)
//{
//	if (k == 0)
//		return 0;
//	int s = 0;
//	for (int j = 0; j < k; ++j)
//	{
//		s += nums[j];
//	}
//	int s2 = s;
//	for (int i = 1; i < size - k + 1; ++i)
//	{
//		s -= nums[i - 1];
//		s += nums[i + k - 1];
//		a2 = max(s, s2);
//	}
//	return s2 / k;
//}

#include<iostream>
#include<string>
using namespace std;
string func(string s1, string s2)
{
	string s = (s1.length() > s2.length()) ? s1 : s2;
	size_t k1 = s1.length(), k2 = s2.length(), k = s.length();
	unsigned int a = 0, b, c;
	while (k1 > 0 || k2 > 0)
	{
		b = ((k1 > 0) ? s1[k1 - 1] - '0' : 0);
		c = ((k2 > 0) ? s2[k2 - 1] - '0' : 0);
		s[k - 1] = '0' + b^c^a;
		a = (b&c) | (a&(b | c));
		if (k1 > 0)
			--k1;
		if (k2 > 0)
			--k2;
		if (k > 0)
			--k;
	}
	if (a)
		s = "1" + s;
	return s;
}

int main()
{
	/*int a, b;
	int arr[] = { 2, 3, 413, 3, -7, -8, -9, 8, 9, 3123, 131 };
	foo(arr, 0, sizeof(arr) / sizeof(int)-1, &a, &b);
	printf("%d", a);*/
	//printf("%d", func(8));

	//printf("%d", g(2000017));
	string s = func("0001101001101100", "1001010100010010");
	printf("%s", s.c_str());
	return 0;
}