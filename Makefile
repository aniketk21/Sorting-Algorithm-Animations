main: main.o menu.o print_in_middle.o bubblesort.o selectionsort.o num_generator.o num_of_rows.o init_sort_info.o num_io.o print_intro.o windows.o
	cc main.o menu.o print_in_middle.o bubblesort.o selectionsort.o num_generator.o num_of_rows.o init_sort_info.o -Wall -lm -lmenu -lncurses num_io.o print_intro.o windows.o -o main
main.o: main.c
	cc -c -Wall main.c
bubblesort.o: bubblesort.c
	cc -c -Wall bubblesort.c
quicksort.o: quicksort.c
	cc -c -Wall quicksort.c
selectionsort.o : selectionsort.c
	cc -c -Wall selectionsort.c
menu.o: menu.c
	cc -c -Wall menu.c
print_in_middle.o: print_in_middle.c
	cc -c -Wall print_in_middle.c
num_generator.o: num_generator.c
	cc -c -Wall num_generator.c
num_of_rows.o: num_of_rows.c
	cc -c -Wall num_of_rows.c
init_sort_info.o: init_sort_info.c
	cc -c -Wall init_sort_info.c
num_io.o: num_io.c
	cc -c -Wall num_io.c
print_intro.o: print_intro.c
	cc -c -Wall print_intro.c
windows.o: windows.c
	cc -c -Wall windows.c
