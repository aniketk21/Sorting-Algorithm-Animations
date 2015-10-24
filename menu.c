/* Prints menu:
 * 1. Bubble Sort
 * 2. Quicksort
 * 3. Selection Sort
 */
#include <menu.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

char *choices[] = {
                        "1. Bubble Sort",
                        "2. Quicksort",
                        "3. Selection Sort",
                        (char *)NULL,
                  };

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);

void info_on_sort(WINDOW *win, FILE *f2);

int menu(FILE *f1, char *a)
{	ITEM **my_items;
	int c, y, x;
	FILE *f2;
	MENU *menu;
        WINDOW *menu_win, *info_win;
        int n_choices, i;
	const char *ch = NULL;
	
	f2 = fopen("files/sort_info", "r");
	if(f2 == NULL) {
		perror("open failed on file sort_info");
		return errno;
	}	
	fscanf(f1, "%[^\n]", a);
	
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	
	/* Create items */
        n_choices = ARRAY_SIZE(choices);
        my_items = (ITEM **)calloc(n_choices, sizeof(ITEM *));
        for(i = 0; i < n_choices; ++i)
		my_items[i] = new_item(choices[i], ch);

	y = ceil(0.3658 * LINES); /* For placing the menu box at the center */
	x = ceil(0.3472 * COLS);
	
	/* Create menu */
	menu = new_menu((ITEM **)my_items);

	/* Create the window to be associated with the menu */
        menu_win = newwin(10, 40, y, x);
	//info_win = newwin(20, 60, 4, 60);
	//keypad(info_win, TRUE);
	keypad(menu_win, TRUE);

        /* Set main window and sub window */
        set_menu_win(menu, menu_win);
        set_menu_sub(menu, derwin(menu_win, 6, 38, 3, 1));

	/* Set menu mark to the string " > " */
        set_menu_mark(menu, " > ");
	
	/* Print a border around the window and print a title for menu_win and info_win */
        box(menu_win, 0, 0);
	print_in_middle(menu_win, 1, 0, 40, "SELECT ONE", COLOR_PAIR(1));
	mvwaddch(menu_win, 2, 0, ACS_LTEE);
	mvwhline(menu_win, 2, 1, ACS_HLINE, 38);
	mvwaddch(menu_win, 2, 39, ACS_RTEE);
	
	/*box(info_win, 0, 0);
	print_in_middle(info_win, 1, 0, 60, "DESCRIPTION", COLOR_PAIR(1));
	mvwaddch(info_win, 2, 0, ACS_LTEE);
	mvwhline(info_win, 2, 1, ACS_HLINE, 58);
	mvwaddch(info_win, 2, 59, ACS_RTEE);
	info_on_sort(info_win, f2);*/

	mvprintw(LINES - 2, 0, "%s\n", a);
	fgetc(f1);
	fscanf(f1, "%[^\n]", a);
	mvprintw(LINES - 1, 0, "%s\n", a);
	refresh();
        
	/* Post the menu */
	post_menu(menu);
	wrefresh(menu_win);

	while((c = wgetch(menu_win)) != KEY_F(2))
	{       switch(c)
	        {	case KEY_DOWN:
				menu_driver(menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(menu, REQ_UP_ITEM);
				break;
		}
                wrefresh(menu_win);
	}	

	/* Unpost and free all the memory taken up */
        unpost_menu(menu);
        free_menu(menu);
        for(i = 0; i < n_choices; ++i)
                free_item(my_items[i]);
	fclose(f2);
	return 0;
}

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color)
{	int length, x, y;
	float temp;

	if(win == NULL)
		win = stdscr;
	getyx(win, y, x);
	if(startx != 0)
		x = startx;
	if(starty != 0)
		y = starty;
	if(width == 0)
		width = 80;

	length = strlen(string);
	temp = (width - length)/ 2;
	x = startx + (int)temp;
	wattron(win, color);
	mvwprintw(win, y, x, "%s", string);
	wattroff(win, color);
	refresh();
}

void info_on_sort(WINDOW *win, FILE *f2) {
	char c;
	short int i = 0, cnt_nl = 0;
	int count = 0;
	wmove(win, 3, 2);
	wrefresh(win);
	while(!feof(f2)) {
		c = fgetc(f2);
		if(c == '2' || c == '3') {
			wmove(win, cnt_nl + 4, 2); 
			wrefresh(win);
		}
		if(c == '\n') {
			wmove(win, count + i + 3, 2); /*i+cnt+3*/
			wrefresh(win);
			i++;
			cnt_nl++;
		}	
		wprintw(win, "%c", c);
		count++;
	}
}
