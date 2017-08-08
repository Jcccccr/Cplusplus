#define _CRT_SECURE_NO_WARNINGS 1


#include<stdio.h>
#include<assert.h>
#include<math.h>

#define EXP  0.0000001                                 //另外一个注意点是在比较double的变量的时候宏定义精度比较，绝对不能使用d1==d2;這样

//模拟C库函数中的pow函数，实现求base的exponent次方的值
double MyPower(double base, int exponent)
{

	double result = 1.0;
	//错误检测
	if (base<EXP && base>-EXP && exponent < 0)      //这道题的坑在于如果说底数为0 的时候指数小于0的时候 报错！
	{
		printf("0为底数不可以是负数次方\n");
		return 0.0;
	}
	if (exponent == 0)
		return result;
	if (exponent > 0)      //指数为正
	{
		int i = 0;
		for (; i < exponent; i++)
		{
			result *= base;
		}
		return result;
	}
	else                 //指数为负，结果取倒数
	{
		int i = 0;
		for (; i < -exponent; i++)
		{
			result *= base;
		}
		return 1.0 / result;
	}
}


//************************测试用例************************
void test(void)
{
	double result = 1.0;
	//result = MyPower(3, 4);
	//result = MyPower(-1, 4);
	//result = MyPower(-2, -3);
	//result = MyPower(-2, 0);
	result = MyPower(0, -4);
	printf("%lf\n", result);
}
int main()
{
	test();
	return 0;
}