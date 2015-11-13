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

int selectionsort(void) {
	WINDOW *win1, *win2, *win3;
	FILE *fp1;
	int startx_of_box, starty_of_box, width_of_box, height_of_box, max_x, max_y, start_y, start_x;  
	int choice, i, j, iter_no = 1, inner_iter, random = 1;
	int min, min_index, x_box1, x_box2;
	char c;
	data ssort;

	init_sort_info(&ssort); /* initialise number of swaps and comparisons to 0 */
	win3 = NULL;
	cbreak();
	
	fp1 = fopen("files/selectionsort.txt", "r");
	if(fp1 == NULL) {
		perror("open failed on file selectionsort.txt");
		return errno;
	}	
	
	getmaxyx(stdscr, max_y, max_x); /* get max coordinates of the screen */
	print_in_middle(stdscr, 3, 0, max_x, "SELECTION SORT", COLOR_PAIR(3));
	
	start_y = max_y / 5;
	start_x = max_x / 4 + 4;
	print_intro(fp1, start_y, start_x); /* print the introduction page of Selection Sort */
	
	instruction(max_y - 2, 0, "Press <ENTER> to CONTINUE or 'p' to return to the previous menu.");
	c = getch();
	if(c == 'p') { /* exit */
		clear();
		curs_set(TRUE);
		return 0;
	}	
	else {
		get_num_elem(&ssort); /* get the number of elements to perform sorting on */
		clear();
		
		while(random != 0) { /* this loop is required because sometimes random function generates already sorted elements */
			random = num_generator(&ssort); /* randomly generate 'elements' numbers and store in ssort.numbers[elements] */
			message(max_y); /* print "generating random numbers..." */
		}
		clear();
		
		print_in_middle(stdscr, 3, 0, max_x, "SELECTION SORT", COLOR_PAIR(3));
		
		inner_iter = ssort.elements;
		height_of_box = 3; /* height of box */
		width_of_box = 4; /* width of box */
		starty_of_box = (max_y - height_of_box) / 4 + 5;  /* starting y coordinate of the box */
		startx_of_box = max_x / 4 + 2;  /* starting x coordinate of the box */
		
		instruction(max_y - 3, 0, "Press <ENTER> to START.");
		instruction(max_y - 2, 0, "Press 'p' to go to the Main Menu.\n");
		
		curs_set(FALSE); /* curs_set(TRUE) shows a dirty cursor at top-left of the box */
		win1 = create_newwin(height_of_box, width_of_box, starty_of_box, startx_of_box); /* create windows */
		startx_of_box += 8;
		win2 = create_newwin(height_of_box, width_of_box, starty_of_box, startx_of_box);
		
		attron(A_BOLD);	
		print_numbers(&ssort, max_y, max_x);
		attroff(A_BOLD);
		choice = getch();
		if(choice == 'p') { /* exit */
			clear();
			curs_set(TRUE);
			destroy_win(win1);
			destroy_win(win2);
			return 0;
		}	
		if(choice == ENTER) { /* start the animation */
			move(max_y - 3, 0);
			clrtoeol();
			
			attron(A_BOLD);
			mvprintw(max_y - 12, 0, "GREEN: Smallest element in the current list.");
			mvprintw(max_y - 10, 0, "YELLOW: Final position of element.");
			attroff(A_BOLD);
			
			instruction(max_y - 3, 0, "Press <RIGHT ARROW KEY> to proceed to the next step.");
			sleep(3);
			attron(A_BOLD);
			refresh();
			destroy_win(win1);
			x_box1 = startx_of_box;
			for(j = 0; j < ssort.elements - 1; j++) {
				sleep(1);
				mvprintw(max_y / 4, (max_x - 19) / 2,"Iteration number: %d", iter_no);
				
				destroy_win(win2);
				print_numbers(&ssort, max_y, max_x);
				x_box2 = x_box1 + 5;
				win1 = create_newwin(height_of_box, width_of_box, starty_of_box, x_box1);
				win2 = create_newwin(height_of_box, width_of_box, starty_of_box, x_box1 + 5);
				
				print_numbers(&ssort, max_y, max_x);
				
				min = ssort.numbers[j];
				min_index = j;
				
				move(max_y - 19, 0);
				clrtoeol();
				mvprintw(max_y - 19, max_x / 4 + 18, "Minimum element is %d.", ssort.numbers[j]);
				refresh();
				for(i = j + 1; i < inner_iter; i++) {
					sleep(1);
					print_numbers(&ssort, max_y, max_x);
					destroy_win(win2);
					win2 = create_newwin(height_of_box, width_of_box, starty_of_box, x_box2);
					if(ssort.numbers[i] < min) {
						print_numbers(&ssort, max_y, max_x);
						sleep(1);
						min = ssort.numbers[i];
						min_index = i;
						move(max_y - 19, 0);
						clrtoeol();
						mvprintw(max_y - 19, max_x / 4 + 18, "New minimum element is %d.", ssort.numbers[i]);
						refresh();
					}
					else {
						move(max_y - 19, 0);
						clrtoeol();
						mvprintw(max_y - 19, max_x / 4 + 18, "Minimum element remains %d.", ssort.numbers[min_index]);
						refresh();
					}	
					ssort.comparisons++; /* increment the number of comparisons in ssort */
					print_numbers(&ssort, max_y, max_x);
					choice = getch();
					if(choice == 'p') { /* exit */
						clear();
						curs_set(TRUE);
						destroy_win(win1);
						destroy_win(win2);
						return 0;
					}
					x_box2 += 5;
				}
				iter_no++;
				/* place a box over the smallest number */
				box_over_num(min_index, win3, max_y, max_x, height_of_box, width_of_box, 3);
				print_numbers(&ssort, max_y, max_x);
				sleep(1);
				
				move(max_y - 19, 0);
				clrtoeol();
				mvprintw(max_y - 19, max_x / 4 + 18, "Now %d and %d get swapped.", ssort.numbers[min_index], ssort.numbers[j]);
				refresh();
				sleep(2);
				
				destroy_win(win3);
				print_numbers(&ssort, max_y, max_x);
				win3 = NULL;
				
				ssort.numbers[min_index] = ssort.numbers[j];
				ssort.numbers[j] = min;
				ssort.swaps++;
				/* place a box over the number, now in its final position */
				box_over_num(j, win3, max_y, max_x, height_of_box, width_of_box, 4);
				
				x_box1 += 5;
				print_numbers(&ssort, max_y, max_x);
			}
			destroy_win(win1);
			destroy_win(win2);
			print_numbers(&ssort, max_y, max_x);
			sleep(1);
			
			clear_boxes(starty_of_box); /* clear the boxes from the screen */
			
			move(max_y - 19, 0);
			clrtobot();
			mvprintw(max_y - 17, max_x / 4 + 15, "Yeah! The numbers are sorted!!");
			mvprintw(max_y - 13, max_x / 4 + 15, "Info:");
			mvprintw(max_y - 11, max_x / 4 + 15, "Number of swaps = %d", ssort.swaps);
			mvprintw(max_y - 9, max_x / 4 + 15, "Number of comparisons = %d", ssort.comparisons);
			attroff(A_BOLD);
		}
		move(max_y - 4, 0);
		clrtobot();
		curs_set(TRUE);
		instruction(max_y - 2, 0, "Press any key to continue.\n");
		getch();
	}
	fclose(fp1);
	free(ssort.numbers);
	return 0;
}
