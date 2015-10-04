#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ncurses.h> 
int main() {
	char mesg[]="SORTING ALGORITHM DEMOS";
	char ch;
	int row,col;
	initscr();
	raw();
	noecho();
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	getmaxyx(stdscr,row,col);
	mvprintw(row/2,(col-strlen(mesg))/2,"%s",mesg);
 	mvchgat(row/2, (col-strlen(mesg))/2, -1, A_BLINK, 1, NULL);
	attron(A_STANDOUT);
	mvprintw(LINES - 2, 0, "Press 'y' to continue, 'n' to exit\n");
	attroff(A_STANDOUT);
	ch = getch();
	if(ch == 'y') {
 	/* go to next screen window */
		clear();
		strcpy(mesg, "Which sorting algorithms to demonstrate?\n");
		mvprintw(row / 4, (col - strlen(mesg)) / 2, "%s", mesg);
		refresh();
		getch();
	}
	else if(ch == 'n') {
		clear();
		exit(0);
	}	
	refresh();
	endwin();

 	return 0;
}
