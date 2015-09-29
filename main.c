#include <stdio.h>
#include <string.h>
#include <ncurses.h> 
int main()
{
 char mesg[]="Sorting Algorithms";		/* message to be appeared on the screen */
 char ch;
 int row,col;				/* to store the number of rows and *
					 * the number of colums of the screen */
 initscr();				/* start the curses mode */
 getmaxyx(stdscr,row,col);		/* get the number of rows and columns */
 mvprintw(row/2,(col-strlen(mesg))/2,"%s",mesg);
                     		/* print the message at the center of the screen */
 mvprintw(LINES - 2, 0, "Press ENTER to continue, ESC to exit\n");
 ch = getch();
 if(ch == 'CR') {
 	/* go to next screen window ... */
 }
 if(ch == 'ESC')	
 refresh();
 endwin();

 return 0;
}
