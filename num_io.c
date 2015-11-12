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

void print_numbers(data *p, int max_y, int max_x) { /* print the numbers */
	short int k;
	move(max_y / 4 + 5, max_x / 4 + 10);
	printw(" ");
	for(k = 0; k < p->elements; k++)
		printw("%d    ", p->numbers[k]);
	refresh();
}

void get_num_elem(data *p) { /* this function is to get from the user the number of elements to perform sorting on */
	echo();
	attron(A_BOLD);
	while(1) {
		clear();
		mvprintw(1, 0, "Enter the number of elements to perform sorting on [Min: 2, Max: 10] and then press <ENTER> ");
		scanw("%d", &p->elements);
		refresh();
		if((p->elements >= 2) && (p->elements <= 10))
			return;
		else {
			clear();
			mvprintw(1, 0, "Enter a number between 2 & 10...\nPress any key to continue...");
			refresh();
			getch();
		}
	}
	attroff(A_BOLD);
	noecho();
}
