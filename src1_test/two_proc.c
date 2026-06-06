#include "../include/_include.h"
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Random playback function
void random_play(void)
{
    gotoxy(0, 0);
    int sec = 100;
    while (!_kbhit()) // Detect keyboard input, exit synchronously with time_count
    {
        printf("Timer Process 1: Waiting for %d seconds\r", sec);
        fflush(stdout); // Force flush output buffer
        Sleep(1000);
        sec++;
    }
    printf("\nTimer Process 1: Keyboard input detected, exiting timer!\n");
}

// Time counting output function
void time_count(void)
{
    gotoxy(3, 3);
    int sec = 0;
    while (!_kbhit()) // Detect keyboard input, exit synchronously with random_play
    {
        printf("Timer Process 2: Waiting for %d seconds\r", sec);
        fflush(stdout); // Force flush output buffer
        Sleep(1000);
        sec++;
    }
    printf("\nTimer Process 2: Keyboard input detected, exiting timer!\n");
}

// Child process entry function (distinguish which function to execute through command line parameters)
int main(int argc, char *argv[])
{
    system("cls");
    if (argc < 2)
    {
        // Parent process logic: create two child processes
        STARTUPINFO si = {0};
        PROCESS_INFORMATION pi1 = {0}, pi2 = {0};
        si.cb = sizeof(STARTUPINFO);

        // 获取当前程序的完整路径（关键修复点1）
        char exePath[MAX_PATH] = {0};
        GetModuleFileName(NULL, exePath, MAX_PATH);

        // 拼接命令行参数：完整路径 + 参数（关键修复点2）
        char cmd1[MAX_PATH] = {0};
        sprintf(cmd1, "\"%s\" 1", exePath); // 带引号避免路径含空格问题
        char cmd2[MAX_PATH] = {0};
        sprintf(cmd2, "\"%s\" 2", exePath);

        // Create random_play process
        BOOL ret1 = CreateProcess(
            exePath,               // 可执行文件完整路径（关键修复点3）
            cmd1,                  // 完整命令行（路径+参数）
            NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi1);

        // Create time_count process
        BOOL ret2 = CreateProcess(
            exePath,               // 可执行文件完整路径
            cmd2,                  // 完整命令行（路径+参数）
            NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi2);

        if (!ret1 || !ret2)
        {
            printf("Failed to create process! Error code: %d\n", GetLastError());
            return 1;
        }

        printf("Parent Process: Two child processes created, press any key to terminate...\n");
        _getch(); // Wait for user key press

        // Terminate child processes
        TerminateProcess(pi1.hProcess, 0);
        TerminateProcess(pi2.hProcess, 0);

        // Close process and thread handles
        CloseHandle(pi1.hProcess);
        CloseHandle(pi1.hThread);
        CloseHandle(pi2.hProcess);
        CloseHandle(pi2.hThread);

        printf("Parent Process: Child processes terminated, program exiting!\n");
    }
    else
    {
        // Child process logic: execute corresponding function according to parameters
        if (argv[1][0] == '1')
        {
            random_play(); // First child process executes random_play
        }
        else if (argv[1][0] == '2')
        {
            time_count(); // Second child process executes time_count
        }
    }

    return 0;
}