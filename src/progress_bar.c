#include "../include/_include.h"
static void origin_empty_process()
{
    int x = 0, y = 30;
    gotoxy(x++, y);
    printf("[");
    for (int i = 0; i < 100; i++)
    {
        gotoxy(x++, y);
        printf("%s", single_dot);
    }
    printf("]");
}
void process()
{
    origin_empty_process();
    int x = 0, y = 30;
    gotoxy(x++, y);
    printf("[");
    for (int i = 0; i < 100; i++)
    {
        gotoxy(x++, y);
        printf("%s", single_bar);
        Sleep(10);
    }
    printf("]");
}
