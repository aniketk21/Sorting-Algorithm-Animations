#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <menu.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <unistd.h>

#define ENTER '\n'
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

void menu(FILE *f1, char *a);
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);
void info_on_sort(WINDOW *win, FILE *f3);
int bubblesort(void);
WINDOW *create_newwin(int height_of_box, int width_of_box, int starty_of_box, int startx_of_box);
void destroy_win(WINDOW *local_win);
void print_intro(FILE *fp, int cur_y, int cur_x);
void print_numbers(int *num, int max_y, int max_x);
