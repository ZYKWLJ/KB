#include "../include/_include.h"
// 乱序播放，按下键盘后打破循环进入游戏！
void flash(void)
{
    // for (char c = 'A'; c <= 'Z'; c++)
    // {
    //     drawe_block_by_key(c, BLOCK_CHAR_BLANK);
    //     sleep(20);
    //     drawe_block_by_key(c, BLOCK_CHAR_BLANK);
    // }
    while (!_kbhit())
    {
        green_block_by_key('A' + rand() % 26, BLOCK_CHAR_BLANK);

        Sleep(500);
        // system("cls");
        ClearSpecificLines(0, 7);
    }
}

void flash2(void)
{
    int sec = 0;
    while (1)
    {
        printf("wait for %d sec", sec);
        Sleep(1000);
    }
}