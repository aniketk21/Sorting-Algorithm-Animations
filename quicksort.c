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

#include <stdio.h>

void quickSort( int[], int, int);
int partition( int[], int, int);


int main() 
{
	int a[] = { 7, 12, 1, -2, 0, 15, 4, 11, 9};

	int i;
	printf("\n\nUnsorted array is:  ");
	for(i = 0; i < 9; ++i)
		printf(" %d ", a[i]);
	printf("\n");
	quickSort( a, 0, 8);

	printf("\n\nSorted array is:  ");
	for(i = 0; i < 9; ++i)
		printf(" %d ", a[i]);
	return 0;
}



void quickSort( int a[], int l, int r) {
   int j, i;
   for(i = 0; i < 9; ++i)
		printf(" %d ", a[i]);
	printf("\n");
   if( l < r ) {
   	// divide and conquer
       j = partition( a, l, r);
       quickSort( a, l, j-1);
       quickSort( a, j+1, r);
   }
}



int partition( int a[], int l, int r) {
   int pivot, i, j, t;
   pivot = a[l];
   i = l; j = r+1;
   while(1) {
   	do ++i; 
		while( a[i] <= pivot && i <= r );
   	do --j; 
		while( a[j] > pivot );
   	if( i >= j ) 
		break;
	printf("\nNow %d and %d get swapped\n", a[i], a[j]);
   	t = a[i]; 
	a[i] = a[j]; 
	a[j] = t;
   }
	printf("\nNow pivot:%d and %d get swapped\n", a[l], a[j]);
	t = a[l]; 
	a[l] = a[j]; 
	a[j] = t;
   return j;
}
