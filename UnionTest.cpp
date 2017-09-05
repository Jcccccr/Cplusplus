#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<stdio.h>
using namespace std;
   
typedef union haha
{
   char a[5];
   int b;
}haha;

int main()
{
	cout << sizeof(haha) << endl;
	return 0;
}