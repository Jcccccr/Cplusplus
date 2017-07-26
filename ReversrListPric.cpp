#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<string>
#include<assert.h>
using namespace std;

//链表的逆置问题

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

Node* ReverseList(Node** pHead)
{
	assert(pHead);
	if (*pHead == NULL)
	{
		printf("链表为空\n");
		return NULL;
	}
	if ((*pHead)->_next == NULL)
	{
		return *pHead;
	}
	Node* newNode = NULL;
	Node* prev = *pHead;
	Node* cur = (*pHead)->_next;
	newNode = prev;
	prev->_next = NULL;
	while (cur)
	{
		Node* tmp = cur;
		cur = cur->_next;
		tmp->_next = newNode;
		newNode = tmp;
	}
	*pHead = newNode;
}

void PrintList(Node* head)
{
	Node* cur = head;
	while (cur)
	{
		cout << cur->_data << " ";
		cur = cur->_next;
	}
	cout << endl;
}
void test()
{
	PushBack(&_head, 1);
	PushBack(&_head, 2);
	PushBack(&_head, 3);
	PushBack(&_head, 4);
	PushBack(&_head, 5);
	PushBack(&_head, 6);
	PushBack(&_head, 7);
	PrintList(_head);
	ReverseList(&_head);
	PrintList(_head);
}
int main()
{
	test();
	return 0;
}
