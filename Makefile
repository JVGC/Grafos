# Compilador gcc
CP = gcc
# Parâmetros de compilação
P_CO = -c -lm -g3 -std=gnu99

main: UC.o  main.o 
	$(CP) UC.o main.o -o main 

all: UC.o  main.o 
	$(CP) UC.o main.o -o main 

UC.o: UC.c
	$(CP) $(P_CO) UC.c

main.o: main.c UC.o
	$(CP) $(P_CO) main.c

run: main
	./main < entrada.txt
clean: 
	rm -rf *o main

clean_all:	
	rm -rf *o