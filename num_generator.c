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
		if(p->numbers[i] < p->numbers[i + 1])
			flag = 0;
		else
			flag = 1;
	}
	if(flag == 0)
		return 0;
	else
		return 1;
}										
