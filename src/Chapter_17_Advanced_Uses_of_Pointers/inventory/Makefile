main: node.o sllist.o main.o
	gcc -Wall -W -O -ansi -std=c11 -pedantic -o main node.o sllist.o main.o

main.o: main.c sllist.h node.h
	gcc -Wall -W -O -ansi -std=c11 -pedantic -c main.c

sllist.o: node.h sllist.h sllist.c
	gcc -Wall -W -O -ansi -std=c11 -pedantic -c sllist.c

node.o: node.h node.c
	gcc -Wall -W -O -ansi -std=c11 -pedantic -c node.c
