#include <stdio.h>
#include <stdlib.h>

#include "hashmap.h"
#include "analisador_lexico.h"

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


int table_of_transitions[8][94] = {
    { 0, 98, 98, 98, 98, 98, 98, 98, 19, 20, 29, 27, 18, 28, 16, 21,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  2, 17,  3, 32,  4, 98, 98,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 98, 98, 98, 98, 98, 98,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 30, 98, 31},
	{11, 98, 98, 98, 98, 98, 98, 98, 11, 11, 11, 11, 11, 11, 11, 11,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 11, 11, 11, 11, 11, 98, 98,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 98, 98, 98, 98, 98, 98,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 11, 98, 11},
	{15, 98, 98, 98, 98, 98, 98, 98, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 14, 15, 98, 98, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 98, 98, 98, 98, 98, 98, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 98, 15},
	{25, 98, 98, 98, 98, 98, 98, 98, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 26, 24, 98, 98, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 98, 98, 98, 98, 98, 98, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 98, 25},
	{23, 98, 98, 98, 98, 98, 98, 98, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 22, 23, 98, 98, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 98, 98, 98, 98, 98, 98, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 98, 23},
	{12, 98, 98, 98, 98, 98, 98, 98, 12, 12, 12, 12, 12, 12,  6, 12,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5, 12, 12, 12, 12, 12, 98, 98, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 98, 98, 98, 98, 98, 98, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 12, 98, 12},
	{99, 98, 98, 98, 98, 98, 98, 98, 99, 99, 99, 99, 99, 99, 99, 99,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 99, 99, 99, 99, 99, 98, 98, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 98, 98, 98, 98, 98, 98, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 98, 99},
	{13, 98, 98, 98, 98, 98, 98, 98, 13, 13, 13, 13, 13, 13, 13, 13,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 13, 13, 13, 13, 13, 98, 98, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 13, 13, 99, 99, 99, 99, 98, 98, 98, 98, 98, 98, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 98, 99}
};


/**
 * Função inclui no hashmap as palavras reservadas. Retorna 0 em sucesso.
 */
int populate_hashmap(map_t in) {
	int ok = 0;

	for(int i = 0; i < SIZE_TAB_RESERVADAS; i++) {
		ok = hashmap_put(in, tab_reservados[i].string, &(tab_reservados[i]));
		if(ok) {
			printf("Erro em adicionar %d palavra no hashmap.\n", i);
			return -1;
		}
	}
	
	return 0;
}

/**
 * Função que carrega um arquivo fonte passado como parâmetro.
 */
void load_file(char * file){
	char file_name[] = "meu_programa.txt";
	char * line = NULL;

	FILE *program = fopen(file_name, "r");

	if(program == NULL){
		printf("Your file was not found");
		exit(EXIT_FAILURE);
	}

	line = read_file_line(program);
	while (line != NULL){
		printf("%s", line);
		// HERE WE'LL CALL THE LEXIC ANALIZER FUNCTION WITH 'LINE' PARAMETER 
		line = read_file_line(program);
	}
	
	fclose(program);
	free(line);
	free(program);

}

/**
 * Função que lê e retorna uma linha do arquivo aberto.
 */
char * read_file_line(FILE* program){
	char * temp_line = NULL;
	__ssize_t line_size;
  	size_t line_buf_size = 0;

	line_size = getline(&temp_line, &line_buf_size, program);

	if(line_size > 0)
		return temp_line;
	
	free(temp_line);
	return NULL;
}

/**
 * Função que recebe o estado atual e o símbolo lido, calcula a transição
 * 							e retorna o novo estado.
 */
int get_next_state(int state, char simbolo) {
	if (state < 0 || simbolo < 0)
		return -1;

	simbolo -= 32;

	return table_of_transitions[state][simbolo];
}

par_token * get_par_token(char * string) {
	extern map_t map;
	if (!string) {
		printf("\nErro em get_par_token: parâmetro string nulo.\n");
		return NULL;
	} else if (!map) {
		printf("\nErro em get_par_token: parâmetro map nulo.\n");
		return NULL;
	}
	
	par_token * par;
	int erro = hashmap_get(map, string, &par);

	if (erro)
		return NULL;
	else
		return par;
}	
