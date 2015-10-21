main: main.o menu.o
	cc main.o menu.o -Wall -lmenu -lncurses -o main
main.o: main.c
	cc -c -Wall main.c
bubblesort.o: bubblesort.c
	cc -c -Wall bubblesort.c
quicksort.o: quicksort.c
	cc -c -Wall quicksort.c
menu: menu.o
	cc menu.o -Wall -lmenu -lncurses -o menu
menu.o: menu.c
	cc -c -Wall menu.c

