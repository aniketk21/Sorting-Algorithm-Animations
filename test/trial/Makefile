m2: main2.o print_in_middle.o
	cc main2.o print_in_middle.o -lncurses -o m2
main: main.o print_in_middle.o
	cc main.o print_in_middle.o -lncurses -Wall -o main
print_in_middle.o: print_in_middle.c
	cc -c -Wall print_in_middle.c
main.o: main.c 
	cc -c -Wall main.c
main2.o: main2.c
	cc -c -Wall main2.c
