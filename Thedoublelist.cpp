#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
struct ListNode
{
	DateType _data;
	ListNode* _next;
	ListNode* _prev;

	ListNode(const DataType x)
		:_data(x)
		, _next(NULL)
		, _prev(NULL)
	{}
}; 

class List
{
	typedef ListNode Node;
public:
	List()
		:_head(NULL)
		, _tail(NULL)



};