/*  Sorting Algorithm Animations.
 *  Copyright (C) 2015 kaniket21@gmail.com Aniket Kulkarni.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <menu.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <limits.h>

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
void menu(void);

/* print_in_middle function prints a string in the middle of a box */
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);

/* print_intro function prints the introduction page of the sorting algorithms, taking input from a file */
void print_intro(FILE *fp, int start_y, int start_x);

/* bubblesort function shows a demo of Bubble Sort */
int bubblesort(void);

/* selectionsort function shows a demo of Selection Sort */
int selectionsort(void);

/* quicksort function shows a demo of Quicksort */
int quicksort(void);

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
char start(void);

/* num_of_rows function returns the number of rows in a file. This function is needed for printing the description of a sorting algo */
int num_of_rows(FILE *fp);

/* init_sort_info initialises the number of swaps and comparisons of a particular sorting algo to 0 */
void init_sort_info(data *p);

/* message function prints the message "generating random numbers..." while the numbers are being generated */
void message(int max_y);

/* instruction function prints the instructions about how to proceed further */
void instruction(int y, int x, char *str);

/* box_over_num function places a box over an index specified along with a specific colour */
void box_over_num(int l, WINDOW *win, int max_y, int max_x, int height_of_box, int width_of_box, int color_pair);

/* clear_boxes function deletes the boxes after the animation is over */
void clear_boxes(int starty_of_box);
