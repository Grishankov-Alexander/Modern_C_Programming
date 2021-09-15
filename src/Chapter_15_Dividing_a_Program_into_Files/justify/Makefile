justify: justify.o word.o line.o
	gcc -Wall -W -O -ansi -std=c11 -pedantic -o justify justify.o word.o line.o

justify.o: justify.c word.h line.h
	gcc -Wall -W -O -ansi -std=c11 -pedantic -c justify.c

word.o: word.h word.c
	gcc -Wall -W -O -ansi -std=c11 -pedantic -c word.c

line.o: line.h line.c
	gcc -Wall -W -O -ansi -std=c11 -pedantic -c line.c
