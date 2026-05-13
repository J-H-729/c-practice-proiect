#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"game.h"
#include<stdlib.h>
#include<time.h>

void Initbroad(char broad[ROW][COL],int row,int col)
{
    int i = 0;
    int j = 0;
    for (i = 0;i < row;i++)
    {
        for (j = 0;j < col;j++)
        {
            broad[i][j] = ' ';
        }
    }
}


void Display(char broad[ROW][COL], int row, int col)
{
    int i = 0;
    for (i = 0;i < row;i++)
    {
        int j = 0;
        for (j = 0;j < col;j++)
        {
            printf(" %c ", broad[i][j]);
            if (j < col - 1)
                printf("|");
        }
        printf("\n");

        if(i<row-1)
        {
            int j = 0;
            for(j=0;j<col;j++)
            {
                printf("---");
                if (j < col-1 )
                    printf("|");
            }
        }
        printf("\n");
    }
}

void player(char broad[ROW][COL], int row, int col)
{
    int x =0;
    int y = 0;
    while (1)
    {
        printf("请输入坐标");
        scanf("%d %d",&x,&y);
        if (x>0 && x< row+1 && y>0 && y<col+1)
        {
            if (broad[x - 1][y - 1] == ' ')
            {
                broad[x - 1][y - 1] = '*';
                break;
            }
            else
            {
                printf("该位置已被占用，请重新输入\n");
            }
        }
        else
        {
            printf("请输入有效的坐标\n");
        }
    }
}

void computer(char broad[ROW][COL], int row, int col)
{
    int x = 0;
    int y = 0;
    printf("电脑落子\n");
    
    while (1)
    {
        x = rand() % row;
        y = rand() % col;
        if (broad[x][y] == ' ')
        {
            broad[x][y] = '#';
            break;
        }
    }
}

int isFULL(char broad[ROW][COL], int row, int col)
{
    int i=0;
    int j = 0;
    for (i = 0;i < row;i++)
    {
        for (j = 0;j < col;j++)
        {
            if (broad[i][j] == ' ')
            {
                return 0;
            }
        }
    }
    return 1;
}


char iswin(char broad[ROW][COL], int row, int col)
{
    int i = 0;
    for (i = 0;i < row;i++)
    {
        if (broad[i][0] == broad[i][1] && broad[i][1] == broad[i][2] && broad[i][1] != ' ')
            return broad[i][1];
    }
    int j = 0;
    for (j = 0;j < col;j++)
    {
        if (broad[0][j] == broad[1][j] && broad[1][j] == broad[2][j] && broad[1][j] != ' ')
            return broad[1][j];
    }
    if (broad[0][0] == broad[1][1] && broad[1][1] == broad[2][2] && broad[1][1] != ' ')
    {
        return broad[1][1];
    }
    if (broad[0][2] == broad[1][1] && broad[1][1] == broad[2][0] && broad[1][1] != ' ')
    {
        return broad[1][1];
    }
    if (isFULL(broad,row,col))
    {
        return 'Q';//平局
    }
    return 'C';//continue
}
