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

void print_intro(FILE *fp, int start_y, int start_x) { /* prints the introduction page of the sorting algorithm */
	char desc[64];
	int y, x, cnt = 0, rows_in_file;
	y = start_y;
	x = start_x;
	move(y, x);
	rows_in_file = num_of_rows(fp); /* num_of_rows returns the number of rows in a file */
	rewind(fp); /* num_of_rows function takes the curses to EOF, so rewind() the file pointer */
	attron(A_BOLD);
	while(cnt < rows_in_file) {
		fscanf(fp, "%[^\n]", desc);
		fgetc(fp); /* eat the '\n' */
		mvprintw(y, x, "%s", desc);
		y++;
		cnt++;
	}
	refresh();
	attroff(A_BOLD);
}
