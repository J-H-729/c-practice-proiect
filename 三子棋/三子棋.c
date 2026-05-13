#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"game.h"
#include<stdlib.h>
#include<time.h>

void menu()
{
    printf("*********************************\n");
    printf("*********************************\n");
    printf("*************1. play*************\n");
    printf("*************0. exit*************\n");
    printf("*********************************\n");
    printf("*********************************\n");
}

void game()
{
    int ret = 0;
    char broad[ROW][COL] = { 0 };
    Initbroad(broad, ROW, COL);
    Display(broad, ROW, COL);
    while (1)
    {
        player(broad, ROW, COL);
        ret = iswin(broad, ROW, COL);
        if (ret != 'C')
        {
            break;
        }
        Display(broad, ROW, COL);
        computer(broad,ROW,COL);
        ret=iswin(broad, ROW, COL);
        if (ret != 'C')
        {
            break;
        }
        Display(broad,ROW,COL);
    }
    if (ret == '*')
    {
        printf("玩家胜利\n");
    }
    else if (ret == '#')
    {
        printf("电脑胜利\n");
    }
    else
    {
        printf("平局\n");
    }
    Display(broad, ROW, COL);
}

int main()
{
    srand((unsigned int)time(NULL));
    int input = 0;
    do
    {
        menu();
        printf("请输入选项\n");
        scanf("%d", &input);
        switch (input)
        {
        case 1:
            game();
            break;
        case 0:
            printf("退出游戏\n");
            break;
        default:
            printf("请输入正确选项\n");
            break;
        }
    } while (input);
    return 0;
}
