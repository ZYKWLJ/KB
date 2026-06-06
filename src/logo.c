
#include "../include/_include.h"
// 逐行打印指定图案的函数
// 将图案按行拆分，每行作为一个字符串
const char *logo_lines[] = {
    "\n\n\n\n\n\n\n \n\n\n\n _  __  ____  ",
    "| |/ / | __ ) ",
    "|   /  |  _ \\ ",
    "|   \\  | |_) |",
    "|_|\\_\\ |____/ ",
    "              " // 最后一行空行，与原图案一致
};
void print_logo(const char *logo_lines[],int line_count)
{
    // 获取图案的总行数
    // 逐行打印
    for (int i = 0; i < line_count; i++)
    {
        printf("%s\n", logo_lines[i]); // 打印当前行并换行
        // 可选：每行打印后延迟一段时间（如200毫秒），视觉效果更好
        // Sleep(200);
    }
}