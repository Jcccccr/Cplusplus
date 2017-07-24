#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<assert.h>
#include<string>
//替换空格最优解： 时间复杂度： o（N） 空间复杂度：o（1）
//前后字符指针大法好
using namespace std;
void ReplaceBlank(char str[], size_t length,int Maxlength)
{
	assert(str);
	assert(length);
	//先求出替换过后的数组的长度
	size_t i = 0;
	size_t count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
			count++;
		i++;
	}
	if (count == 0)
	{
		printf("无须替换\n");
		return;
	}
	size_t newlength = length + count * 2;
	if (newlength > Maxlength)                //字符数组的最大容量空间
		return;
	//定义两个指针一前一后，从后往前开始替换
	int FastIndex =length - 1;
	int SlowIndex= newlength - 1;
	while (FastIndex!= SlowIndex)
	{
		while (str[FastIndex]!=' ')
		{
			str[SlowIndex--] = str[FastIndex--];
		}
		FastIndex--;
		if (SlowIndex - FastIndex >= 3)
		{
			str[SlowIndex--] = '0';
			str[SlowIndex--] = '2';
			str[SlowIndex--] = '%';
		}
		else
		{
			printf("出错\n");
			return;
		}
	}
}

void test(void)
{
	//char string[] = "hello the world";    //我之前不像给个大空间，想着就硬头皮把后面的值覆盖了，后面反正是随机值应该不影响，但是发现這样，功能实现了，但是返回的时候挂掉，说堆栈被破坏
	const int Maxlength = 100;              //后来我乖乖给了大空间，顺利运行。
	char string[Maxlength] = "hello the world";
	size_t length = strlen(string) + 1;
	ReplaceBlank(string, length, Maxlength);	
	size_t i = 0;
	while (string[i] != '\0')
	{
		cout << string[i] << " ";
		i++;
	}
	cout << endl;
}
int main()
{
	test();
	return 0;
}

