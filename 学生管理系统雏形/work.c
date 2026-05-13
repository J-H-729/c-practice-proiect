#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

typedef struct 
{
    long long id;                 // 学生学号
    char name[50];          // 学生姓名
    char date[20];          // 入学日期
   char college[100];     // 学院
    char description[200];  // 班级
    int contact[50];       // 联系方式
    char ioclass[20];        //是否就业
} Student;


void addItem() 
{
    Student item;
    system("cls");
    printf("\n**添加学生信息**\n");

    // 自动生成ID
    item.id = getNextId();

    printf("学生姓名: ");
    scanf("%s", &item.name);

    printf("入学日期(YYYY-MM-DD): ");
    scanf("%s", &item.date);

    printf("所属学院: ");
    scanf("%s", &item.college);

    printf("班级: ");
    scanf("%s", &item.description);

    printf("联系方式: ");
    scanf("%s", &item.contact);

    strcpy(item.ioclass, "未就业");
    
    // 写入文件
    FILE* fp = fopen("data.txt", "ab");
    if (fp == NULL) 
    {
        printf("文件打开失败!\n");
        return;
    }
    fwrite(&item, sizeof(Student), 1, fp);
    fclose(fp);
    printf("\n添加成功! ID为: %d\n", item.id);
}



void listAllItems() 
{
    system("cls");
    printf("\n=== 学生信息目录 ===\n");

    FILE* fp = fopen("data.txt", "rb");
    if (fp == NULL) 
    {
        printf("没有学生!\n");
        return;
    }

    printf("%-5s %-15s %-12s %-15s %-30s %-15s %-10s\n",
        "ID", "学生姓名", "入学日期", "学院", "班级", "联系方式", "是否就业");

    Student item;
    while (fread(&item, sizeof(Student), 1, fp))
    {
        printf("%-5lld%-15s %-12s %-15s %-30s %-15s %-10s\n",
            item.id, item.name, item.date, item.college,
            item.description, item.contact, item.ioclass);
    }
    fclose(fp);
}


void searchByName() 
{
    char name[50];
    int found = 0;

    system("cls");
    printf("\n=== 按学生姓名查找 ===\n");
    printf("请输入学生姓名: ");
    scanf("%s", name);

    FILE* fp = fopen("data.txt", "rb");
    if (fp == NULL)
    {
        printf("没有学生!\n");
        return;
    }

    Student item;
    printf("\n查找结果:\n");
    printf("%-5s%-15s %-12s %-15s %-30s %-15s %-10s\n",
        "ID", "学生姓名", "入学日期", "学院", "班级", "联系方式", "是否就业");

    while (fread(&item, sizeof(Student), 1, fp)) 
    {
        if (strstr(item.name, name) != NULL)
        {
            printf("%-5d %-15s %-12s %-15s %-30s %-15s %-10s\n",
                item.id, item.name, item.date, item.college,
                item.description, item.contact, item.ioclass);
            found = 1;
        }
    }

    if (!found) 
    {
        printf("未找到该学生!\n");
    }
    fclose(fp);
}


void searchByDate() 
{
    char date[20];
    int found = 0;

    system("cls");
    printf("\n=== 按入学日期查找 ===\n");
    printf("请输入入学日期(YYYY-MM-DD): ");
    scanf("%s", date);

    FILE* fp = fopen("data.txt", "rb");
    if (fp == NULL) {
        printf("没有学生!\n");
        return;
    }

    Student item;
    printf("\n查找结果:\n");
    printf("%-5s%-15s %-12s %-15s %-30s %-15s %-10s\n",
        "ID", "学生姓名", "入学日期", "学院", "班级", "联系方式", "是否就业");

    while (fread(&item, sizeof(Student), 1, fp)) {
        if (strcmp(item.date, date) == 0) {
            printf("%-5d %-15s %-12s %-15s %-30s %-15s %-10s\n",
                item.id, item.name, item.date, item.college,
                item.description, item.contact, item.ioclass);
            found = 1;
        }
    }

    if (!found) 
    {
        printf("该日期没有学生记录!\n");
    }
    fclose(fp);
}


