#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<assert.h>
using  namespace std;

//重建二叉树
//主要思想是将问题提留在当前的情况下，按顺序遍历前序遍历的数组用来确定当前的跟结点，然后中序遍历辅助确定左子树和右子树。
//要注意的是条件的判断，什么时候返回，什么时候递归左子树什么时候递归右子树？

typedef struct TreeNode
{
	int _data;
	TreeNode* _left;
	TreeNode* _right;
}Node;

Node* ConstructTree(int* PrevHead, int* PrevTail, int* InorderHead, int* InorderTail)
{
	//创建结点
	int value = PrevHead[0];
	Node* root = new Node();
	root->_data = value;
	root->_left = NULL;
	root->_right = NULL;
	//返回条件
	if (PrevHead == PrevTail&&InorderHead == InorderTail)
	{
		if (*PrevHead != *InorderHead)              //这个判断的目的就是在锁定最后一个叶子结点的时候发现两个不相等，那么這个数组输入一定是有问题的 要报错返回。
		{
			cout << " INPUT  ERROR" << endl;
			return NULL;
		}
		return root;
	}
	//在中序遍历数组中找当前的跟结点的左边有没有数了，如果说左边有那么就有左子树，求左边的数据的长度。
	int leftlength = 0;
	int* cur = InorderHead;
	while (*cur != value)
	{
		leftlength++;
		cur++;
	}
	int* PrevEnd = PrevHead + leftlength;
	//递归子问题
	if (leftlength > 0)           //递归左边
	{
		root->_left = ConstructTree(PrevHead + 1, PrevEnd, \
			InorderHead, InorderHead + leftlength - 1);
	}
	if (leftlength < PrevTail - PrevHead)    //递归右边
	{
		root->_right = ConstructTree(PrevEnd + 1, PrevTail, \
			InorderHead + leftlength + 1, InorderTail);
	}
	//左右子树都建立完毕之后范围root
	return root;
}

Node* ReCreateBinaryT(int* PrevHead, int* InOrderHead, size_t length)
{
	assert(PrevHead);
	assert(InOrderHead);
	assert(length);
	return ConstructTree(PrevHead, PrevHead + length - 1,\
		             InOrderHead, InOrderHead + length - 1);
}

//****************测试**************************
void test()
{
	int arr1[] = { 1, 2, 4, 7, 3, 5, 6, 8 };
	int arr2[] = { 4, 7, 2, 1, 5, 3, 8, 6 };
	size_t length = sizeof(arr1) / sizeof(arr1[0]);
	Node* root = ReCreateBinaryT(arr1, arr2, length);
}
int main()
{
	test();
	return 0;
}