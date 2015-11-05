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

int main() {
	char msg[100];
	char ch;
	FILE *f1;
	f1 = fopen("files/intro.txt", "r");
	if(f1 == NULL) {
		perror("open failed on files/intro.txt");
		return errno;
	}
	initscr(); /* initialise curses mode */
	raw();
	noecho(); /* echoing of characters is turned off */
	keypad(stdscr, TRUE);
	if(has_colors())
		start_color();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	ch = start(msg, f1);	
	if(ch == ENTER) { /* go to next screen window */
		clear();
		fgetc(f1);
		menu(f1, msg); /* print the menu */
		refresh();
	}
	else if(ch == KEY_BACKSPACE)
		clear();
	refresh();
	endwin();
	fclose(f1);
	return 0;
}

char start(char *msg, FILE *f1) {
	char ch;
	int row, col;
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	getmaxyx(stdscr, row, col);
	fscanf(f1, "%[^\n]", msg);
	mvprintw(row / 2, (col - strlen(msg)) / 2,"%s", msg);
	mvchgat(row/2, (col-strlen(msg))/2, -1, A_BOLD, 1, NULL);
	fgetc(f1);
	fscanf(f1, "%[^\n]", msg);
	attron(A_REVERSE);
	mvprintw(row - 2, 0, "%s\n",msg);
	attroff(A_REVERSE);
	refresh();
	ch = getch();
	return ch;
}
