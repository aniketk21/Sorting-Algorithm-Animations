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

int main(int argc, char *argv[]) {
	if(argc > 1) {
		printf("Usage: ./<executable file name>\n\n");
		return 0;
	}	
	char ch;
	
	initscr(); /* initialise curses mode */
	raw();
	noecho(); /* echoing of characters is turned off */
	keypad(stdscr, TRUE);
	if(has_colors())
		start_color();
	init_pair(1, COLOR_CYAN, COLOR_BLACK); /* initialise colour pairs */
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	
	ch = start();	
	if(ch == ENTER) { /* start the program */
		clear();
		menu(); /* print the menu and proceed */
	}
	else if(ch == KEY_BACKSPACE) /* exit */
		clear();
	
	refresh();
	endwin(); /* end curses mode */
	printf("\nThanks!\n");
	return 0;
}

char start(void) {
	char choice;
	int row, col;
	
	getmaxyx(stdscr, row, col); /* get max dimensions of the screen */
	print_in_middle(stdscr, row / 2, 0, col, "SORTING ALGORITHM ANIMATIONS", COLOR_PAIR(1));
	
	instruction(row - 2, 0, "Press <ENTER> to continue or <BACKSPACE> to exit.");
	choice = getch();
	return choice;
}
