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

int num_generator(data *p) {
	int i, max = 10, flag;
	time_t tt;
	
	p->numbers = (int *)malloc(p->elements * sizeof(int));
	if(p->numbers == NULL) {
		perror("malloc failed");
		return errno;
	}	
	srandom(time(&tt));
	for(i = 0; i < p->elements; i++) 
		p->numbers[i] = random() % max;
	for(i = 0; i < p->elements - 1; i++) { /* this loop checks if the random numbers generated are already in sorted order */
		if(p->numbers[i] <= p->numbers[i + 1])
			flag = 0;
		else
			flag = 1;
	}
	if(flag == 0)
		return 1;
	else
		return 0;
}

void message(int max_y) {
	mvprintw(max_y / 4, 0, "Generating random numbers...");
	refresh();
	return;
}
