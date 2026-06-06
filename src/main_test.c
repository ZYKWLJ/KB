
#include "../include/_include.h"

int main(void)
{
    hide_cursor();
    init_game_area();
    // Sleep(20000);
    // 必须只执行一次！
    srand((unsigned int)time(NULL));
    // process();

    init_all_keyboard();
    while (1)
    {
        switch (choose_mode())
        {
            // 这里不会执行？注意这个特点！直接跳转到对应标签处去了！
            // arrow_menu_remove();
            // arrow_action();

        case 0:
        {
            arrow_menu_remove(cur_mode);
            arrow_action();
            // 只显示单个按键，绿色
            mode_1_action();
            system("cls");
        }
        /* code */
        break;
        case 1:
        {
            arrow_menu_remove(cur_mode);
            arrow_action();
            // 显示全部键盘(白色)，按下的键显示为绿色
            mode_2_action();
            system("cls");
        }
        break;
        case 2:
        {
            arrow_menu_remove(cur_mode);
            arrow_action();
            // 给出目标键，让你按下，初始全部为白色，按下为绿色，且累加
            mode_3_action();
            system("cls");
        }
        /* code */
        break;
        case 3:
        {
            arrow_menu_remove(cur_mode);
            arrow_action();
            // 给出目标键，让你按下，，初始全部为白色，按下后该键位消失绿色后，消失
            mode_4_action();
            system("cls");
        }
        /* code */
        break;
        default:
            break;
        }
        if_enter = 0;
        // 循环读取缓冲区剩余所有字符，直到为空
        while (_kbhit())
        {
            _getch(); // 读取并丢弃缓冲区剩余字符
        }
    }

    return 0;
}