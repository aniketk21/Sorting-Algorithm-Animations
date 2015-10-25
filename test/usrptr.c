#include <curses.h>
#include <menu.h>
#include <string.h>
#include <stdlib.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 	4

char *choices[] = {
                        "Bubble sort",
                        "Quicksort",
                        "Selection sort",
                        "Choice 4",
			"Choice 5",
			"Choice 6",
			"Choice 7",
                        "Exit",
                  };
void func(char *name, FILE *fp);
void bsort(FILE *fp) {
	scr_dump("win_state");
	clear();
	printw("Welcome to Bubble Sort\n");
	getch();
	scr_restore("win_state");
	doupdate();
}
void qsort1(FILE *fp) {
	scr_dump("win_state");
	clear();
	printw("Welcome to Quicksort\n");
	getch();
	scr_restore("win_state");
	doupdate();
}
void ssort(FILE *fp) {
	scr_dump("win_state");
	clear();
	printw("Welcome to Selection Sort\n");
	getch();
	scr_restore("win_state");
	doupdate();
}
int main()
{	ITEM **my_items;
	int c;				
	MENU *my_menu;
        int n_choices, i;
	FILE *fp = fopen("win_state" ,"w");
	
	/* Initialize curses */	
	initscr();
	start_color();
        cbreak();
        noecho();
	keypad(stdscr, TRUE);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_MAGENTA, COLOR_BLACK);

	/* Initialize items */
        n_choices = ARRAY_SIZE(choices);
        my_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));
        for(i = 0; i < n_choices; ++i)
	{       my_items[i] = new_item(choices[i], choices[i]);
		/* Set the user pointer */
		set_item_userptr(my_items[i], func);
	}
	my_items[n_choices] = (ITEM *)NULL;

	/* Create menu */
	my_menu = new_menu((ITEM **)my_items);

	/* Post the menu */
	mvprintw(LINES - 3, 0, "Press <ENTER> to see the option selected");
	mvprintw(LINES - 2, 0, "Up and Down arrow keys to naviage (F1 to Exit)");
	post_menu(my_menu);
	refresh();

	while((c = getch()) != KEY_F(1))
	{       switch(c)
	        {	case KEY_DOWN:
				menu_driver(my_menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(my_menu, REQ_UP_ITEM);
				break;
			case 10: /* Enter */
			{	
				int index;
				ITEM *cur;
				void (*p)(char *);
				cur = current_item(my_menu);
				index = item_index(cur);
				p = item_userptr(cur);
				p((char *)item_name(cur));
				pos_menu_cursor(my_menu);
				if(index == 0)
					bsort(fp);
				else if(index == 1)
					qsort1(fp);
				else if(index == 2)
					ssort(fp);	
				break;
			}
			break;
		}
	}	
	unpost_menu(my_menu);
	for(i = 0; i < n_choices; ++i)
		free_item(my_items[i]);
	free_menu(my_menu);
	endwin();
	return 0;
}

void func(char *name, FILE *fp)
{	move(20, 0);
	clrtoeol();
	mvprintw(20, 0, "Item selected is : %s", name);
	/*if(!strcmp(name, "Bubble sort"))
		bsort(fp);
	if(!strcmp(name, "Quicksort"))
		qsort1(fp);
	if(!strcmp(name, "Selection sort"))
		ssort(fp);*/

}
