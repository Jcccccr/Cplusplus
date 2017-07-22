#define _CRT_SECURE_NO_WARNINGS 1

//二叉树的层序遍历
//利用队列
#include<iostream>
#include<queue>
#include<string>
#include<assert.h>
using namespace std;

//层序遍历
void LevelOrder()
{
	assert(_root);
	Node* cur = _root;
	queue<Node*> _q;
	_q.push(cur);
	while (!_q.empty())
	{
		if (cur->_left)
			_q.push(cur->_left);
		if (cur->_right)
			_q.push(cur->_right);
		cout << _q.front()->_data << " ";
		_q.pop();
		if (!_q.empty())             //注意這里为什么有判断   因为最后一次pop  会让队列为空，一个空的队列取front( )引发错误！！！记住了
			cur = _q.front();
	}
}
int main()
{
	return 0;
}