#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
int DigitSum(int n)
{
	if (n == 0)
		return 0;
	if (n != 0)
		return (n % 10) + DigitSum(n / 10);
}
int main()
{
	int n = 1729;
	printf("%d\n", DigitSum(n));
    return 0;
}