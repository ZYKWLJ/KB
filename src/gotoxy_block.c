
#include "../include/_include.h"
// 移动光标到指定位置并画画方块
void drawe_block_blank(int x, int y, char block_char, char key)
{

    gotoxy(x, y);
    printf("%c---%c", block_char, block_char);
    gotoxy(x + 4, y + 1);
    printf("|");
    gotoxy(x + 4, y + 2);
    printf("%c", block_char);
    gotoxy(x + 3, y + 2);
    printf("-");
    gotoxy(x + 2, y + 2);
    printf("-");
    gotoxy(x + 1, y + 2);
    printf("-");
    gotoxy(x, y + 2);
    printf("%c", block_char);
    gotoxy(x, y + 1);
    printf("|");
    gotoxy(x + 2, y + 1);
    printf("%c", key);
}

void drawe_green_blank(int x, int y, char block_char, char key)
{
    printf("%s%s", GREEN, BOLD);
    drawe_block_blank(x, y, block_char, key);
    printf("%s", RESET);
}

void remove_block_blank(int x, int y)
{

    gotoxy(x, y);
    printf("%c   %c", ' ', ' ');
    gotoxy(x + 4, y + 1);
    printf(" ");
    gotoxy(x + 4, y + 2);
    printf("%c", ' ');
    gotoxy(x + 3, y + 2);
    printf(" ");
    gotoxy(x + 2, y + 2);
    printf(" ");
    gotoxy(x + 1, y + 2);
    printf(" ");
    gotoxy(x, y + 2);
    printf("%c", ' ');
    gotoxy(x, y + 1);
    printf(" ");
    gotoxy(x + 2, y + 1);
    printf("%c", ' ');
}

void white_block_by_key(char key, char block_char)
{
    int x = coordinate[key - 'A'][0];
    int y = coordinate[key - 'A'][1];
    drawe_block_blank(x, y, block_char, key);
}

void green_block_by_key(char key, char block_char)
{
    printf("%s%s", GREEN, BOLD);
    white_block_by_key(key, block_char);
    printf("%s", RESET);
}

void red_block_by_key(char key, char block_char)
{
    printf("%s%s", RED, BOLD);
    white_block_by_key(key, block_char);
    printf("%s", RESET);
}

void green_block_then_remove(char key, char block_char)
{
    green_block_by_key(key, block_char);
    Sleep(500);
    remove_block_blank(coordinate[key - 'A'][0], coordinate[key - 'A'][1]);
}
void green_block_Xms_then_remove(char key, char block_char,int Xms)
{
    green_block_by_key(key, block_char);
    Sleep(Xms);
    remove_block_blank(coordinate[key - 'A'][0], coordinate[key - 'A'][1]);
}

void green_then_white_block(char key, char block_char)
{
    green_block_by_key(key, block_char);
    Sleep(500);
    white_block_by_key(key, block_char);
}
