demo: main.o f1.o f2.o
	gcc -Wall -W -O -ansi -std=c11 -pedantic -o demo main.o f1.o f2.o

main.o: f1.h main.c
	gcc -Wall -W -O -ansi -std=c11 -pedantic -c main.c

f1.o: f1.h f2.h f1.c
	gcc -Wall -W -O -ansi -std=c11 -pedantic -c f1.c

f2.o: f1.h f2.h f2.c
	gcc -Wall -W -O -ansi -std=c11 -pedantic -c f2.c
