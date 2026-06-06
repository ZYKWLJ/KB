
#include "../include/_include.h"
void error_print(char *chars)
{
    gotoxy(error_line_x, error_line_y);
    printf("%s", error_chars);
    printf("%s", chars);
    Sleep(1000);
    gotoxy(error_line_x, error_line_y);
    for (size_t i = 0; i < strlen(error_chars) + strlen(chars); i++)
    {
        printf("%s", " ");

    }
}