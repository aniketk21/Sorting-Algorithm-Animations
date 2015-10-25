#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ncurses.h> 
#include <errno.h>
#define ENTER '\n'

int menu(FILE *f1, FILE *f2, char *a);

int main() {
	char msg[100];
	char ch;
	int row,col;
	FILE *f1, *f2;
	f1 = fopen("files/instr", "r");
	if(f1 == NULL) {
		perror("open failed on files/instr");
		return errno;
	}
	f2 = fopen("files/win_state", "w");
	if(f2 == NULL) {
		perror("open failed on files/instr");
		return errno;
	}
	initscr();
	raw();
	noecho();
	keypad(stdscr, TRUE);
	if(has_colors())
		start_color();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	getmaxyx(stdscr,row,col);
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
	if(ch == ENTER) {
 	/* go to next screen window */
		scr_dump("screen_state");
		//putwin(stdscr, f2);
		clear();
		fgetc(f1);
		menu(f1, f2, msg);
		refresh();
		getch();
	}
	else if(ch == KEY_BACKSPACE)
		clear();
	refresh();
	endwin();
	fclose(f1);
	fclose(f2);
	return 0;
}
