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

void box_over_num(int l, WINDOW *win, int max_y, int max_x, int height_of_box, int width_of_box, int color_pair) {
	int starty_of_box, startx_of_box;
	starty_of_box = (max_y - height_of_box) / 4 + 5;
	startx_of_box = max_x / 4 + 10 + 5 * l;
	win = create_newwin(height_of_box, width_of_box, starty_of_box, startx_of_box);
	wbkgd(win, COLOR_PAIR(color_pair));
	wrefresh(win);
}
