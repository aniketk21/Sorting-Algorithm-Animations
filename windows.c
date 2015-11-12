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

/* create_newwin creates a window of specifies dimensions */
WINDOW *create_newwin(int height_of_box, int width_of_box, int starty_of_box, int startx_of_box) {
	WINDOW *local_win;
	local_win = newwin(height_of_box, width_of_box, starty_of_box, startx_of_box);
	box(local_win, 0, 0); /* second argument is a whitespace so that the number inside it gets displayed properly */ 
	wrefresh(local_win);
	return local_win;
}

void destroy_win(WINDOW *local_win) { /* this function destroys a window */
	/* box(local_win, ' ', ' '); : This won't produce the desired
	 * result of erasing the window. It will leave it's four corners 
	 * and so an ugly remnant of window. 
	 */
	wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
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

void clear_boxes(int starty_of_box) {
	move(starty_of_box, 0);
	clrtoeol();
	move(starty_of_box + 2, 0);
	clrtoeol();
}	
