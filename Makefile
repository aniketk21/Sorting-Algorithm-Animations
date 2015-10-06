main: main.o
	cc main.o -Wall -lncurses -o main
main.o: main.c
	cc -c -Wall main.c
bubblesort.o: bubblesort.c
	cc -c -Wall bubblesort.c
quicksort.o: quicksort.c
	cc -c -Wall quicksort.c
menu1: menu1.o
	cc menu1.o -Wall -lmenu -lncurses -o menu1
menu1.o: menu1.c
	cc -c -Wall menu1.c

