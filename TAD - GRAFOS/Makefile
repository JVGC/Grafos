objects = main.o matriz.o listaADJ.o lista.o

all: $(objects)
	gcc -o main $(objects) -g -I.

main.o: main.c matriz.h
	gcc -c main.c

matriz.o: matriz.c matriz.h
	gcc -c matriz.c

lista.o: lista.h lista.c
	gcc -c lista.c

listaADJ.o: listaADJ.c matriz.h lista.h
	gcc -c listaADJ.c	

clean:
	rm *.o main


run:
	./main