
#include "../include/_include.h"

// 清除控制台中从startRow到endRow的内容（行号从1开始）
void ClearSpecificLines(int startRow, int endRow)
{
    // 获取控制台句柄
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE)
    {
        printf("获取控制台句柄失败！\n");
        return;
    }

    // 获取控制台屏幕缓冲区信息（包含窗口大小、光标位置等）
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        printf("获取控制台信息失败！\n");
        return;
    }

    // 保存当前光标位置，用于后续还原
    COORD originalCursorPos = csbi.dwCursorPosition;

    // 控制台缓冲区宽度（一行的字符数）
    DWORD bufferWidth = csbi.dwSize.X;
    // 用于存储覆盖行的空格
    char *emptyLine = (char *)malloc(bufferWidth + 1);
    if (emptyLine == NULL)
    {
        printf("内存分配失败！\n");
        return;
    }
    memset(emptyLine, ' ', bufferWidth); // 填充空格
    emptyLine[bufferWidth] = '\0';       // 字符串结束符

    // 遍历要清除的行，逐行覆盖
    for (int row = startRow; row <= endRow; row++)
    {
        // 设置光标位置到当前行的第0列（行号从0开始，所以要-1）
        COORD cursorPos;
        cursorPos.X = 0;
        cursorPos.Y = row - 1; // 转换为程序内部的0起始行号
        SetConsoleCursorPosition(hConsole, cursorPos);

        // 输出空格覆盖整行
        printf("%s", emptyLine);
    }

    // 还原光标到操作前的位置（可选，根据需求决定是否保留）
    SetConsoleCursorPosition(hConsole, originalCursorPos);

    // 释放内存
    free(emptyLine);
}
