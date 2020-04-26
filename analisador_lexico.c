#include <stdio.h>
#include <stdlib.h>

#include "hashmap.h"

#define SIZE_TAB_RESERVADAS 39		/* Tamanho da tabela de palavras reservadas. */ 

typedef struct {
	char * string;
	char * token;
} par_token;

par_token tab_reservados[] = {
	{"program", "<PROGRAM>"},
	{"ident", "<IDENT>"},
	{";", "<PONTO_VIRGULA>"},
	{".", "<PONTO>"},
	{"begin", "<BEGIN>"},
	{"end", "<END>"},
	{"const", "<CONST>"},
	{"=", "<IGUAL>"},
	{"var", "<VAR>"},
	{":", "<DOIS_PONTOS"},
	{"real", "<REAL>"},
	{"integer", "<INTEGER>"},
	{",", "<VIRGULA>"},
	{"procedure", "<PROCEDURE>"},
	{"(", "<ABRE_PARENTESIS>"},
	{")", "<FECHA_PARENTESIS>"},
	{"else", "<ELSE>"},
	{"read", "<READ>"},
	{"write", "<WRITE>"},
	{"while", "<WHILE>"},
	{"do", "<DO>"},
	{"if", "<IF>"},
	{"then", "<THEN>"},
	{"for", "<FOR>"},
	{"to", "<TO>"},
	{":=", "<DOIS_PONTOS_IGUAL>"},
	{"<>", "<DIFERENTE>"},
	{">=", "<MAIOR_IGUAL>"},
	{"<=", "<MENOR_IGUAL>"},
	{">", "<MAIOR>"},
	{"<", "<MENOR>"},
	{"+", "<MAIS>"},
	{"-", "<MENOS>"},
	{"*", "<MULT>"},
	{"/", "<DIV>"},
	{"num_inteiro", "<NUM_INTEIRO>"},
	{"num_real", "<NUM_REAL>"},
	{"{", "<ABRE_CHAVE>"},
	{"}", "<FECHA_CHAVE>"}
};

/**
 * Função inclui no hashmap as palavras reservadas. Retorna 0 em sucesso.
 */
int populate_hashmap(map_t in) {
	int ok = 0;

	for(int i = 0; i < SIZE_TAB_RESERVADAS; i++) {
		ok = hashmap_put(in, tab_reservados[i].string, &(tab_reservados[i]));
		if(!ok) {
			printf("Erro em adicionar %d palavra no hashmap.\n", i);
			return -1;
		}
	}
	
	return 0;
}
