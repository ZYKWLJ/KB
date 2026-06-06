
#ifndef ERROR_H_
#define ERROR_H_
#include <stdio.h>
#include <windows.h>
#include "../include/gotoxy.h"
#define error_line_x 0
#define error_line_y AREA_HEIGHT + 10
#define error_chars BOLD RED "ERROR:" RESET
void error_print(char *chars);
#endif /* ERROR_H_ */