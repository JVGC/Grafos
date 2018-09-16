objects = main.o matriz.o Dijikstra.o fila.o

all: $(objects)
	gcc -o main $(objects) -g -I.

main.o: main.c matriz.h
	gcc -c main.c

matriz.o: matriz.c matriz.h
	gcc -c matriz.c

Dijikstra.o: Dijikstra.c Dijikstra.h matriz.h 
	gcc -c Dijikstra.c  

fila.o:	fila.c fila.h
	gcc -c fila.c

clean:
	rm *.o main

zip:
	zip LAB5.zip main.c fila.h fila.c matriz.c matriz.h Dijikstra.h Dijikstra.c Makefile

run:
	./main
