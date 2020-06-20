# Makefile do projeto. make all gera o executável e make clean remove os *.o e
# o executável.

all: lexico

lexico: lexico.o hashmap.o analisador_lexico.o
	gcc -g -o lexico -Wall lexico.o hashmap.o analisador_lexico.o

lexico.o: main.c hashmap.h analisador_lexico.h
	gcc -g -o lexico.o main.c -c -Wall

hashmap.o: hashmap.c hashmap.h
	gcc -g -o hashmap.o hashmap.c -c -Wall

analisador_lexico.o: analisador_lexico.c hashmap.h analisador_lexico.h main.o
	gcc -g -o analisador_lexico.o analisador_lexico.c -c -Wall

clean:
	rm -f *.o *~ lexico