void deleteItem()
{
    int id, found = 0;

    system("cls");
    printf("\n=== 删除学生信息 ===\n");
    printf("请输入要删除的学生ID: ");
    scanf("%d", &id);

    FILE* fp = fopen("data.txt", "rb");
    if (fp == NULL) 
    {
        printf("没有学生!\n");
        return;
    }

    FILE* temp = fopen("temp.txt", "wb");
    Student item;

    while (fread(&item, sizeof(Student), 1, fp))
    {
        if (item.id == id) {
            found = 1;
            continue; // 跳过要删除的记录
        }
        fwrite(&item, sizeof(Student), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    if (found)
    {
        remove("data.txt");
        rename("temp.txt", "data.txt");
        printf("删除成功!\n");
    }
    else
    {
        remove("temp.txt");
        printf("未找到该ID的学生!\n");
    }
}


void modifyItem() 
{
    int id, found = 0;

    system("cls");
    printf("\n=== 修改学生信息 ===\n");
    printf("请输入要修改的学生ID: ");
    scanf("%d", &id);

    FILE* fp = fopen("data.txt", "rb+");
    if (fp == NULL)
    {
        printf("没有学生!\n");
        return;
    }

    Student item;
    long pos = 0;

    while (fread(&item, sizeof(Student), 1, fp)) 
    {
        if (item.id == id) 
        {
            found = 1;
            pos = ftell(fp) - sizeof(Student);
            break;
        }
    }

    if (found) 
    {
        printf("\n当前信息:\n");
        printf("学生姓名: %s\n", item.name);
        printf("入学日期: %s\n", item.date);
        printf("学院: %s\n", item.college);
        printf("班级: %s\n", item.description);
        printf("联系方式: %s\n", item.contact);
        printf("是否就业: %s\n", item.ioclass);

        printf("\n请输入新信息:\n");
        printf("学生姓名: ");
        scanf("%s", &item.name);

        printf("入学日期(YYYY-MM-DD): ");
        scanf("%s", &item.date);

        printf("学院: ");
        scanf("%s", &item.college);

        printf("班级: ");
        scanf("%s", &item.description);

        printf("联系方式: ");
        scanf("%s", &item.contact);

        printf("状态(未就业/已就业): ");
        scanf("%s", &item.ioclass);

        fseek(fp, pos, SEEK_SET);
        fwrite(&item, sizeof(Student), 1, fp);
        printf("\n修改成功!\n");
    }
    else 
    {
        printf("未找到该ID的学生!\n");
    }

    fclose(fp);
}


void showStatistics() 
{
    int total = 0, found = 0, notFound = 0;

    system("cls");
    printf("\n=== 统计信息 ===\n");

    FILE* fp = fopen("data.txt", "rb");
    if (fp == NULL)
    {
        printf("没有学生!\n");
        return;
    }

    Student item;
    while (fread(&item, sizeof(Student), 1, fp)) 
    {
        total++;
        if (strcmp(item.ioclass, "已就业") == 0) 
        {
            found++;
        }
        else 
        {
            notFound++;
        }
    }
    fclose(fp);

    printf("总学生数: %d\n", total);
    printf("已就业学生数: %d\n", found);
    printf("未就业学生数: %d\n", notFound);
    printf("就业率: %.2f%%\n", total > 0 ? (float)found / total * 100 : 0);
}


// 获取下一个ID
 int getNextId()
{
    FILE* fp = fopen("data.txt", "rb");
    if (fp == NULL)
    {
        return 1LL; // 文件不存在时从初始ID开始，long long类型
    }

    // 获取文件大小
    fseek(fp, 0, SEEK_END);
    long fileSize = ftell(fp);

    // 检查1：文件大小是否为结构大小的整数倍，以防止文件损坏
    if (fileSize % sizeof(Student) != 0) {
        fclose(fp);
        return 1LL;
    }

    // 检查2：空文件
    if (fileSize == 0)
    {
        fclose(fp);
        return 1LL;
    }

    // 计算记录数
    int records = fileSize / sizeof(Student);
    if (records == 0)
    {
        fclose(fp);
        return 1LL;
    }

    // 检查3：定位到最后一条记录是否成功
    if (fseek(fp, (records - 1) * sizeof(Student), SEEK_SET) != 0) {
        fclose(fp);
        return 1LL;
    }

    Student lastItem;
    // 检查4：读取最后一条记录是否成功
    if (fread(&lastItem, sizeof(Student), 1, fp) != 1)
    {
        fclose(fp);
        return 1LL;
    }

    fclose(fp);
    return lastItem.id + 1;
}


// 备份数据
void backupData() 
{
    FILE* src = fopen("data.txt", "rb");
    FILE* dest = fopen("databackup.txt", "wb");

    if (src == NULL || dest == NULL) return;

    Student item;
    while (fread(&item, sizeof(Student), 1, src))
    {
        fwrite(&item, sizeof(Student), 1, dest);
    }

    fclose(src);
    fclose(dest);
}


int main() 
{
    int choice;

    // 程序启动时自动备份
    backupData();
  /*  system("color 70");*/
    while (1) {
        system("cls");
        printf("\n=== 学生信息管理系统 ===\n");
        printf("1. 添加学生信息(输入1)\n");
        printf("2. 查看所有学生信息(输入2)\n");
        printf("3. 按学生姓名查找(输入3)\n");
        printf("4. 按入学日期查找(输入4)\n");
        printf("5. 删除学生信息(输入5)\n");
        printf("6. 修改学生信息(输入6)\n");
        printf("7. 统计学生信息(输入7)\n");
        printf("8. 退出系统(输入8)\n");
        printf("请选择功能: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: addItem(); break;
        case 2: listAllItems(); break;
        case 3: searchByName(); break;
        case 4: searchByDate(); break;
        case 5: deleteItem(); break;
        case 6: modifyItem(); break;
        case 7: showStatistics(); break;
        case 8:
            printf("\n谢谢使用，再见!\n");
            exit(0);
        default:
            printf("无效选择，请重新输入!\n");
        }

        printf("\n按任意键继续...");
        getch();
    }

    return 0;
}