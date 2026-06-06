#include "../include/_include.h"
// 在上方显示出对应mode的样式！

static void A_Z_random_show()
{
    green_block_then_remove('A' + rand() % 26, BLOCK_CHAR_BLANK);
}

static void show_mode_1_flash()
{
    init_print_all_mode_green_and_show_desc();

    while (1)
    {
        only_print_my_mode_green_and_show_desc();
        A_Z_random_show();
        if (_kbhit())
        {
            int key = _getch();
            if (key == 0xE0 || key == 0)
            { // 表示这个是扩展键
                key = _getch();
                if (key == 0x48) // 上箭头
                {
                    last_mode = cur_mode;
                    cur_mode = cur_mode == 0 ? 3 : cur_mode - 1;
                    break;
                }
                else if (key == 0x50) // 下箭头
                {
                    last_mode = cur_mode;
                    cur_mode = cur_mode == 3 ? 0 : cur_mode + 1;
                    break;
                }
                else
                {
                    error_print("only up and down arrow key to choose mode");
                }
                // only_print_my_mode_green_and_show_desc();
            }
            else if (key == 0x0D)
            {
                if_enter = 1;
                return;
            }
            else
            {
                error_print("only up and down arrow key to choose mode");
            }
        }
    }
}

// 这是模式2的动画，就是在模式一个情况下，显示全部的键盘，按中为绿色，否则为白色
static void show_mode_2_flash()
{
    init_print_all_mode_green_and_show_desc();
    white_keyboard();
    while (1)
    {
        only_print_my_mode_green_and_show_desc();
        green_then_white_block('A' + rand() % 26, BLOCK_CHAR_BLANK);
        if (_kbhit())
        {
            int key = _getch();
            if (key == 0xE0 || key == 0)
            { // 表示这个是扩展键
                key = _getch();
                if (key == 0x48) // 上箭头
                {
                    last_mode = cur_mode;
                    cur_mode = cur_mode == 0 ? 3 : cur_mode - 1;
                    break;
                }
                else if (key == 0x50) // 下箭头
                {
                    last_mode = cur_mode;
                    cur_mode = cur_mode == 3 ? 0 : cur_mode + 1;
                    break;
                }
                else
                {
                    error_print("only up and down arrow key to choose mode");
                }
                only_print_my_mode_green_and_show_desc();
            }
            else if (key == 0x0D)
            {
                if_enter = 1;
                return;
            }
            else
            {
                error_print("only up and down arrow key to choose mode");
            }
        }
    }
}

int key_one_by_one_no_repeat[26] = {0};

static void re_init_key_one_by_one_no_repeat()
{
    for (int i = 0; i < 26; i++)
    {
        key_one_by_one_no_repeat[i] = 0;
    }
}

static void avoid_repeat()
{
    int ret = 0;
    for (int i = 0; i < 26; i++)
    {
        ret += key_one_by_one_no_repeat[i];
    }
    if (ret == 26)
    {
        re_init_key_one_by_one_no_repeat();
        // 并且再次全白键盘！
        white_keyboard();
    }
}
static char press_one_by_one()
{
    gotoxy(coordinate['V' - 'A'][0] - 7, coordinate['V' - 'A'][1] + 6);
    printf("press:");
    // 关键修复1：srand不能放在子函数内！否则每次调用都会重置随机数种子，导致随机数重复
    // 注意：srand((unsigned int)time(NULL)); 需移到main函数/程序入口处，只执行一次
    // 弄完就从头开始！
    avoid_repeat();
    // 改用索引操作，避免字符运算的边界错误
    int random_idx = rand() % 26;

    // 关键修复2：持续循环直到找到未使用的位置（核心逻辑修正）
    while (key_one_by_one_no_repeat[random_idx] == 1)
    {
        random_idx = (random_idx + 1) % 26; // 逐个往后找，直到找到未使用的索引
    }

    // 标记为已使用，并转换为字符
    key_one_by_one_no_repeat[random_idx] = 1;
    char random_key = 'A' + random_idx;
    drawe_green_blank(coordinate['V' - 'A'][0] + 2, coordinate['V' - 'A'][1] + 5, ' ', random_key);
    return random_key;
}

void green_shine_to_green_key(char key)
{
    green_block_by_key(key, BLOCK_CHAR_BLANK);
    Sleep(500);
    remove_block_blank(coordinate[key - 'A'][0], coordinate[key - 'A'][1]);
    Sleep(500);
    green_block_by_key(key, BLOCK_CHAR_BLANK);
}
static void show_mode_3_flash()
{
    init_print_all_mode_green_and_show_desc();
    white_keyboard();
    while (1)
    {
        only_print_my_mode_green_and_show_desc();
        // green_then_white_block('A' + rand() % 26, BLOCK_CHAR_BLANK);
        char key = press_one_by_one(); // flash
        green_shine_to_green_key(key);
        gotoxy(coordinate['V' - 'A'][0] - 7, coordinate['V' - 'A'][1] + 9);
        int int_part = rand() % 1 + 1;               // 1~9的整数部分
        double dec_part = (double)rand() / RAND_MAX; // 0~1之间的随机小数
        double random_num = int_part + dec_part;     // 最终1~10的随机数
        printf("press '%c' time: %.6f sec\n", key, random_num);
        if (_kbhit())
        {
            int key = _getch();
            if (key == 0xE0 || key == 0)
            { // 表示这个是扩展键
                key = _getch();
                if (key == 0x48) // 上箭头
                {
                    last_mode = cur_mode;
                    cur_mode = cur_mode == 0 ? 3 : cur_mode - 1;
                    break;
                }
                else if (key == 0x50) // 下箭头
                {
                    last_mode = cur_mode;
                    cur_mode = cur_mode == 3 ? 0 : cur_mode + 1;
                    break;
                }
                else
                {
                    error_print("only up and down arrow key to choose mode");
                }
                only_print_my_mode_green_and_show_desc();
            }
            else if (key == 0x0D)
            {
                if_enter = 1;
                return;
            }
            else
            {
                error_print("only up and down arrow key to choose mode");
            }
        }
    }
}

