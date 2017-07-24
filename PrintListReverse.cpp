#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
#include<assert.h>
using namespace std;
//面试题6：从尾到头打印链表  

//先创建一个链表 
struct ListNode
{
	int _data;
	ListNode* _next;
};
typedef ListNode Node;
Node* _head = NULL;

//尾插
void PushBack(Node** _pHead, int data)
{
	assert(_pHead);
	if (*_pHead == NULL)
	{
		*_pHead = new Node();
		(*_pHead)->_data = data;
		(*_pHead)->_next = NULL;
	}
	else
	{
		Node* cur = *_pHead;
		while (cur->_next)
		{
			cur = cur->_next;
		}
		Node* newNode = new Node();
		newNode->_data = data;
		newNode->_next = NULL;
		cur->_next = newNode;
	}
}
//题目一:  从尾到头打印单链表
void PrintReverse(Node* _head)
{
	if (_head == NULL)
		return;
	PrintReverse(_head->_next);
	cout << _head->_data << " ";
}


//正常打印
void PrintList(Node** _pHead)
{
	assert(_pHead);
	Node* cur = *_pHead;
	while (cur)
	{
		cout << cur->_data << " ";
		cur = cur->_next;
	}
	cout << endl;
}
void test(void)
{
	PushBack(&_head, 1);
	PushBack(&_head, 2);
	PushBack(&_head, 3);
	PushBack(&_head, 4);
	PushBack(&_head, 5);
	PrintList(&_head);
	PrintReverse(_head);
}
int main()
{
	test();
	return 0;
}
