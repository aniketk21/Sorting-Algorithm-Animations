#include <stdio.h>
void bubblesort(int a[], int size) {
	int i, j, k, temp;
	printf("Numbers are\n");
	for(k = 0; k < size; k++)
		printf(" %d ", a[k]);
	printf("\n");	
	for(i = 0; i < size - 1; i++) {
		for(j = 0; j < size - 1; j++) {
			if(a[j] > a[j + 1]) {
				temp = a[j + 1];
				a[j + 1] = a[j];
				a[j] = temp;
			}
		}
		getchar();
		for(k = 0; k < size; k++)
			printf(" %d " , a[k]);
		printf("\n");	
	}
}
