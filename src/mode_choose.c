#include "../include/_include.h"

#define MODE1_NAME "mode1: basic test1"
#define MODE1_DESC "only one keytab, no pressure"
#define MODE2_NAME "mode2: basic test2"
#define MODE2_DESC "all keyboards, no pressure"
#define MODE3_NAME "mode3: advanced test1"
#define MODE3_DESC "all keyboards, time counter"
#define MODE4_NAME "mode4: advanced test2"
#define MODE4_DESC "keyboards remove, time counter"



struct mode
{
    char mode_name[30];
    char mode_desc[64];
    int x;
    int y;
} modes[4] = {
    {MODE1_NAME, MODE1_DESC, MODE_CHOOSE_X, MODE_CHOOSE_Y},
    {MODE2_NAME, MODE2_DESC, MODE_CHOOSE_X, MODE_CHOOSE_Y + 1},
    {MODE3_NAME, MODE3_DESC, MODE_CHOOSE_X, MODE_CHOOSE_Y + 2},
    {MODE4_NAME, MODE4_DESC, MODE_CHOOSE_X, MODE_CHOOSE_Y + 3}};

int cur_mode = 0;
int last_mode = -1;
int if_enter = 0;

// 这是当前mode的打印操作
static void print_cur_mode_and_show_desc()
{
    // 跳转到指定mode文字处
    gotoxy(modes[cur_mode].x, modes[cur_mode].y);
    // 将前面的文字变绿,并变出来后面的说明
    printf("%s%s%s->%s%s", GREEN, BOLD, modes[cur_mode].mode_name, modes[cur_mode].mode_desc, RESET);
    // 将后面的文字清除
}
// 这是上一个mode的删除操作
static void clear_last_mode_and_show_desc()
{
    // 跳转到指定mode文字处
    gotoxy(modes[last_mode].x, modes[last_mode].y);
    // 将前面的文字变白
    printf("%s", modes[last_mode].mode_name);
    // 将后面的文字清除
    for (size_t i = 0; i <= strlen(modes[last_mode].mode_desc) + 1; i++)
    {
        printf(" ");
    }
}

void only_print_my_mode_green_and_show_desc()
{
    clear_last_mode_and_show_desc(last_mode);
    print_cur_mode_and_show_desc(cur_mode);
}

void init_print_all_mode_green_and_show_desc()
{
    print_cur_mode_and_show_desc(cur_mode);
    for (int i = 0; i < 4; i++)
    {
        if (i == cur_mode)
        {
            continue;
        }
        gotoxy(modes[i].x, modes[i].y);
        printf("%s", modes[i].mode_name);
    }
}

int choose_mode()
{
    system("cls");
    init_game_area();
    init_print_all_mode_green_and_show_desc();
    
    while (1)
    {
        only_print_my_mode_green_and_show_desc();
        //显示动画的入口
        show_mode_flash(cur_mode);
        if (if_enter)
        {
            return cur_mode;
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
                    // system("cls");
                }
                else if (key == 0x50) // 下箭头
                {
                    last_mode = cur_mode;
                    cur_mode = cur_mode == 3 ? 0 : cur_mode + 1;
                    // system("cls");
                }
                else
                {
                    error_print("only up and down arrow key to choose mode");
                }
            }
            else if (key == 0x0D)
            {
                return cur_mode;
            }
            else
            {
                error_print("only up and down arrow key to choose mode");
            }
        }
    }
}