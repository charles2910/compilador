# Makefile do projeto. make all gera o executável e make clean remove os *.o e
# o executável.

all: main

main: main.o hashmap.o analisador_lexico.o
	gcc -o main -Wall main.o hashmap.o analisador_lexico.o

main.o: main.c hashmap.h analisador_lexico.h
	gcc -o main.o main.c -c -Wall

hashmap.o: hashmap.c hashmap.h
	gcc -o hashmap.o hashmap.c -c -Wall

analisador_lexico.o: analisador_lexico.c hashmap.h analisador_lexico.h main.o
	gcc -o analisador_lexico.o analisador_lexico.c -c -Wall

clean:
	rm -f *.o *~ main
