#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<assert.h>
#include<string>
#include<vector>
using namespace std;

//堆的运用，实际上堆是一种算法一种思想，我们在模拟堆的时候把他想象成一种容器了，实质上只是数组而已，只是在vector基础之上加入了向上调整算法和向下调整算法，這样的话我们可以
//运用這个堆起来的数组解决一些排序的问题


//1.   N个数里面求前K个最大的数  （如果N非常大，都排序一遍时间复杂度太大，而且很可能内存放不下，這里就需要使用到堆）
//     使用小堆


//void AdjustDown(int root, size_t n, int a[])          //向下调整为小堆      //问题：我刚开始的时候是把這个函数放在TopFromK()里面的  但是就会出现问题 为什么？
//{                                                  //我觉的我犯了一个低级错误，一个函数的内部怎么可以声明另一个函数，只能各自声明定义
//	int parent = root;
//	int child = parent * 2 + 1;
//	while (child<n)
//	{
//		if (child != n - 1 && a[child + 1] <a[child])
//		{
//			child++;
//		}
//
//		if (a[child]<a[parent])
//		{
//			swap(a[parent], a[child]);
//			parent = child;
//			child = child * 2 + 1;
//		}
//		else
//		{
//			break;
//		}
//	}
//}
//void TopKformN()
//{
//	const size_t N = 100000;
//	const size_t K = 10;
//	int a[N] = { 0 };
//	for (size_t i = 0; i < N; i++)
//	{
//		a[i] = rand() % N;
//	}
//	int heap[K] = { 0 };
//	for (size_t i = 0; i < K; i++)
//	{
//		heap[i] = a[i];
//	}
//
//	for (int i = (K - 2) / 2; i >= 0; i--)
//	{
//		AdjustDown(heap[(K - 2) / 2], K, heap);
//	}
//
//
//	for (size_t i = K + 1; i < N; i++)                       //這里一个一个去比
//	{                                                     //如果后面的数遇到比根结点大的，就和根结点替换，替换结束后从根结点向下调整
//		if (a[i]>heap[0])
//		{
//			heap[0] = a[i];
//			AdjustDown(heap[0], K, heap);
//		}
//	}
//	for (int i = 0; i < K; i++)
//	{
//		cout << heap[i] << " ";
//	}
//
//
//}
//int main()
//{
//	TopKformN();
//	return 0;
//}




//2.  大堆实现升序    （小堆实现升序时间复杂度大，效率低）
//3.  小堆实现降序    
//以下为升序排序 ，  降序排序只要将向下调整函数稍作更改就行

void AdjustDown(int root, size_t n, int* a)                       //注意這里的root是下标             
{                                                 
	int parent = root;
	int child = parent * 2 + 1;
	while (child<n)
	{
		if (child != n - 1 && a[child + 1] >a[child])
		{
			child++;
		}

		if (a[child]>a[parent])
		{
			swap(a[parent], a[child]);
			parent = child;
			child = child * 2 + 1;
		}
		else
		{
			break;
		}
	}
}


//排序函数
void HeapSort(int* a,size_t n)                 
{
    //建堆
	for (int i = (n - 2) / 2; i >= 0; i--)
	{
		AdjustDown(i, n, a);
	}
	//排序：   将堆顶数据（最大值）放至数组最后，n减1，向下调整 循环往复
	for (int i = 1; i < n;i++)
	{
	    swap(a[n - i], a[0]);
		AdjustDown(0, n - i , a);
	}
	
}

void test()
{
	int a[] = { 10, 11, 13, 12, 16, 18, 15, 17, 14, 19 };
	HeapSort(a,sizeof(a)/sizeof(a[0]));
	int i = 0;
	for (i = 0; i < sizeof(a) / sizeof(a[0]); i++)
	{
		cout << a[i] << " ";
	}
}
int main()
{
	test();
	return 0;
}