#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<string>
#include<assert.h>
using namespace std;

//打印
void PrintArr(int* a, size_t n)
{
	for (size_t i = 0; i < n; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}


//直接插入排序
void InsertSort(int a[], size_t n)
{
	for (size_t index = 0; index < n; index++)
	{
		int tmp = a[index];
		int end = index - 1;
		while (end != -1)
		{
			if (a[end]>tmp)              //這里的>和<可以控制是升序还是降序
			{
				a[end + 1] = a[end];       //后移
			}
			else
			{
				break;
			}
			end--;
		}
		a[end + 1] = tmp;
	}
}


//选择排序（每次选一个数字）升序（选择排序）
void SelectSort(int a[], size_t n)
{
	size_t end = 0;
	for (; end < n - 1; end++)
	{
		size_t i = end + 1;
		int min = a[i];
		int minindex = i;
		for (; i < n; i++)
		{
			if (a[i] < min)
			{
				min = a[i];
				minindex = i;
			}
		}
		swap(a[end], a[minindex]);
	}
}
//选择排序（每次选择两个数字，最大和最小）        //当最小的数在0号下标，最大的数在数组最后的时候同时选择两个数就会出现问题
void SelectSortD(int a[], size_t n)
{
	int i = 0;
	int j = 0;
	for (; i < n - j; i++, j++)
	{
		int begin = i;
		int end = n - j - 1;
		int min = begin;
		int max = end;
		while (begin != end + 1)        //刚开始忘了+1
		{
			if (a[begin] < a[min])
			{
				min = begin;
			}
			begin++;
		}
		begin = i;
		while (end != begin + 1)        
		{
			if (a[end]>a[max])
			{
				max = end;
			}
			end--;
		}
		end = n - j - 1;
		swap(a[begin], a[min]);
		swap(a[end], a[max]);
	}
}
//选择排序—堆排

void Adjustdown(int root,size_t n,int a[])     //root当前下标
{
	int parent = root;
	int child = parent * 2 + 1;            //左孩子
	while (child < n)
	{
		if (child != n - 1 && a[child] < a[child + 1])       //选择大的那个孩子      這里的条件判断很容易出错
		{
			child++;   
		}
		if (a[parent] < a[child])
		{
			swap(a[parent], a[child]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
			break;              //注意這里如果我不写這个break  程序死循环了
	}
}
void HeapSort(int arr[],size_t n)
{
	assert(arr);
	//先建大堆
	for (int i = (n - 2) / 2; i >= 0; i--)      //注意這里是(n-2)/2   不是(n-1)/2 刚开始写错了
	{
		Adjustdown(i, n, arr);
	}
	//利用堆顶最大的数据排序
	for (size_t i = 1; i < n; i++)
	{
		swap(arr[0], arr[n - i]);
		Adjustdown(0, n - i, arr);
	}
}

//交换排序—冒泡排序  时间复杂度是o（N^2）
void BubbleSort(int* a,size_t n)
{
	for (int end = n - 1; end>0; end--)
	{
		bool exchange = false;
		size_t first = 0;
		size_t second = first + 1;
		while (second != (end + 1))
		{
			if (a[first] > a[second])
			{
				swap(a[first],a[second]);
				exchange = true;
			}
			++first;
			++second;
			if (exchange == false)
			{
				cout << "没有发生交换" << endl;
			}
		}
	}
}

//交换排序—快速排序（快排）（递归）   
//左右指针法
int PartSort(int* a, int begin, int end)
{
	int key = end;
	while (begin != end)
	{
		while (begin < end && a[begin] <= a[key])     //這里的问题之一就是如果出现相等的数，如果条件写错那么就会出现死循环
		{
			begin++;
		}
		while (begin < end && a[end] >= a[key])
		{
			end--;
		}
		if (begin < end)
		swap(a[begin], a[end]);
	}
	swap(a[begin], a[key]);
	return begin ;
}
//挖坑法    (写错了)
int WKPartSort(int* a, int begin, int end)
{
	int key = a[end];
	while (begin != end)
	{
		while (begin < end && a[begin] <= a[end])
		{
			begin++;
		}
		a[end] = a[begin];
		while (begin<end && a[end] > key)
		{
			end--;
		}
		a[end] = a[begin];   
	}
	a[begin] = key;      //begin和end相会的地方绝对是一个坑，然后把key值填充进去就行
	return begin;
}

//前后指针法   

void QuickSort(int* a, int begin, int end)
{
	assert(a);
	if (begin < end)
	{
		//int prev = PartSort(a, begin, end);
		int prev = WKPartSort(a, begin, end);
		QuickSort(a, begin, prev-1);
		QuickSort(a, prev + 1, end);
	}
	else
      return;
}

int main()
{
	//int arr[] = { 2, 5, 4, 9, 3, 6, 1, 8, 7, 0 };
	int arr[] = { 1, 9, 6, 4, 0, 5, 7, 8, 2, 3 };
	//int arr[] = { 0, 3, 6, 4, 1, 5, 7, 8, 2, 9 };
	//string arr[] = { "hahah", "hehe", "huhuhu", "jajxi", "hsu" };
	//int arr[] = { 3, 1, 4, 2 };                                      //针对于有很多循环的可以用小一点的数组测试
	PrintArr(arr, sizeof(arr) / sizeof(arr[0]));
	//InsertSort(arr, sizeof(arr) / sizeof(arr[0]));
	//SelectSortD(arr, sizeof(arr) / sizeof(arr[0]));
	//HeapSort(arr, sizeof(arr) / sizeof(arr[0]));
	//BubbleSort(arr, sizeof(arr) / sizeof(arr[0]));
	QuickSort(arr, 0, sizeof(arr) / sizeof(arr[0]) - 1);
	PrintArr(arr, sizeof(arr) / sizeof(arr[0]));
	return 0;
}

