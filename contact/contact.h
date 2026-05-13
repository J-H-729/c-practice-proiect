#pragma once
#define MAX 100
#define MAX_NAME 20
#define MAX_SEX 10
#define MAX_TELE 20
#define INC_SZ 2
#define MAX_ADDR 30
#define DEFAULT_SZ 3
#include<stdio.h>
#include<errno.h>
#include<assert.h>
#include<string.h>
#include<stdlib.h>
typedef struct iniopeo
{
	char name[MAX_NAME];
	int age;
	char sex[MAX_SEX];
	char tele[MAX_TELE];
	char addr[MAX_ADDR];
}iniopeo;

//静态
//typedef struct Contate
//{
//  iniopeo data[100];
//	int count;
//}Contact;

//动态
typedef struct Contate
{
	iniopeo *data;
	int count;
	int capacity;
}Contact;

//	初始化
int IntiContact(Contact* pc);

//添加通讯录
void AddContact(Contact* pc);

//显示通讯录
void ShowContact(Contact* pc);

//删除通讯录
void DeleteContact(Contact* pc);

//查找通讯录
void SearchContact(Contact* pc);

//修改通讯录
void ModifyContact(Contact* pc);

//排序通讯录
void SortContact(Contact* pc);

//销毁通讯录
void DestroyContact(Contact* pc);

//保存通讯录
void SaveContact(const Contact* pc);

//加载通讯录
void  LoadContact(Contact* pc);

//扩容
void CheckCapacity(Contact* pc);