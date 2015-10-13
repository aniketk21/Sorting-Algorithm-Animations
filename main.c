#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ncurses.h> 
#include <errno.h>

void menu1(FILE *f1, char *a);
int main(int argc, char *argv[]) {
	char mesg[100];
	char ch;
	int row,col;
	FILE *f1 = fopen(argv[1], "r");
	if(f1 == NULL) {
		perror("open failed");
		return errno;
	}
	initscr();
	raw();
	noecho();
	keypad(stdscr, TRUE);
	start_color();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	getmaxyx(stdscr,row,col);
	fscanf(f1, "%[^\n]", mesg);
	mvprintw(row/2,(col-strlen(mesg))/2,"%s",mesg);
 	mvchgat(row/2, (col-strlen(mesg))/2, -1, A_BLINK, 1, NULL);
	fgetc(f1);
	fscanf(f1, "%[^\n]", mesg);
	attron(A_STANDOUT);
	mvprintw(LINES - 2, 0, "%s\n",mesg);
	attroff(A_STANDOUT);
	ch = getch();
	if(ch == 'y') {
 	/* go to next screen window */
		clear();
		fgetc(f1);
		/*fscanf(f1, "%[^\n]", mesg);
		mvprintw(row / 4, (col - strlen(mesg)) / 2, "%s", mesg);*/
		menu1(f1, mesg);
		refresh();
		getch();
	}
	else if(ch == 'n') {
		clear();
		exit(0);
	}	
	refresh();
	endwin();
	fclose(f1);
 	return 0;
}
