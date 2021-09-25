dllist: dllist.o main.o
	gcc -Wall -W -O -ansi -std=c11 -pedantic -o dllist dllist.o main.o

main.o: dllist.h main.c
	gcc -Wall -W -O -ansi -std=c11 -pedantic -c main.c

dllist.o: dllist.h dllist.c
	gcc -Wall -W -O -ansi -std=c11 -pedantic -c dllist.c
