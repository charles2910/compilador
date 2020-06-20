# Makefile do projeto. make all gera o executável e make clean remove os *.o e
# o executável.

all: sintatico

sintatico: main.c analisador_lexico.c analisador_lexico.h analisador_sintatico.c analisador_sintatico.h hashmap.c hashmap.h stack.c stack.h
	gcc -g -o sintatico main.c analisador_lexico.c analisador_sintatico.c hashmap.c stack.c

clean:
	rm -f *.o *~ sintatico
