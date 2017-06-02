#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#ifndef  __CONTACT_H__
#define  __CONTACT_H__
#endif // __CONTACT_N__


#define MAX_NAME 10
#define MAX_SEX  10
#define MAX_ADDR 20
#define MAX_TELE 10
#define MAX     1000

typedef struct people
{
	char name[MAX_NAME];
	int age;
	char sex[MAX_SEX];
	char addr[MAX_ADDR];
	char tele[MAX_TELE];
}people;

typedef struct contact
{
	int num;
	people contact[MAX];
}contact;


void init_contact(contact* n);
void add_contact(contact* n);
void dele_contact(contact* n);
void srch_contact(contact* n);
void modf_contact(contact* n);
void show_contact(contact* n);
void emty_contact(contact* n);
void sort_contact(contact* n);



