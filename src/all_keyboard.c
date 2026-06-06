#include "../include/_include.h"
/*默认Q(0,0),则A(2,2),Z(4,4)*/
int coordinate[26][2] = {};
char first_line[] = {'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P'};
char second_line[] = {'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L'};
char third_line[] = {'Z', 'X', 'C', 'V', 'B', 'N', 'M'};
// #define Q_X 50
// #define Q_Y 10
void init_all_keyboard()
{
    for (size_t i = 0; i < sizeof(first_line) / sizeof(first_line[0]); i++)
    {
        coordinate[first_line[i] - 'A'][0] = Q_X + i * 4;
        coordinate[first_line[i] - 'A'][1] = Q_Y + 0;
    }
    for (size_t i = 0; i < sizeof(second_line) / sizeof(second_line[0]); i++)
    {
        coordinate[second_line[i] - 'A'][0] = Q_X + i * 4 + 2;
        coordinate[second_line[i] - 'A'][1] = Q_Y + 0 + 2;
    }
    for (size_t i = 0; i < sizeof(third_line) / sizeof(third_line[0]); i++)
    {
        coordinate[third_line[i] - 'A'][0] = Q_X + i * 4 + 2 + 2;
        coordinate[third_line[i] - 'A'][1] = Q_Y + 0 + 2 + 2;
    }
}
void print_all_keyboard_green()
{
    for (int i = 'A'; i <= 'Z'; i++)
    {
        green_block_by_key(i, BLOCK_CHAR_BLANK);
        // drawe_block_by_key(i, BLOCK_CHAR_PLUS);
        Sleep(200);
    }
}

void white_keyboard()
{
    for (int i = 'A'; i <= 'Z'; i++)
    {
        // drawe_block_by_key(i, BLOCK_CHAR_BLANK);
        white_block_by_key(i, BLOCK_CHAR_BLANK);
    }
}

void red_keyboard()
{
    for (int i = 'A'; i <= 'Z'; i++)
    {
        // drawe_block_by_key(i, BLOCK_CHAR_BLANK);
        red_block_by_key(i, BLOCK_CHAR_BLANK);
    }
}

void flowing()
{
    // 目前清屏，然后随机显示
}