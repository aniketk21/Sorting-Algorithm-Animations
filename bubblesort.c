void bubblesort(long a[], long size) {
	int i, j, temp, swapped = 1;
	for(i = 0; swapped && i < size - 1; i++) {
		swapped = 0;
		for(j = 0; j < size - 1; j++) {
			if(a[j] > a[j + 1]) {
				temp = a[j + 1];
				a[j + 1] = a[j];
				a[j] = temp;
				swapped++;
			}	

		}
	}
}
