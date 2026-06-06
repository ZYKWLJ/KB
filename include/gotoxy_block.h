
#include "../include/_include.h"

#define BLOCK_CHAR_PLUS '+'
#define BLOCK_CHAR_BLANK ' '
//复色选中按键
void drawe_block_blank(int x, int y, char block_char, char key);
//完美的方块
void drawe_block_green_beauty(int x, int y, char key);
// 染色选中按键
void drawe_block_green(int x, int y, char block_char, char key);
//显示一个快快，然后消失
void green_block_then_remove(char key, char block_char);
void green_then_white_block(char key, char block_char);
void green_block_by_key(char key, char block_char);
void white_block_by_key(char key, char block_char);
void red_block_by_key(char key, char block_char);
void remove_block_blank(int x, int y);
void green_block_Xms_then_remove(char key, char block_char,int Xms);