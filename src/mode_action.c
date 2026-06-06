#include "../include/_include.h"

// get_key_loop_only_one_key
void mode_1_action()
{

    int last_key = 0; // 记录上一个按键
    int num_key = 0;

    while (1)
    {
        if (_kbhit())
        {

            int key = _getch();

            // 检查是否是ESC键
            if (key == 27)
            {
                printf("退出程序\n");
                return;
            }

            // 检查是否是字母键
            if ((key >= 'A' && key <= 'Z') || (key >= 'a' && key <= 'z'))
            {
                key ^= 1 << 5;
                if (key != last_key)
                { // 说明需要绘制新的形状
                    system("cls");
                    green_block_by_key(key, BLOCK_CHAR_BLANK);
                    last_key = key;
                }
            }
        }
        Sleep(20);
    }
}

// get_key_loop_all_key
void mode_2_action()
{
    int last_key = -1; // 记录上一个按键
    int num_key = 0;
    white_keyboard();
    while (1)
    {
        if (_kbhit())
        {

            int key = _getch();

            // 检查是否是ESC键
            if (key == 27)
            {
                printf("退出程序\n");
                return;
            }

            // 检查是否是字母键
            if ((key >= 'A' && key <= 'Z') || (key >= 'a' && key <= 'z'))
            {
                key ^= 1 << 5;
                if (last_key == -1)
                {
                    green_block_by_key(key, BLOCK_CHAR_BLANK);
                    last_key = key;
                }
                else if (key != last_key)
                { // 说明需要绘制新的形状
                    // 将上一个按键恢复颜色
                    white_block_by_key(last_key, BLOCK_CHAR_BLANK);
                    // 将新颜色上色
                    green_block_by_key(key, BLOCK_CHAR_BLANK);
                    last_key = key;
                }
            }
            else
            {
                // 循环读取缓冲区剩余所有字符，直到为空
                while (_kbhit())
                {
                    _getch(); // 读取并丢弃缓冲区剩余字符
                }
            }
        }
        Sleep(20);
    }
}

int key_26_no_repeat[26] = {0};

static void init_key_26_no_repeat()
{
    for (int i = 0; i < 26; i++)
    {
        key_26_no_repeat[i] = 0;
    }
}

// 这个判重逻辑是没有问题的！测试过了，但是这里为什么有问题呢？
char press_random_key_no_repeat()
{

    gotoxy(coordinate['V' - 'A'][0] - 7, coordinate['V' - 'A'][1] + 6);
    printf("press:");
    // 关键修复1：srand不能放在子函数内！否则每次调用都会重置随机数种子，导致随机数重复
    // 注意：srand((unsigned int)time(NULL)); 需移到main函数/程序入口处，只执行一次

    // 改用索引操作，避免字符运算的边界错误
    int random_idx = rand() % 26;

    // 关键修复2：持续循环直到找到未使用的位置（核心逻辑修正）
    while (key_26_no_repeat[random_idx] == 1)
    {
        random_idx = (random_idx + 1) % 26; // 逐个往后找，直到找到未使用的索引
    }

    // 标记为已使用，并转换为字符
    key_26_no_repeat[random_idx] = 1;
    char random_key = 'A' + random_idx;
    drawe_green_blank(coordinate['V' - 'A'][0] + 2, coordinate['V' - 'A'][1] + 5, ' ', random_key);
    return random_key;
}

void green_shine_key(char key)
{
    green_block_by_key(key, BLOCK_CHAR_BLANK);
    Sleep(100);
    remove_block_blank(coordinate[key - 'A'][0], coordinate[key - 'A'][1]);
    Sleep(100);
    white_block_by_key(key, BLOCK_CHAR_BLANK);
}

