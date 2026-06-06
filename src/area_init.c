
#include "../include/_include.h"
// 使用渐变风格！
static void init_border(int x_start, int y_start, int area_width, int area_height)
{
    // 上
    for (int x = x_start, y = y_start; x < area_width + x_start; x++)
    {
        gotoxy(x, y);
        printf("%c", (x == x_start) ? '+' : '-');
        // Sleep(2);
    }
    // 右
    for (int x = x_start + area_width - 1, y = y_start; y < area_height + y_start; y++)
    {
        gotoxy(x, y);
        printf("%c", (y == y_start) ? '+' : '|');
        // Sleep(2);
    }

    // 下1
    for (int x = x_start + area_width - 1, y = y_start + area_height - 1 - 7; x > x_start; x--)
    {
        gotoxy(x, y);
        printf("%c", (x == x_start + area_width - 1) ? '+' : '-');
        // Sleep(2);
    }

    // 下2
    for (int x = x_start + area_width - 1, y = y_start + area_height - 1; x > x_start; x--)
    {
        gotoxy(x, y);
        printf("%c", (x == x_start + area_width - 1) ? '+' : '-');
        // Sleep(2);
    }
    // 左
    for (int x = x_start, y = y_start + area_height - 1; y > y_start; y--)
    {
        gotoxy(x, y);
        printf("%c", (y == y_start + area_height - 1) ? '+' : '|');
        // Sleep(2);
    }
}

// 初始化游戏区域（只在开始时绘制一次）
void init_game_area()
{
    init_border(BORDER_X_START, BORDER_Y_START, AREA_WIDTH, AREA_HEIGHT);
}