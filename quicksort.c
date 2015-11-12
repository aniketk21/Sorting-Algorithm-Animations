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

int partition(int a[], int l, int r, int max_y, int max_x, data *qcsort, WINDOW *win) {
	int pivot, i, j, temp, choice, posx_i, posx_j, y_i, y_j;
	
	pivot = a[l];
	/* place a red box over the pivot */
	box_over_num(l, win, max_y, max_x, 3, 4, 2); /* height of box = 3, width of box = 4 */
	
	attron(A_BOLD);
	
	y_i = (max_y - 3) / 4 + 3; /* y coordinate of the row in which 'i' moves */
	y_j = (max_y - 3) / 4 + 4; /* y coordinate of the row in which 'j' moves */
	i = l;
	j = r + 1;
	posx_j = max_x / 4 + 11 + 5 * (j - 1);
	
	mvprintw(y_j, posx_j, "j");
	refresh();
	print_numbers(qcsort, max_y, max_x);
	while(1) {
		do {
			move(y_i, 0);
			clrtoeol();
			
			++i;
			
			move(max_y - 19, max_x / 4 + 18);
			clrtoeol();
			if(a[i] <= pivot)
				mvprintw(max_y - 19, max_x / 4 + 18, "As i: %d <= pivot: %d, increment i.", a[i], pivot);
			else	
				mvprintw(max_y - 19, max_x / 4 + 18, "As i: %d > pivot: %d, stop.", a[i], pivot);
			posx_i = max_x / 4 + 11 + 5 * i;
			mvprintw(y_i, posx_i, "i");
			refresh();
			
			(qcsort->comparisons)++; /* increment the number of comparisons in qcsort */
			choice = getch();
			if(choice == 'p') /* exit */
				return INT_MIN;
		} while(a[i] <= pivot && i < r);
		do {
			move(y_j, 0);
			clrtoeol();

			--j;

			move(max_y - 19, max_x / 4 + 18);
			clrtoeol();
			if(a[j] > pivot)
				mvprintw(max_y - 19, max_x / 4 + 18, "As j: %d > pivot: %d, decrement j.", a[j], pivot);
			else	
				mvprintw(max_y - 19, max_x / 4 + 18, "As j: %d <= pivot: %d, stop.", a[j], pivot);
			posx_j = max_x / 4 + 11 + 5 * j;
			mvprintw(y_j, posx_j, "j");
			refresh();

			(qcsort->comparisons)++;
			choice = getch();
			if(choice == 'p') /* exit */
				return INT_MIN;
		} while(a[j] > pivot);
		if(i >= j) /*  i and j have crossed over */
			break;

		move(max_y - 19, max_x / 4 + 18);
		clrtoeol();
		mvprintw(max_y - 19, max_x / 4 + 18, "Now i: %d and j: %d get swapped.", a[i], a[j]);
		refresh();

		temp = a[i]; /* swap i and j */
		a[i] = a[j];
		a[j] = temp;

		(qcsort->swaps)++; /* increment swaps */
		choice = getch();
		print_numbers(qcsort, max_y, max_x);
	}
	move(max_y - 19, max_x / 4 + 18);
	clrtoeol();
	mvprintw(max_y - 19, max_x / 4 + 18, "As i and j have crossed, pivot: %d and j: %d get swapped.", a[l], a[j]);
	refresh();

	temp = a[l]; /* swap pivot and j */
	a[l] = a[j];
	a[j] = temp;
	(qcsort->swaps)++;
	choice = getch();
	if(choice == 'p') /* exit */
		return INT_MIN;
	
	print_numbers(qcsort, max_y, max_x);
	/* place a box over the element j */ 
	box_over_num(j, win, max_y, max_x, 3, 4, 3); /* height of box = 3, width of box = 4, color_pair = 3 */
	
	mvprintw(y_j, max_x / 4 + 11 + 5 * j, " "); /* copy a whitespace over the green box */
	attroff(A_BOLD);
	return j;
}

int quicksort_driver(int a[], int l, int r, int max_y, int max_x, data *qcsort, WINDOW *win) {
	int j;
	if(l < r) {
		j = partition(a, l, r, max_y, max_x, qcsort, win);
		if(j == INT_MIN) /* exit */
			return INT_MIN;
		quicksort_driver(a, l, j - 1, max_y, max_x, qcsort, win);
		quicksort_driver(a, j + 1, r, max_y, max_x, qcsort, win);
	}
	attron(A_BOLD);
	print_numbers(qcsort, max_y, max_x);
	attroff(A_BOLD);
	return 0;
}

