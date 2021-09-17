inventory: main.o part.o inventory.o readln.o
	gcc -Wall -W -O -ansi -std=c11 -pedantic -o inventory main.o part.o inventory.o readln.o

main.o: main.c inventory.h readln.h part.h
	gcc -Wall -W -O -ansi -std=c11 -pedantic -c main.c

inventory.o: inventory.h inventory.c part.h
	gcc -Wall -W -O -ansi -std=c11 -pedantic -c inventory.c

part.o: part.h part.c
	gcc -Wall -W -O -ansi -std=c11 -pedantic -c part.c

readln.o: readln.h readln.c
	gcc -Wall -W -O -ansi -std=c11 -pedantic -c readln.c
