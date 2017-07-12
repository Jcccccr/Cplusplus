#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<assert.h>
#include<string>
using namespace std;

//链表结构实现一个队列  实现基本的队列的相关擦操作
//无头单链表
template<class T>
struct QueueNode
{
	T  _data;
	QueueNode<T>* _next;
	QueueNode(const T& data)
		:_data(data)
		, _next(NULL)
	{
	}
};
template<class T>
class MyQueue
{
	typedef QueueNode<T>  Node;
protected:
	Node* _head;
public:
	MyQueue()
		:_head(NULL)
	{
		cout << "构造队列结构" << endl;
	}
	void Push(const T& data)        //队尾插入
	{
		if (_head == NULL)
		{
			_head = new Node(data);
		}
		else
		{
			Node* cur = _head;
			while (cur->_next)
			{
				cur=cur->_next
			}
			Node* newNode = new Node(data);
			cur->_next = newNode;
		}
	}
	void Pop()         //队头删除   
	{
		if (_head == NULL)    //没有元素
		{
			printf("链表为空\n");
			return;
		}
		if (_head->_next == NULL)    //有一个元素
			_head = NULL;
		else                        //多个元素
		{
			Node* tmp = _head;
			Node* next = _head->_next;
			_head = next;
			delete tmp;
		}
		return;
	}
	T& Front()
	{
		if (_head == NULL)    //没有元素
		{
			printf("链表为空\n");
			return;
		}
		else
		{
			return _head->_data;
		}
	}
};


void TestQueue()
{
}
int main()
{
	TestQueue();
	return 0;
}