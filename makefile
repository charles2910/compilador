# Makefile do projeto. make all gera o executável e make clean remove os *.o e
# o executável.

all: main

main: main.o hashmap.o analisador_lexico.o analisador_sintatico.o
	gcc -g -o main -Wall main.o hashmap.o analisador_lexico.o analisador_sintatico.o

main.o: main.c hashmap.h analisador_lexico.h
	gcc -g -o main.o main.c -c -Wall

hashmap.o: hashmap.c hashmap.h
	gcc -g -o hashmap.o hashmap.c -c -Wall

analisador_sintatico.o: analisador_sintatico.c analisador_sintatico.h
	gcc -g -o analisador_sintatico.o analisador_sintatico.c -c -Wall

analisador_lexico.o: analisador_lexico.c hashmap.h analisador_lexico.h main.o
	gcc -g -o analisador_lexico.o analisador_lexico.c -c -Wall

clean:
	rm -f *.o *~ main
