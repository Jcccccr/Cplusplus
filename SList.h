//  单向链表
#ifndef __SLIST_H__
#define __SLIST_H__

#endif //__SLIST_H__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

typedef int DataType;

typedef struct Node
{
	DataType data;
	struct Node* next;

}Node,*pNode ,*pList;

void Init_slist(pList* pplist);
pNode BuyNode(DataType d);
void PushBack(pList* pplist, DataType d);           //看起来貌似每次都需要传头指针为参数 貌似于功能无关  但是要知道只有知道了头指针
void PopBack(pList* pplist);
void PushFront(pList* pplist, DataType d);
void PopFront(pList* pplist);
void Print(pList plist);                          //我们才能找到后面所有的节点进行操作
void Getslistlength(pList plist);
pNode Find(pList plist,DataType d);
void Remove(pList* pplist, DataType d);
void RemoveAll(pList* pplist,DataType d);
void Insert(pList* pplist, pNode pos, DataType d);     //指定位置插入
void Erase(pList* pplist, pNode pos);                 //指定位置删除    pos 位置
void Destoryslist(pList* pplist);