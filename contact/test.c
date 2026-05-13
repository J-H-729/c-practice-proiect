#define _CRT_SECURE_NO_WARNINGS

#include"contact.h"
void munu()
{
	printf("*********************************************************\n");
	printf("*********       1.add               2.del     ***********\n");
	printf("*********       3.search            4.sort    ***********\n");
	printf("*********       5.show              6.modify  ***********\n");
	printf("*********       0.exit                        ***********\n");
	printf("*********************************************************\n");

}
enum Option
{
	EXIT,
	ADD,
	DEL,
	SEARCH,
	SORT,
	SHOW,
	MODIFY,

};
int main()
{
	int input = 0;
	Contact con;
	IntiContact(&con);
	do
	{
	
		munu();
		printf("请输入选项\n");
		scanf("%d", &input);
		switch (input)
		{
		case ADD:
			AddContact(&con);
			system("cls");
			break;
		case DEL:
			DeleteContact(&con);
			break;
		case SEARCH:
			SearchContact(&con);
			break;
		case SORT:
			SortContact(&con);
			break;
		case SHOW:
			ShowContact(&con);
			break;
		case MODIFY:
			ModifyContact(&con);
			break;
		case EXIT:
			SaveContact(&con);
			DestroyContact(& con);
			printf("已成功退出\n");
			break;
		default:
			printf("请输入正确的选项\n");
			break;

		}


	} while (input);
	return 0;
}