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
	WINDOW *win1, *win2, *win3;
	FILE *fp1;
	int startx_of_box, starty_of_box, width_of_box, height_of_box, max_x, max_y, start_y, start_x;  
	int choice, i, j, orig_x_of_box, temp, iter_no = 1, inner_iter, swapped = 1, random = 1;
	char c;
	data bsort;
	
	fp1 = fopen("files/bubblesort.txt", "r");
	if(fp1 == NULL) {
		perror("open failed on file bubblesort.txt");
		return errno;
	}
	
	init_sort_info(&bsort);
	win3 = NULL;
	cbreak();
	
	getmaxyx(stdscr, max_y, max_x); /* store the max coordinates of the stdscr */
	print_in_middle(stdscr, 5, 0, max_x, "BUBBLE SORT", COLOR_PAIR(3));
	
	start_y = max_y / 4;
	start_x = max_x / 4 + 4;
	
	print_intro(fp1, start_y, start_x); /* print the introduction page of Bubble Sort */
	
	instruction(max_y - 2, 0, "Press <ENTER> to CONTINUE or 'p' to return to the previous menu.");
	c = getch();
	if(c == 'p') {
		clear();
		curs_set(TRUE);
		return 0;
	}	
	else {
		get_num_elem(&bsort); /* get the number of elements to perform sorting on */
		clear();
		
		while(random != 0) {
			random = num_generator(&bsort); /* randomly generate 'elements' numbers and store in bsort.numbers[elements] */
			message(max_y); /* print "generating numbers..." */
		}
		clear();

		print_in_middle(stdscr, 3, 0, max_x, "BUBBLE SORT", COLOR_PAIR(3));
		
		inner_iter = bsort.elements; /* inner_iter is used in second 'for' loop below as a loop control variable */
		height_of_box = 3;
		width_of_box = 4;
		starty_of_box = (max_y - height_of_box) / 4 + 5;
		startx_of_box = max_x / 4 + 2;
		instruction(max_y - 3, 0, "Press <ENTER> to START.");
		instruction(max_y - 2, 0, "Press 'p' to go to Main Menu.\n");
		
		curs_set(FALSE); /* curs_set(TRUE) shows a dirty cursor at top-left of the box */
		win1 = create_newwin(height_of_box, width_of_box, starty_of_box, startx_of_box);
		startx_of_box += 8;
		orig_x_of_box = startx_of_box;
		win2 = create_newwin(height_of_box, width_of_box, starty_of_box, startx_of_box);
		attron(A_BOLD);
		print_numbers(&bsort, max_y, max_x);
		attroff(A_BOLD);	
		choice = getch();
		if(choice == 'p') {
			clear();
			curs_set(TRUE);
			destroy_win(win1);
			destroy_win(win2);
			return 0;
		}	
		else if(choice == ENTER) {
			move(max_y - 3, 0);
			clrtoeol();
			instruction(max_y - 8, 0, "GREEN: Final position of element.");
			instruction(max_y - 3, 0, "Press Right Arrow Key to proceed to the next step.");
			sleep(3);
			attron(A_BOLD);
			for(j = 0; swapped && j < bsort.elements - 1; j++) {
				sleep(1);
				swapped = 0;
				mvprintw(max_y / 4, (max_x - 19) / 2,"Iteration number: %d", iter_no);
				refresh();
				for(i = 0; i < inner_iter - 1; i++) {
					print_numbers(&bsort, max_y, max_x);
					
					destroy_win(win1);
					destroy_win(win2);
					print_numbers(&bsort, max_y, max_x);
					win1 = create_newwin(height_of_box, width_of_box, starty_of_box, startx_of_box);
					win2 = create_newwin(height_of_box, width_of_box, starty_of_box, startx_of_box += 5);
					
					bsort.comparisons++;
					if(bsort.numbers[i] > bsort.numbers[i + 1]) {
						print_numbers(&bsort, max_y, max_x);
						sleep(0.5);
						
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
						
						sleep(2);
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
					
					choice = getch();
					if(choice == 'p') {
						clear();
						curs_set(TRUE);
						destroy_win(win1);
						destroy_win(win2);
						return 0;
					}
				}
				inner_iter--;/* this is to make the second box go one unit lesser to the right after each iteration */
				iter_no++;
				print_numbers(&bsort, max_y, max_x);
				sleep(1);
				
				destroy_win(win1);
				destroy_win(win2);
				win1 = create_newwin(height_of_box, width_of_box, starty_of_box, orig_x_of_box);
				startx_of_box = orig_x_of_box;
				win2 = create_newwin(height_of_box, width_of_box, starty_of_box, orig_x_of_box + 5);
				box_over_num(inner_iter, win3, max_y, max_x, height_of_box, width_of_box, 3);
				print_numbers(&bsort, max_y, max_x);
			}
			destroy_win(win1);
			destroy_win(win2);
			print_numbers(&bsort, max_y, max_x);
			sleep(1);
			clear_boxes(starty_of_box);
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
		}
		move(max_y - 4, 0);
		clrtobot();
		attroff(A_BOLD);
		curs_set(TRUE);
		instruction(max_y - 2, 0, "Press any key to continue.\n");
		getch();
	}
	fclose(fp1);
	return 0;
}
