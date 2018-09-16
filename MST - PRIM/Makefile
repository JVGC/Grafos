objects = main.o matriz.o PRIM.o fila.o

all: $(objects)
	gcc -o main $(objects) -g -I.

main.o: main.c matriz.h
	gcc -c main.c

matriz.o: matriz.c matriz.h
	gcc -c matriz.c

PRIM.o: PRIM.c PRIM.h matriz.h 
	gcc -c PRIM.c  

fila.o:	fila.c fila.h
	gcc -c fila.c

clean:
	rm *.o main

zip:
	zip LAB4.zip main.c fila.h fila.c matriz.c matriz.h PRIM.h PRIM.c Makefile

run:
	./main
