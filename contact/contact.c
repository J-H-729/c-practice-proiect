#define _CRT_SECURE_NO_WARNINGS
#include"contact.h"
//动态
//void IntiContact(Contact* pc)
//{
//	assert(pc);
//	pc->count = 0;
//	memset(pc->data,0,sizeof(pc->data));
//}

//获取联系人
void LoadContact(Contact* pc)
{
	assert(pc);
	FILE* pfread = fopen("test.txt", "rb");
	if (pfread == NULL)
	{
		perror("LoadContact");
		return;
	}
	iniopeo tmp = { 0 };
	while ((fread(&tmp, sizeof(iniopeo), 1, pfread)) == 1)
	{
		CheckCapacity(pc);
		pc->data[pc->count] = tmp;
		pc->count++;
	}
	fclose(pfread);
	pfread = NULL;
}

//扩容
void CheckCapacity(Contact*pc)
{
	if (pc->count == pc->capacity)
	{
		iniopeo* ptr = (iniopeo*)realloc(pc->data,(pc->capacity + INC_SZ) * sizeof(iniopeo));
		if (ptr == NULL)
		{
			printf("AddContact::%s\n", strerror(errno));
			return;
		}
		else
		{
			pc->data = ptr;
			pc->capacity += INC_SZ;
			printf("扩容成功\n"); 
		}
	}
}
//动态
int IntiContact(Contact* pc)
{
	assert(pc);
	pc->count = 0;
	pc->data=(iniopeo*)calloc(DEFAULT_SZ,sizeof(iniopeo));
	if (pc->data == NULL)
	{
		printf("IntiContact::%s\n", strerror(errno));
		return 1;
	}
	pc->capacity = DEFAULT_SZ;
	//加载文件中的联系人信息到通讯录
	LoadContact(pc);
	return 0;
	
}


//动态
//void AddContact(Contact* pc)
//{
//	assert(pc);
//	if (pc->count == 100)
//	{
//		printf("通讯录已满，无法添加\n");
//		return;
//	}
//	printf("请输入姓名\n");
//	scanf("%s", pc->data[pc->count].name);
//	printf("请输入年龄\n");
//	scanf("%d", &(pc->data[pc->count].age));
//	printf("请输入性别\n");
//	scanf("%s", pc->data[pc->count].sex);
//	printf("请输入电话\n");
//	scanf("%s", pc->data[pc->count].tele);
//	printf("请输入地址\n");
//	scanf("%s", pc->data[pc->count].addr);
//	pc->count++;
//	printf("添加成功\n");
//}


//动态




	void AddContact(Contact * pc)
	{
		assert(pc);
		CheckCapacity(pc);
		printf("请输入姓名\n");
		scanf("%s", pc->data[pc->count].name);
		printf("请输入年龄\n");
		scanf("%d", &(pc->data[pc->count].age));
		printf("请输入性别\n");
		scanf("%s", pc->data[pc->count].sex);
		printf("请输入电话\n");
		scanf("%s", pc->data[pc->count].tele);
		printf("请输入地址\n");
		scanf("%s", pc->data[pc->count].addr);
		pc->count++;
		printf("添加成功\n");
	}


void ShowContact(Contact* pc)
{
	assert(pc);
	int i = 0;
	printf("%20s\t%5s\t%5s\t%12s\n", "姓名", "年龄", "性别", "电话", "地址");
	for (i = 0;i < pc->count;i++)
	{
		printf("%20s\t%5d\t%5s\t%12s\n", pc->data[i].name,
		    pc->data[i].age,
			pc->data[i].sex,
			pc->data[i].tele,
			pc->data[i].addr);
	}
}


void DeleteContact(Contact* pc)
{
	assert(pc);
	int i = 0;
	char name[MAX_NAME] = { 0 };
	if (pc->count == 0)
	{
		printf("通讯录为空，没有可删除的\n");
	}
	printf("请输入要删除的人的姓名\n");
	scanf("%s", name);
	//查找
	int pos=FindContact(pc,name);

	if (pos == -1)
	{
		printf("要删除的人不存在\n");
		return;
	}
	//删除
	for (i = pos;i < pc->count - 1;i++)
	{
		pc->data[i] = pc->data[i + 1];
	}
	pc->count--;
	printf("删除成功\n");
}



//查找通讯录
static int FindContact(Contact* pc, char name[])//static 限制作用域，只能在本文件中使用
{
	assert(pc);
	int i = 0;
	for (i = 0;i < pc->count;i++)
	{
		if (0 == (strcmp(pc->data[i].name, name)))
		{
			return i;
		}
	}
	return -1;
}
 

void SearchContact(Contact* pc)
{
	assert(pc);
	char name[MAX_NAME] = { 0 };
	printf("请输入要查找的人的姓名\n");
	scanf("%s", name);
	int pos = FindContact(pc, name);
	if (pos == -1)
	{
		printf("要查找的人不存在\n");
		return;
	}
	printf("%20s\t%5s\t%5s\t%12s\n", "姓名", "年龄", "性别", "电话", "地址");
		printf("%20s\t%5d\t%5s\t%12s\n", pc->data[pos].name,
			pc->data[pos].age,
			pc->data[pos].sex,
			pc->data[pos].tele,
			pc->data[pos].addr);
}

void ModifyContact(Contact* pc)
{
	assert(pc);
	char name[MAX_NAME] = { 0 };
	printf("请输入要修改的人的姓名\n");
	scanf("%s", name);
	int pos = FindContact(pc, name);
	if (pos == -1)
	{
		printf("要查找的人不存在\n");
		return;
	}
	printf("请输入修改后的姓名\n");
	scanf("%s", pc->data[pos].name);
	printf("请输入修改后的年龄\n");
	scanf("%d", &(pc->data[pos].age));
	printf("请输入修改后的性别\n");
	scanf("%s", pc->data[pos].sex);
	printf("请输入修改后的电话\n");
	scanf("%s", pc->data[pos].tele);
	printf("请输入修改后的地址\n");
	scanf("%s", pc->data[pos].addr);
	printf("修改成功\n");
}


int cmp_peo_name(const void* e1, const void* e2)
{
	return strcmp(((iniopeo*)e1)->name, ((iniopeo*)e2)->name);
}
void SortContact(Contact* pc)
{
	assert(pc);
	qsort(pc->data, pc->count, sizeof(iniopeo), cmp_peo_name);
	printf("排序成功\n");
}


void DestroyContact(Contact* pc)
{
	assert(pc);
	free(pc->data);
	pc->data = NULL;
}


void SaveContact(const Contact* pc)
{
	assert(pc);
	FILE* pfwrite = fopen("test.txt", "wb");
	if (pfwrite == NULL)
	{
		perror("SaveContact");
		return 1;
	}
	int i = 0;
	for (i = 0;i < pc->count;i++)
	{
		fwrite(pc->data + i, sizeof(iniopeo), 1, pfwrite);
	}
	fclose(pfwrite);
	pfwrite = NULL;
}