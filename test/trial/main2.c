#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

WINDOW *create_newwin(int height_of_box, int width_of_box, int starty_of_box, int startx_of_box);
void destroy_win(WINDOW *local_win);
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);
void print_intro(FILE *fp, int cur_y, int cur_x);

int main(int argc, char *argv[]) {
	WINDOW *win1, *win2;
	FILE *fp1, *fp2;
	int startx_of_box, starty_of_box, width_of_box, height_of_box, max_x, max_y, cur_y, cur_x;  
	int ch, i, num[10];
	char c, info[64];
	
	fp1 = fopen("bubblesort", "r");
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
	//curs_set(FALSE);
	if(has_colors())
		start_color();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	getmaxyx(stdscr, max_y, max_x);
	attron(A_BOLD);
	print_in_middle(stdscr, 5, 0, max_x, "BUBBLE SORT", COLOR_PAIR(1));
	cur_y = max_y / 4;
	cur_x = max_x / 4 + 4;
	move(cur_y, cur_x);
	print_intro(fp1, cur_y, cur_x); 
	attroff(A_BOLD);
	mvprintw(LINES - 1, 0, "Press <ENTER> to continue or <F2> to exit");
	c = getch();
	if(c == KEY_F(2)) {
		mvprintw(0, 0, "IF ENT\n");
		refresh();
		clear();
		exit(0);
	}	
	else {
		clear();
		for(i = 0; i < 10; i++)
			fscanf(fp2, "%d", &num[i]);
		height_of_box = 3;
		width_of_box = 4;
		starty_of_box = (max_y - height_of_box) / 4;
		startx_of_box = max_x / 4 + 2; /*(COLS - width_of_box);*/

		mvprintw(max_y - 1, 0, "Press <BACKSPACE> to exit");

		win1 = create_newwin(height_of_box, width_of_box, starty_of_box, startx_of_box); /* -=2 */
		win2 = create_newwin(height_of_box, width_of_box, starty_of_box, startx_of_box += 8); /* +=3 */
		
		/*mvprintw((max_y / 4), (max_x / 4 + 10), " 5    1    3    7    9    0    6    2    4    8\n");
		*/
		move(max_y / 4, max_x / 4 + 10);
		printw(" ");
		for(i = 0; i < 10; i++)
			printw("%d    ", num[i]);
		printw("\n");
		move(starty_of_box, startx_of_box);
		refresh();
		wrefresh(win1);
		wrefresh(win2);
		while((ch = getch()) != KEY_BACKSPACE) {
			for(i = 0; i < 9; i++) {
				//mvprintw(max_y / 4, max_x / 4 + 10, " 5    1    3    7    9    0    6    2    4    8\n");
				//refresh();
				move(max_y / 4, max_x / 4 + 10);
				printw(" ");
				for(i = 0; i < 10; i++)
					printw("%d    ", num[i]);
				printw("\n");
				move(starty_of_box, startx_of_box);
				refresh();

				wrefresh(win1);
				wrefresh(win2);
				sleep(2); /* will produce a lag of 2 sec. */
				destroy_win(win1);
				destroy_win(win2);
				win1 = create_newwin(height_of_box, width_of_box, starty_of_box, startx_of_box); /* += 2 */
				win2 = create_newwin(height_of_box, width_of_box, starty_of_box, startx_of_box += 5);
			}
			//mvprintw(max_y / 4, max_x / 4 + 10, " 5    1    3    7    9    0    6    2    4    8\n");
			move(max_y / 4, max_x / 4 + 10);
			printw(" ");
			for(i = 0; i < 10; i++)
				printw("%d    ", num[i]);
			printw("\n");
			move(starty_of_box, startx_of_box);
			refresh();
		}
	}
	//getch();
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

WINDOW *create_newwin(int height_of_box, int width_of_box, int starty_of_box, int startx_of_box) {
	WINDOW *local_win;
	local_win = newwin(height_of_box, width_of_box, starty_of_box, startx_of_box);
	box(local_win, ' ', 0); /* second argument is a whitespace so that the number inside it gets displayed properly */ 
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
