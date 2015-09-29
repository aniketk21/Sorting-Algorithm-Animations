main: main.o
	cc main.o -Wall -lncurses -o main
main.o: main.c
	cc -c -Wall main.c
bubblesort.o: bubblesort.c
	cc -c -Wall bubblesort.c
quicksort.o: quicksort.c
	cc -c -Wall quicksort.c		
