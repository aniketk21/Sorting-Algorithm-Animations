main: main.o menu.o print_in_middle.o bubblesort.o
	cc main.o menu.o print_in_middle.o bubblesort.o -Wall -lm -lmenu -lncurses -o main
main.o: main.c
	cc -c -Wall main.c
bubblesort.o: bubblesort.c
	cc -c -Wall bubblesort.c
quicksort.o: quicksort.c
	cc -c -Wall quicksort.c
menu.o: menu.c
	cc -c -Wall menu.c
print_in_middle.o: print_in_middle.c
	cc -c -Wall print_in_middle.c
