#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>

void my_swap(char* p1, char* p2,int count)
{
	int i = 0;
	for (i = 0; i < count; i++)
	{
		char tmp = *(p1 + i);                 //注意這里的swap是一个字节一个字节交换的  中间变量的类型为char 一个字节空间
		*(p1 + i) = *(p2 + i);               //也可以写成  p1[i]=p2[i];
		*(p2 + i) = tmp;
	}
}

void bubble_sort(void *base,
	size_t num,                                   //size_t相当于 unsigned int
	size_t width,
	int(*cmp)(const void *elem1, const void *elem2)
	)
{
	unsigned int i = 0;
	unsigned int j = 0;                              //這里定义无符号 是与size_t保持同类型
	for (i = 0; i < num; i++)
	{
		for (j = 0; j < num - i - 1; j++)
		{
			if (cmp((char*)base + j*width, (char*)base + (j + 1)*width)>0)         //通过指针调用cmp_int函数 函数参数分别是第一个和第二个元素首地址
				                                                              //width决定了访问的跨度
				my_swap( (char*)base + j*width, 
				        (char*)base + (j + 1)*width,                             //以字节为单位进行交换
						 width
					   );
		}
	}

}

int cmp_int(const void *elem1, const void *elem2)      
{
	return (*(int*)elem1) - (*((int*)elem2));                    //由于是数组  强制类型转换整形指针访问四个字节来比较两个元素的大小  
}  

int main()
{    
	int arr[] = { 3, 2, 1, 4, 5, 6, 7, 8, 9, 10 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	int i = 0;
	bubble_sort(arr, sz, sizeof(int), cmp_int);
	for (i = 0; i < sz; i++)
	{
		printf("%d ", arr[i]);
	}
    return 0;
}