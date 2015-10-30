#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#define ENTER '\n'

WINDOW *create_newwin(int height_of_box, int width_of_box, int starty_of_box, int startx_of_box);
void destroy_win(WINDOW *local_win);
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);
void print_intro(FILE *fp, int cur_y, int cur_x);
void print_numbers(int *num, int max_y, int max_x);

int main(int argc, char *argv[]) {
	WINDOW *win1, *win2;
	FILE *fp1, *fp2;
	int startx_of_box, starty_of_box, width_of_box, height_of_box, max_x, max_y, cur_y, cur_x;  
	int ch, i, num[10], j, orig_x_of_box, temp, iter_no = 1, inner_iter = 9, swapped = 1;
	char c;
	
	fp1 = fopen("bubblesort.txt", "r");
	if(fp1 == NULL) {
		perror("open failed on bubblesort");
		return errno;
	}	
	
	fp2 = fopen("num.txt", "r");
	if(fp2 == NULL) {
		perror("open failed on num.txt");
		return errno;
	}

	initscr();
	cbreak();
	keypad(stdscr, TRUE);
	curs_set(FALSE);
	if(has_colors())
		start_color();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	getmaxyx(stdscr, max_y, max_x);
	attron(A_BOLD);
	print_in_middle(stdscr, 5, 0, max_x, "BUBBLE SORT", COLOR_PAIR(1));
	cur_y = max_y / 4;
	cur_x = max_x / 4 + 4;
	move(cur_y, cur_x);
	print_intro(fp1, cur_y, cur_x); /* print the introduction page of Bubble Sort */
	attroff(A_BOLD);
	attron(A_REVERSE);
	mvprintw(LINES - 2, 0, "Press <ENTER> to CONTINUE or 'n' to EXIT");
	attroff(A_REVERSE);
	c = getch();
	if(c == 'n') {
		clear();
	}	
	else {
		clear();
		
		attron(A_BOLD);
		print_in_middle(stdscr, 3, 0, max_x, "BUBBLE SORT", COLOR_PAIR(1));
		attroff(A_BOLD);
		
		for(i = 0; i < 10; i++)
			fscanf(fp2, "%d", &num[i]);
		
		height_of_box = 3;
		width_of_box = 4;
		starty_of_box = (max_y - height_of_box) / 4 + 5; // + 5;
		startx_of_box = max_x / 4 + 2;
		
		attron(A_REVERSE);
		mvprintw(max_y - 3, 0, "Press <ENTER> to START");
		/******* Previous menu option *********/
		mvprintw(max_y - 2, 0, "Press 'n' to EXIT");
		attroff(A_REVERSE);
		win1 = create_newwin(height_of_box, width_of_box, starty_of_box, startx_of_box);
		startx_of_box += 8;
		orig_x_of_box = startx_of_box;
		win2 = create_newwin(height_of_box, width_of_box, starty_of_box, startx_of_box);
		attron(A_BOLD);
		print_numbers(num, max_y, max_x);
		attroff(A_BOLD);
		ch = getch();
		if(ch == ENTER) {
			move(max_y - 3, 0);
			clrtoeol();
			attron(A_REVERSE);
			mvprintw(max_y - 3, 0, "Press Right Arrow Key to go to the next step");
			attroff(A_REVERSE);
			sleep(1);
			attron(A_BOLD);
			refresh();
			for(j = 0; swapped && j < 9; j++) {
				sleep(1);
				swapped = 0;
				mvprintw(max_y / 4, (max_x - 19) / 2,"Iteration number: %d", iter_no);
				for(i = 0; i < inner_iter; i++) {
					sleep(1);
					print_numbers(num, max_y, max_x);
					destroy_win(win1);
					destroy_win(win2);
					print_numbers(num, max_y, max_x);
					win1 = create_newwin(height_of_box, width_of_box, starty_of_box, startx_of_box);
					win2 = create_newwin(height_of_box, width_of_box, starty_of_box, startx_of_box += 5);
					if(num[i] > num[i + 1]) {
						print_numbers(num, max_y, max_x);
						sleep(1);
						move(max_y - 19, 0);
						clrtoeol();
						mvprintw(max_y - 19, max_x / 4 + 18, "Element %d is greater than %d.", num[i], num[i + 1]);
						move(max_y - 17, 0);
						clrtoeol();
						mvprintw(max_y - 17, max_x / 4 + 18, "Hence %d and %d get swapped.", num[i], num[i + 1]);
						refresh(); /* for printing immediately on the screen */
						temp = num[i];
						num[i] = num[i + 1];
						num[i + 1] = temp;
						sleep(2);
						print_numbers(num, max_y, max_x);
						swapped++;
					}
					else {
						print_numbers(num, max_y, max_x);
						move(max_y - 19, 0);
						clrtoeol();
						mvprintw(max_y - 19, max_x / 4 + 18, "Element %d is not greater than %d.", num[i], num[i + 1]);
						move(max_y - 17, 0);
						clrtoeol();
						mvprintw(max_y - 17, max_x / 4 + 18, "Hence these two elements don't get swapped");
						refresh();
						sleep(1);
					}
					print_numbers(num, max_y, max_x);
					/*destroy_win(win1);
					destroy_win(win2);
					move(max_y / 4 + 5, max_x / 4 + 10);
					printw(" ");
					for(k = 0; k < 10; k++)
						printw("%d    ", num[k]);
					refresh();
					win1 = create_newwin(height_of_box, width_of_box, starty_of_box, startx_of_box);
					win2 = create_newwin(height_of_box, width_of_box, starty_of_box, startx_of_box += 5);*/
					//ch = getch();
					/*if(ch == 'n') {
						clear();
						wclear(win1);
						wclear(win2);
						delwin(win1);
						delwin(win2);*/
						/* go to main menu */ /***********IMPORTANT**************/
					//	endwin();
					//	return 0;
				//	}
				}
				inner_iter--;
				iter_no++;
				print_numbers(num, max_y, max_x);
				destroy_win(win1);
				destroy_win(win2);
				win1 = create_newwin(height_of_box, width_of_box, starty_of_box, orig_x_of_box);
				startx_of_box = orig_x_of_box;
				win2 = create_newwin(height_of_box, width_of_box, starty_of_box, orig_x_of_box + 5);
				wrefresh(win1);
				wrefresh(win2);
				print_numbers(num, max_y, max_x);
				//sleep(1);
			}
			print_numbers(num, max_y, max_x);
		}
		move(max_y - 19, 0);
		clrtobot();
		mvprintw(max_y - 10, max_x / 4 + 15, "No swap took place in the previous iteration");
		mvprintw(max_y - 9, max_x / 4 + 15, "this indicates that the numbers are sorted.");	
		attroff(A_BOLD);
		move(max_y - 4, 0);
		clrtobot();
		curs_set(TRUE);
		mvprintw(max_y - 2, 0, "Press any key to continue");
		getch();
	}
	delwin(win1);
	delwin(win2);
	endwin();
	fclose(fp1);
	fclose(fp2);
	return 0;
}