int key_one_by_one_no_repeat_mode_4[26] = {0};

static void re_init_key_one_by_one_no_repeat_mode_4()
{
    for (int i = 0; i < 26; i++)
    {
        key_one_by_one_no_repeat_mode_4[i] = 0;
    }
}

static void avoid_repeat_mode_4()
{
    int ret = 0;
    for (int i = 0; i < 26; i++)
    {
        ret += key_one_by_one_no_repeat_mode_4[i];
    }
    if (ret == 26)
    {
        re_init_key_one_by_one_no_repeat_mode_4();
        // 并且再次全白键盘！
        white_keyboard();
    }
}
static char press_one_by_one_mode_4()
{
    gotoxy(coordinate['V' - 'A'][0] - 7, coordinate['V' - 'A'][1] + 6);
    printf("press:");
    // 关键修复1：srand不能放在子函数内！否则每次调用都会重置随机数种子，导致随机数重复
    // 注意：srand((unsigned int)time(NULL)); 需移到main函数/程序入口处，只执行一次
    // 弄完就从头开始！
    avoid_repeat_mode_4();
    // 改用索引操作，避免字符运算的边界错误
    int random_idx = rand() % 26;

    // 关键修复2：持续循环直到找到未使用的位置（核心逻辑修正）
    while (key_one_by_one_no_repeat_mode_4[random_idx] == 1)
    {
        random_idx = (random_idx + 1) % 26; // 逐个往后找，直到找到未使用的索引
    }

    // 标记为已使用，并转换为字符
    key_one_by_one_no_repeat_mode_4[random_idx] = 1;
    char random_key = 'A' + random_idx;
    drawe_green_blank(coordinate['V' - 'A'][0] + 2, coordinate['V' - 'A'][1] + 5, ' ', random_key);
    return random_key;
}

static char all_key[26] = {0};
static re_init_all_key()
{
    for (int i = 0; i < 26; i++)
    {
        all_key[i] = 0;
    }
}
// 查看是否需要全部赋值为0的标记
static int re_init_all_key_flag = 0;
void white_keyboard_without_somekey()
{
    int exist_0_or_not = 0;
    // 全部都是1了，就说明消除完了，这里需要重新开始
re:
    if (re_init_all_key_flag == 1)
    {
        Sleep(500); // 停顿1s更真实！
        re_init_all_key();
        re_init_all_key_flag = 0; // 记得复原，至关重要！
    }
    for (int i = 0; i < 26; i++)
    {
        if (all_key[i] == 0) // 0才绘制，1不绘制了
        {
            exist_0_or_not = 1; // 还有0在
            white_block_by_key('A' + i, BLOCK_CHAR_BLANK);
        }
    }
    // 没有0在，全部赋值为0
    if (exist_0_or_not == 0)
    {
        // 没有0在了，就要重新全部赋值为0
        re_init_all_key_flag = 1;
        goto re;
    }
}
// 消消乐！
static void show_mode_4_flash()
{
    init_print_all_mode_green_and_show_desc();
    white_keyboard();
    while (1)
    {
        only_print_my_mode_green_and_show_desc();
        // green_then_white_block('A' + rand() % 26, BLOCK_CHAR_BLANK);
        char key = press_one_by_one_mode_4(); // flash
        green_block_then_remove(key, ' ');
        all_key[key - 'A'] = 1; // 去除了下面就不绘制了
        // 因为残缺不全看起来很难看，所以我们每消失一个，都少绘制一个就好了！
        white_keyboard_without_somekey();
        {
            gotoxy(coordinate['V' - 'A'][0] - 7, coordinate['V' - 'A'][1] + 9);
            int int_part = rand() % 1 + 1;               // 1~9的整数部分
            double dec_part = (double)rand() / RAND_MAX; // 0~1之间的随机小数
            double random_num = int_part + dec_part;     // 最终1~10的随机数
            printf("press '%c' time: %.6f sec\n", key, random_num);
        }

        if (_kbhit())
        {
            int key = _getch();
            if (key == 0xE0 || key == 0)
            { // 表示这个是扩展键
                key = _getch();
                if (key == 0x48) // 上箭头
                {
                    last_mode = cur_mode;
                    cur_mode = cur_mode == 0 ? 3 : cur_mode - 1;
                    break;
                }
                else if (key == 0x50) // 下箭头
                {
                    last_mode = cur_mode;
                    cur_mode = cur_mode == 3 ? 0 : cur_mode + 1;
                    break;
                }
                else
                {
                    error_print("only up and down arrow key to choose mode");
                }
                only_print_my_mode_green_and_show_desc();
            }
            else if (key == 0x0D)
            {
                if_enter = 1;
                return;
            }
            else
            {
                error_print("only up and down arrow key to choose mode");
            }
        }
    }
}

void show_mode_flash(int mode)
{
    // gotoxy(0, 28);
    // printf("show_mode_flash mode=%d\n", mode);
    system("cls");
    init_game_area();
    arrow_action_remove();
    arrow_menu(cur_mode);
    switch (mode)
    {
    case 0:
        show_mode_1_flash();
        break;
    case 1:
        show_mode_2_flash();
        break;
    case 2:
        show_mode_3_flash();
        break;
    case 3:
        show_mode_4_flash();
        break;
    default:
        error_print("mode error");
        break;
    }
}