void red_shine_key(char key)
{
    red_block_by_key(key, BLOCK_CHAR_BLANK);
    Sleep(500);
    remove_block_blank(coordinate[key - 'A'][0], coordinate[key - 'A'][1]);
    Sleep(500);
    white_block_by_key(key, BLOCK_CHAR_BLANK);
}
// 给出目标键，让你按下，初始全部为白色，按下为绿色.按错了，错误答案会闪烁红色，正确答案会闪动绿色！
void mode_3_action()
{
    // int last_key = -1; // 记录上一个按键
    // int num_key = 0;
    white_keyboard();
    init_key_26_no_repeat();
    int time_count = 0;
    // 定义计时变量，存储开始和结束时间
    // struct timespec start, end;
    // 存储总耗时（秒 + 纳秒）
    double elapsed_time;
    // 记录开始时间
    // clock_gettime(CLOCK_MONOTONIC, &start);
    double waste_time = 0;
    while (1)
    {
        if (time_count == 26)
        {
            ClearSpecificLines(coordinate['V' - 'A'][0] - 7, coordinate['V' - 'A'][1] + 5 + 8);
            gotoxy(coordinate['V' - 'A'][0] - 7, coordinate['V' - 'A'][1] + 9);
            printf("total time: %.6f sec\n", elapsed_time);
            Sleep(2000);
            while (1)
            {
                if (_kbhit())
                {

                    int key = _getch();

                    // 直到按下ESC才退出
                    if (key == 27)
                    {
                        return;
                    }
                }
            }
        }
        time_count++;
        char random_key = press_random_key_no_repeat();
        // 定义单次时间
        double single_turn_time = 0;
        // 定义计时变量，存储开始和结束时间
        struct timespec start_single, end_single;
        // 记录开始时间
        clock_gettime(CLOCK_MONOTONIC, &start_single);
        while (1)
        {

            if (_kbhit())
            {

                int key = _getch();

                // 检查是否是ESC键
                if (key == 27)
                {
                    printf("退出程序\n");
                    return;
                }

                // 检查是否是字母键
                if ((key >= 'A' && key <= 'Z') || (key >= 'a' && key <= 'z'))
                {
                    key ^= 1 << 5;
                    if (key == random_key)
                    {
                        green_block_by_key(key, BLOCK_CHAR_BLANK);
                        break;
                    }
                    else
                    {
                        red_shine_key(key);          // 1000ms
                        Sleep(500);                  // 500ms
                        green_shine_key(random_key); // 200ms
                        waste_time += 1.5;           // 1000ms+500ms+200ms=1700ms
                    }
                }
                else
                {
                    // 循环读取缓冲区剩余所有字符，直到为空
                    while (_kbhit())
                    {
                        _getch(); // 读取并丢弃缓冲区剩余字符
                    }
                }
            }
        }
        clock_gettime(CLOCK_MONOTONIC, &end_single);
        // 计算总耗时（秒 + 纳秒）
        single_turn_time = (end_single.tv_sec - start_single.tv_sec) + (end_single.tv_nsec - start_single.tv_nsec) / 1e9 - waste_time;
        gotoxy(coordinate['V' - 'A'][0] - 7, coordinate['V' - 'A'][1] + 9);
        printf("press '%c' time: %.6f sec\n", random_key, single_turn_time);
        elapsed_time += single_turn_time;
        Sleep(20);
    }
}

int key_26_no_repeat_mode_4[26] = {0};

static void init_key_26_no_repeat_mode_4()
{
    for (int i = 0; i < 26; i++)
    {
        key_26_no_repeat_mode_4[i] = 0;
    }
}

// 这个判重逻辑是没有问题的！测试过了，但是这里为什么有问题呢？
char press_random_key_no_repeat_mode_4()
{

    gotoxy(coordinate['V' - 'A'][0] - 7, coordinate['V' - 'A'][1] + 6);
    printf("press:");
    // 关键修复1：srand不能放在子函数内！否则每次调用都会重置随机数种子，导致随机数重复
    // 注意：srand((unsigned int)time(NULL)); 需移到main函数/程序入口处，只执行一次

    // 改用索引操作，避免字符运算的边界错误
    int random_idx = rand() % 26;

    // 关键修复2：持续循环直到找到未使用的位置（核心逻辑修正）
    while (key_26_no_repeat_mode_4[random_idx] == 1)
    {
        random_idx = (random_idx + 1) % 26; // 逐个往后找，直到找到未使用的索引
    }

    // 标记为已使用，并转换为字符
    key_26_no_repeat_mode_4[random_idx] = 1;
    char random_key = 'A' + random_idx;
    drawe_green_blank(coordinate['V' - 'A'][0] + 2, coordinate['V' - 'A'][1] + 5, ' ', random_key);
    return random_key;
}