void print_intro(FILE *fp, int cur_y, int cur_x) {
	char desc[64];
	int y, x, cnt;
	y = cur_y;
	x = cur_x;
	cnt = 0;
	while(cnt < 20) {
		fscanf(fp, "%[^\n]", desc);
		fgetc(fp);
		mvprintw(y, x, "%s", desc);
		y++;
		cnt++;
	}
	refresh();
}

void print_numbers(int *num, int max_y, int max_x) {
	short int k;
	move(max_y / 4 + 5, max_x / 4 + 10);
	printw(" ");
	for(k = 0; k < 10; k++)
		printw("%d    ", num[k]);
	refresh();
}	

WINDOW *create_newwin(int height_of_box, int width_of_box, int starty_of_box, int startx_of_box) {
	WINDOW *local_win;
	local_win = newwin(height_of_box, width_of_box, starty_of_box, startx_of_box);
	box(local_win, 0, 0); /* second argument is a whitespace so that the number inside it gets displayed properly */ 
	wrefresh(local_win);
	return local_win;
}

void destroy_win(WINDOW *local_win) {	
	/* box(local_win, ' ', ' '); : This won't produce the desired
	 * result of erasing the window. It will leave it's four corners 
	 * and so an ugly remnant of window. 
	 */
	wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	/* The parameters taken are 
	 * 1. win: the window on which to operate
	 * 2. ls: character to be used for the left side of the window 
	 * 3. rs: character to be used for the right side of the window 
	 * 4. ts: character to be used for the top side of the window 
	 * 5. bs: character to be used for the bottom side of the window 
	 * 6. tl: character to be used for the top left corner of the window 
	 * 7. tr: character to be used for the top right corner of the window 
	 * 8. bl: character to be used for the bottom left corner of the window 
	 * 9. br: character to be used for the bottom right corner of the window
	 */
	wrefresh(local_win);
	delwin(local_win);
}
