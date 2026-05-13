#define ROW 3
#define COL 3

// 初始化棋盘
void Initbroad(char broad[ROW][COL], int row, int col);
// 显示棋盘
void Display(char broad [ROW][COL],int row,int col);
// 玩家落子
void player(char broad[ROW][COL], int row, int col);
// 电脑落子
void computer(char broad[ROW][COL], int row, int col);
// 判断胜负
char iswin(char broad[ROW][COL], int row, int col);