static char_recond_action_4[26] = {0};

static void re_init_char_recond_action_4()
{
    int total = 0;
    for (int i = 0; i < 26; i++)
    {
        total += char_recond_action_4[i];
    }
    if (total == 26)
    {
        for (int i = 0; i < 26; i++)
        {
            char_recond_action_4[i] = 0;
        }
    }
}
static void white_keyboard_without_somekey(int char_recond[])
{
    for (int i = 0; i < 26; i++)
    {
        if (char_recond[i] == 0) // 0才绘制，1不绘制了
        {
            white_block_by_key('A' + i, BLOCK_CHAR_BLANK);
        }
    }
}

// 给出目标键，让你按下，初始全部为白色，按下后该键位闪烁绿色后，消失
void mode_4_action()
{
    // int last_key = -1; // 记录上一个按键
    // int num_key = 0;
    white_keyboard();
    init_key_26_no_repeat_mode_4();
    int time_count = 0;
    // 定义计时变量，存储开始和结束时间
    // struct timespec start, end;
    // 存储总耗时（秒 + 纳秒）
    double elapsed_time;
    // 记录开始时间
    // clock_gettime(CLOCK_MONOTONIC, &start);
    double waste_time = 0;
    while (1)
    {
        if (time_count == 26)
        {
            ClearSpecificLines(coordinate['V' - 'A'][0] - 7, coordinate['V' - 'A'][1] + 5 + 8);
            gotoxy(coordinate['V' - 'A'][0] - 7, coordinate['V' - 'A'][1] + 9);
            printf("total time: %.6f sec\n", elapsed_time);
            Sleep(2000);
            while (1)
            {
                if (_kbhit())
                {

                    int key = _getch();

                    // 直到按下ESC才退出
                    if (key == 27)
                    {
                        return;
                    }
                }
            }
        }
        time_count++;
        char random_key = press_random_key_no_repeat_mode_4();
        // 定义单次时间
        double single_turn_time = 0;
        // 定义计时变量，存储开始和结束时间
        struct timespec start_single, end_single;
        // 记录开始时间
        clock_gettime(CLOCK_MONOTONIC, &start_single);
        // 这里才真正开始动作！
        while (1)
        {

            if (_kbhit())
            {

                int key = _getch();

                // 检查是否是ESC键
                if (key == 27)
                {
                    printf("退出程序\n");
                    return;
                }

                // 检查是否是字母键
                if ((key >= 'A' && key <= 'Z') || (key >= 'a' && key <= 'z'))
                {
                    key ^= 1 << 5;
                    if (key == random_key)
                    {
                        green_block_Xms_then_remove(key, ' ', 100);
                        char_recond_action_4[key - 'A'] = 1;
                        white_keyboard_without_somekey(char_recond_action_4);
                        re_init_char_recond_action_4();
                        break;
                    }
                    else
                    {
                        red_shine_key(key);          // 1000ms
                        Sleep(500);                  // 500ms
                        green_shine_key(random_key); // 200ms
                        waste_time += 1.5;           // 1000ms+500ms+200ms=1700ms
                    }
                }
                else
                {
                    // 循环读取缓冲区剩余所有字符，直到为空
                    while (_kbhit())
                    {
                        _getch(); // 读取并丢弃缓冲区剩余字符
                    }
                }
            }
        }
        clock_gettime(CLOCK_MONOTONIC, &end_single);
        // 计算总耗时（秒 + 纳秒）
        single_turn_time = (end_single.tv_sec - start_single.tv_sec) + (end_single.tv_nsec - start_single.tv_nsec) / 1e9 - waste_time;
        gotoxy(coordinate['V' - 'A'][0] - 7, coordinate['V' - 'A'][1] + 9);
        printf("press '%c' time: %.6f sec\n", random_key, single_turn_time);
        elapsed_time += single_turn_time;
        Sleep(10);
    }
}