int quicksort(void) {
	WINDOW *win1;
	FILE *fp1;
	int max_x, max_y, start_y, start_x, starty_of_box, height_of_box = 3;
	int choice, random = 1, ret_val;
	char c;
	data qcsort;

	init_sort_info(&qcsort); /* initialise number of swaps and comparisons to 0 */
	cbreak();
	init_pair(2, COLOR_RED, COLOR_BLACK);
	
	fp1 = fopen("files/quicksort.txt", "r");
	if(fp1 == NULL) {
		perror("open failed on file quicksort.txt");
		return errno;
	}	
	
	getmaxyx(stdscr, max_y, max_x); /* get the max dimensions of the screen */
	print_in_middle(stdscr, 3, 0, max_x, "QUICKSORT", COLOR_PAIR(3));
	
	start_y = max_y / 5;
	start_x = max_x / 4 + 4;
	print_intro(fp1, start_y, start_x); /* print the introduction page of Quicksort */
	
	instruction(max_y - 2, 0, "Press <ENTER> to CONTINUE or 'p' to return to the previous menu.");
	c = getch();
	if(c == 'p') {
		clear();
		curs_set(TRUE);
		return 0;
	}	
	else {
		(qcsort.comparisons)++; /* this is incremented as the partition function has a do...while */
		get_num_elem(&qcsort); /* get the number of elements to perform sorting on */
		clear();
		
		while(random != 0) { /* this loop is required because sometimes random function generates already sorted elements */
			random = num_generator(&qcsort); /* randomly generate 'elements' numbers and store in qcsort.numbers[elements] */
			message(max_y);
		}
		clear();
		
		print_in_middle(stdscr, 3, 0, max_x, "QUICKSORT", COLOR_PAIR(3));
		
		instruction(max_y - 3, 0, "Press <ENTER> to START.");
		instruction(max_y - 2, 0, "Press 'p' to go to the Main Menu.");
		curs_set(FALSE); /* curs_set(TRUE) shows a dirty cursor at top-left of the box */
		
		attron(A_BOLD);
		print_numbers(&qcsort, max_y, max_x);
		attroff(A_BOLD);
		win1 = NULL;
		choice = getch();
		if(choice == 'p') {
			clear();
			curs_set(TRUE);
			return 0;
		}	
		else if(choice == ENTER) { /* start the animation */
			move(max_y - 3, 0);
			clrtoeol();
			attron(A_BOLD);
			mvprintw(max_y - 12, 0, "RED: Current position of pivot.");
			mvprintw(max_y - 10, 0, "GREEN: Final position of element.");
			attroff(A_BOLD);
			instruction(max_y - 3, 0, "Press <Right Arrow Key> to proceed to the next step.");
			sleep(3);
			attron(A_BOLD);
			ret_val = quicksort_driver(qcsort.numbers, 0, qcsort.elements - 1, max_y, max_x, &qcsort, win1);
			if(ret_val == INT_MIN) { /* exit */
				clear();
				curs_set(TRUE);
				return 0;
			}	
			starty_of_box = (max_y - height_of_box) / 4 + 5;
			sleep(1);

			move(starty_of_box - 2, 0); /* to delete the letter 'i' which remains after the animation */
			clrtoeol();
			move(starty_of_box - 1, 0); /* to delete the letter 'j' which remains after the animation */
			clrtoeol();
			clear_boxes(starty_of_box); /* clear the boxes off the screen */
			move(max_y - 19, 0);
			clrtobot();
			attron(A_BOLD);
			mvprintw(max_y - 17, max_x / 4 + 15, "Yeah! The numbers are sorted!!");
			mvprintw(max_y - 13, max_x / 4 + 15, "Info:");
			mvprintw(max_y - 11, max_x / 4 + 15, "Number of swaps = %d", qcsort.swaps);
			mvprintw(max_y - 9, max_x / 4 + 15, "Number of comparisons = %d", qcsort.comparisons);
		}
		curs_set(TRUE);
		move(max_y - 5, 0);
		clrtobot();
		instruction(max_y - 2, 0, "Press any key to continue.\n");
		getch();
	}
	attroff(A_BOLD);
	fclose(fp1);
	return 0;
}
