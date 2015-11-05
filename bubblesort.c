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

#include "sort_animation.h"

int bubblesort(void) {
	WINDOW *win1, *win2;
	FILE *fp1;
	int startx_of_box, starty_of_box, width_of_box, height_of_box, max_x, max_y, cur_y, cur_x;  
	int ch, i, j, orig_x_of_box, temp, iter_no = 1, inner_iter, swapped = 1, random = 1;
	char c;
	data bsort;
	
	fp1 = fopen("files/bubblesort.txt", "r");
	if(fp1 == NULL) {
		perror("open failed on file bubblesort.txt");
		return errno;
	}	
	
	init_sort_info(&bsort);
	cbreak();
	getmaxyx(stdscr, max_y, max_x);
	attron(A_BOLD);
	print_in_middle(stdscr, 5, 0, max_x, "BUBBLE SORT", COLOR_PAIR(1));
	cur_y = max_y / 4;
	cur_x = max_x / 4 + 4;
	move(cur_y, cur_x);
	print_intro(fp1, cur_y, cur_x); /* print the introduction page of Bubble Sort */
	attroff(A_BOLD);
	attron(A_REVERSE);
	mvprintw(LINES - 2, 0, "Press <ENTER> to CONTINUE or 'n' to EXIT");
	attroff(A_REVERSE);
	c = getch();
	if(c == 'n') {
		clear();
	}	
	else {
		get_num_elem(&bsort); /* get the number of elements to perform sorting on */
		clear();
		attron(A_BOLD);
		print_in_middle(stdscr, 3, 0, max_x, "BUBBLE SORT", COLOR_PAIR(1));
		attroff(A_BOLD);
		while(random != 0) {
			random = num_generator(&bsort); /* randomly generate 'elements' numbers and store in bsort.numbers[elements] */
		}
		inner_iter = bsort.elements;
		height_of_box = 3;
		width_of_box = 4;
		starty_of_box = (max_y - height_of_box) / 4 + 5;
		startx_of_box = max_x / 4 + 2;
		attron(A_REVERSE);
		mvprintw(max_y - 3, 0, "Press <ENTER> to START");
		mvprintw(max_y - 2, 0, "Press 'n' to EXIT");
		attroff(A_REVERSE);
		curs_set(FALSE);
		win1 = create_newwin(height_of_box, width_of_box, starty_of_box, startx_of_box);
		startx_of_box += 8;
		orig_x_of_box = startx_of_box;
		win2 = create_newwin(height_of_box, width_of_box, starty_of_box, startx_of_box);
		attron(A_BOLD);
		print_numbers(&bsort, max_y, max_x);
		attroff(A_BOLD);
		ch = getch();
		if(ch == ENTER) {
			move(max_y - 3, 0);
			clrtoeol();
			attron(A_REVERSE);
			mvprintw(max_y - 3, 0, "Press Right Arrow Key to go to the next step");
			attroff(A_REVERSE);
			sleep(1);
			attron(A_BOLD);
			refresh();
			for(j = 0; swapped && j < bsort.elements - 1; j++) {
				sleep(1);
				swapped = 0;
				mvprintw(max_y / 4, (max_x - 19) / 2,"Iteration number: %d", iter_no);
				for(i = 0; i < inner_iter - 1; i++) {
					sleep(1);
					print_numbers(&bsort, max_y, max_x);
					destroy_win(win1);
					destroy_win(win2);
					print_numbers(&bsort, max_y, max_x);
					win1 = create_newwin(height_of_box, width_of_box, starty_of_box, startx_of_box);
					win2 = create_newwin(height_of_box, width_of_box, starty_of_box, startx_of_box += 5);
					bsort.comparisons++;
					if(bsort.numbers[i] > bsort.numbers[i + 1]) {
						print_numbers(&bsort, max_y, max_x);
						sleep(1);
						move(max_y - 19, 0);
						clrtoeol();
						mvprintw(max_y - 19, max_x / 4 + 18, "Element %d is greater than %d.", bsort.numbers[i], bsort.numbers[i + 1]);
						move(max_y - 17, 0);
						clrtoeol();
						mvprintw(max_y - 17, max_x / 4 + 18, "Hence %d and %d get swapped.", bsort.numbers[i], bsort.numbers[i + 1]);
						refresh(); /* for printing immediately on the screen */
						temp = bsort.numbers[i];
						bsort.numbers[i] = bsort.numbers[i + 1];
						bsort.numbers[i + 1] = temp;
						bsort.swaps++;
						sleep(1);
						print_numbers(&bsort, max_y, max_x);
						swapped++;
					}
					else {
						print_numbers(&bsort, max_y, max_x);
						move(max_y - 19, 0);
						clrtoeol();
						mvprintw(max_y - 19, max_x / 4 + 18, "Element %d is not greater than %d.", bsort.numbers[i], bsort.numbers[i + 1]);
						move(max_y - 17, 0);
						clrtoeol();
						mvprintw(max_y - 17, max_x / 4 + 18, "Hence these two elements don't get swapped");
						refresh();
					}
					print_numbers(&bsort, max_y, max_x);
					ch = getch();
					if(ch == 'n') {
						clear();
						wclear(win1);
						wclear(win2);
						delwin(win1);
						delwin(win2);
						return 0;
					}
				}
				inner_iter--;
				iter_no++;
				print_numbers(&bsort, max_y, max_x);
				sleep(1);
				destroy_win(win1);
				destroy_win(win2);
				win1 = create_newwin(height_of_box, width_of_box, starty_of_box, orig_x_of_box);
				startx_of_box = orig_x_of_box;
				win2 = create_newwin(height_of_box, width_of_box, starty_of_box, orig_x_of_box + 5);
				wrefresh(win1);
				wrefresh(win2);
				print_numbers(&bsort, max_y, max_x);
			}
			move(max_y - 19, 0);
			clrtobot();
			if(iter_no != bsort.elements) {
				mvprintw(max_y - 18, max_x / 4 + 15, "No swap took place in the previous iteration");
				mvprintw(max_y - 17, max_x / 4 + 15, "this indicates that the numbers are sorted.");
			}
			else {
				mvprintw(max_y - 18, max_x / 4 + 15, "Yeah! The numbers are sorted!!");
			}
			mvprintw(max_y - 14, max_x / 4 + 15, "Info:");
			mvprintw(max_y - 12, max_x / 4 + 15, "Number of swaps = %d", bsort.swaps);
			mvprintw(max_y - 10, max_x / 4 + 15, "Number of comparisons = %d", bsort.comparisons);
			attroff(A_BOLD);
		}	
		move(max_y - 4, 0);
		clrtobot();
		curs_set(TRUE);
		mvprintw(max_y - 2, 0, "Press any key to continue");
		getch();
	}
	delwin(win1);
	delwin(win2);
	fclose(fp1);
	return 0;
}
