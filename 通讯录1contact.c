#define _CRT_SECURE_NO_WARNINGS 1

#include"contact.h"
// 初始化函数
void init_contact(contact* n)         //初始化con 把数量和数组全部初始化为0
{   
	int i = 0;
	n->num = 0;
	memset(n->contact, 0, sizeof(people)*MAX);

}

//增加联系人
void add_contact(contact* n)
{
	if (n->num >= MAX)
	{
		printf("电话本已满");
		return;
	}

		printf("请输入姓名：");
		scanf("%s", n->contact[n->num].name);
		printf("请输入年龄：");
		scanf("%5d", &(n->contact[n->num].age));
		printf("请输入性别：");
		scanf("%s", n->contact[n->num].sex);
		printf("请输入住址：");
		scanf("%s", n->contact[n->num].addr);
		printf("请输入电话：");
		scanf("%s", n->contact[n->num].tele);
	n->num++;
	printf("添加成功\n");
}

//定位函数
static int find_contact(contact* n,  char name[])
{  
	int i = 0;
	for (i = 0; i < n->num; i++)
	{
		if (strcmp(name, n->contact[i].name) == 0)
			return i;
	}
	return -1;

}

//删除联系人
void dele_contact(contact* n)
{   
	char name[MAX_NAME] = {0};
	int pos;
	int i=0;
	if (n->num == 0)
	{
		printf("通讯录已为空");
		return;
	}
	printf("请输入要删除人的名字： ");
	scanf("%s", name);
	pos=find_contact(n, name);
	if (pos == -1)
	{
		printf("查无此人\n");
		return;
	}
	for (i = pos; i < n->num-1; i++)
	{
		n->contact[i] = n->contact[i + 1];
	}
	n->num--;
}

//寻找联系人
void srch_contact(contact* n)
{   
	char name[MAX_NAME] = { 0 };
	int pos;
	if (n->num == 0)
	{
		printf("通讯录为空");
		return;
	}
	printf("请输入你要查找的那个人");
	scanf("%s", name);
	pos = find_contact(n, name);
	if (pos == -1)
	{
		printf("查无此人");
		return;
	}
	printf("姓名： %s     年龄：%5d\n性别：%s     住址：%s\n       电话：   %s\n",
		n->contact[pos].name,
		n->contact[pos].age,
		n->contact[pos].sex,
		n->contact[pos].addr,
		n->contact[pos].tele);
}

//修改联系人
void modf_contact(contact* n)
{    
	char name[] = { 0 };
	int pos;
	if (n->num == 0)
	{
		printf("通讯录为空");
		return;
	}
	printf("请输入需要修改的联系人： ");
	scanf("%s", name);
	pos = find_contact(n, name);
	if (pos == -1)
	{
		printf("查无此人");
		return;
	}
	printf("请修改姓名：");
	scanf("%s", n->contact[pos].name);
	printf("请修改年龄：");
	scanf("%5d", &(n->contact[pos].age));
	printf("请修改性别：");
	scanf("%s", n->contact[pos].sex);
	printf("请修改住址：");
	scanf("%s", n->contact[pos].addr);
	printf("请修改电话：");
	scanf("%s", n->contact[pos].tele);

}

//显示联系人
void show_contact(contact* n)
{   
	if (n->num != 0)
	{

		int i = 0;
		printf("*****  联系人  **************\n");
		for (i = 0; i < n->num; i++)
		{
			printf("姓名： %s     年龄：%5d\n性别：%s     住址：%s\n       电话：   %s\n",
				n->contact[i].name,
				n->contact[i].age,
				n->contact[i].sex,
				n->contact[i].addr,
				n->contact[i].tele);
		}
	}
	else
		printf("通讯录为空\n");
}

//清空联系人
void emty_contact(contact* n)
{
	int i = 0;
	n->num = 0;
	memset(n->contact, 0, sizeof(people)*MAX);
	printf("通讯录已清空\n");
}


int cmp_contact(const void *elem1, const void *elem2)       //qsort调用的函数
{
	return strcmp((*(people*)elem1).name, (*(people*)elem2).name);
}

//联系人排序
void sort_contact(contact* n)
{
	int i = 0;
	qsort(n->contact, n->num, 
		 sizeof(people)  ,  cmp_contact);                                    //使用qsort进行排序
	for (i = 0; i < n->num; i++)
	{
		printf("%s\n", n->contact[i].name);
	}
}

