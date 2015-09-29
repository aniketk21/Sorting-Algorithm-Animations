main: main.o
	cc main.o -Wall -lncurses -o main
main.o: main.c
	cc -c main.c
