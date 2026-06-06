 
#ifndef GOTOXY_H_
#define GOTOXY_H_
#include<windows.h>
#include <conio.h>
// 移动光标到指定位置
void gotoxy(int x, int y);
// 隐藏光标
void hide_cursor();

#endif /* GOTOXY_H_ */