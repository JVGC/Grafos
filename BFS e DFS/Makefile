objects = main.o matriz.o busca.o fila.o

all: $(objects)
	gcc -o main $(objects) -g -I.

main.o: main.c matriz.h
	gcc -c main.c

matriz.o: matriz.c matriz.h
	gcc -c matriz.c

busca.o: matriz.h busca.c busca.h fila.h
	gcc -c busca.c

fila.o:	fila.c fila.h
	gcc -c fila.c

clean:
	rm *.o main

zip:
	zip LAB2.zip main.c fila.h fila.c matriz.c matriz.h busca.h busca.c Makefile

run:
	./main