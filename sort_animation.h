#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <menu.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <unistd.h>
#include <time.h>

#define ENTER '\n'
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

typedef unsigned int uint;

typedef struct data {
	int *numbers; /* will store the numbers which are randomly generated */
	uint elements; /* number of elements in 'numbers' array */
	uint swaps; /* for storing the number of swaps the sorting algorithm makes */
	uint comparisons; /* for storing the number of comparisons the sorting algorithm makes */
} data;

/* menu function prints the main menu containing the list of sorting algorithms */
void menu(FILE *f1, char *a);

/* print_in_middle function prints a string in the middle of a box */
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);

/* print_intro function prints the introduction page of the sorting algorithms, taking input from a file */
void print_intro(FILE *fp, int cur_y, int cur_x);

/* bubblesort function shows a demo of Bubble Sort */
int bubblesort(void);

/* create_newwin function creates a window having the following parameters */
WINDOW *create_newwin(int height_of_box, int width_of_box, int starty_of_box, int startx_of_box);

/* destroy_win function destroys the window associated with a box */
void destroy_win(WINDOW *local_win);

/* print_numbers prints the numbers from the array pointed to by num */
void print_numbers(data *p, int max_y, int max_x);

/* num_generator function generates 'elements' numbers randomly */
int num_generator(data *p);

/* get_num_elem function is to get input from the user the number of elements to perform sorting on */
void get_num_elem(data *p);

/* start function is for printing the start page */
char start(char *msg, FILE *f1, FILE *f2);
