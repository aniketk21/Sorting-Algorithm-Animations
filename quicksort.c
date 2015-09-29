void quicksort(long a[], long first, long last) {
	long pivot, j, temp, i;
	if(first < last){
		pivot = first;
		i = first;
		j = last;
		while(i < j) {
			while(a[i] <= a[pivot] && i < last)
				i++;
			while(a[j] > a[pivot])
				j--;
			if(i < j) {
				temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}
		temp = a[pivot];
		a[pivot] = a[j];
		a[j] = temp;
		quicksort(a, first, j - 1);
		quicksort(a, j + 1, last);
	}
}
