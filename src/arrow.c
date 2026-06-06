#include "../include/_include.h"

#define ARROW_ACTION_X Q_X - 10
#define ARROW_ACTION_Y Q_Y + 1

#define ARROW_MENU_X MODE_CHOOSE_X - 10
#define ARROW_MENU_Y MODE_CHOOSE_Y

void arrow_menu(int mode_id)
{
    gotoxy(ARROW_MENU_X, ARROW_MENU_Y + mode_id);
    printf("%s=>%s", BOLD, RESET);
}
void arrow_action()
{
    gotoxy(ARROW_ACTION_X, ARROW_ACTION_Y);
    printf("%s=>%s", BOLD, RESET);
}

void arrow_menu_remove(int mode_id)
{
    gotoxy(ARROW_MENU_X, ARROW_MENU_Y + mode_id);
    printf("  ");
}
void arrow_action_remove()
{
    gotoxy(ARROW_ACTION_X, ARROW_ACTION_Y);
    printf("  ");
}
