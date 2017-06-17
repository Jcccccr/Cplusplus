#define _CRT_SECURE_NO_WARNINGS 1

//const修饰的变量拥有了常量的性质 ，他的值不能被修改，我们只能初始化
//但是要记住的是 ，在C中 const修饰的变量本质还是变量，而不像C++中被修饰的变量就失去了变量的性质完全是一个常量

/*const int i;   
int const i;*///用const申明常量的方式 两种都可以；


// 重要：const修饰的指针变量

//指针的作用就是指向某个变量 变量里面有值，我们可以通过改变指针而改变指针指向的值，
//那么const在這里就起到了对指针不同方面的限定作用：
//我们要改变指针所指向的内容 有两种方式：1.直接改变指针指向的值，2.改变指针变量里面存放的地址




#include<stdio.h>
int main()
{
	int a = 10;
	int*  p = &a;       
	*p = 20;          //1.  通过改变指向的变量的值
	printf("%d\n", a);
    return 0;
}
//那么我们如果用const修饰這样的指针：
int main()
{
	int a = 10;
	int* const p = &a;       //运行无误，這里的p不能被修改的，但不影响他指向的那个空间
	*p = 20;         
	printf("%d\n", a);
	return 0;
}

int main()
{
	int a = 10;
	int const *p = &a;
	*p = 20;                //报错， 這里const修饰了指针所指向的内容 没法改变
	printf("%d\n", a);
	return 0;
}




int main()
{
	int a = 10;
	int b = 20;
	int*  p = &a;
	p = &b;                //2.  通过改变指针变量里面存放的地址改变指向的内容
	printf("%d\n", *p);
	return 0;
}



int main()
{
	int a = 10;
	int b = 20;
	int* const p = &a;      //报错，p被修饰之后没办法被改变
	p = &b;                //想要给变量p重新赋值来改变   
	printf("%d\n", *p);
	return 0;
}



int main()
{
	int a = 10;
	int b = 20;
	int const*  p = &a;
	p = &b;                //运行无误，指针指向的内容没办法改变，但是我们可以改变p的内容
	printf("%d\n", *p);
	return 0;
}

