#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int key_26_no_repeat[26] = {0};
static void init_key_26_no_repeat()
{
    for (int i = 0; i < 26; i++)
    {
        key_26_no_repeat[i] = 0;
    }
}
static void print_key_26_no_repeat_remain()
{
    for (int i = 0; i < 26; i++)
    {
        if (key_26_no_repeat[i] == 0)
        {
            printf("%c ", 'A' + i);
        }
    }
    printf("\n");
}

void loop()
{
    for (int i = 0; i < 26; i++)
    {
        printf("time=>%d\t",i);
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
        print_key_26_no_repeat_remain();
    }
}
int main(void)
{
    srand(time(NULL));
    init_key_26_no_repeat();
    loop();
    return 0;
}