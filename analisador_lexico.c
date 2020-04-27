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


// Qf1 => Q11, Qf2 = Q12, Qf3 = Q13 e assim sucessivamente
// Q98 = QErro1, Q99 = QErro2
//  .    ;   ,   (   )   /  >   +   -   *   {    }  :  <  a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, $,  @,  #,  =

int tableOfTransitions[8][80] = {
    {16, 17, 18, 19, 20, 21, 4, 27, 28, 29, 30, 31, 2, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 98, 98, 98, 32},
	{11, 11, 11, 11, 11, 11,11, 11, 11, 11, 11, 11,11,11, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 98, 98, 98, 21},
	{15, 15, 15, 15, 15, 15,15, 15, 15, 15, 15, 15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15, 98, 98, 98, 14},
	{25, 25, 25, 25, 25, 25,24, 25, 25, 25, 25, 25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25, 98, 98, 98, 26},
	{23, 23, 23, 23, 23, 23,23, 23, 23, 23, 23, 23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23, 98, 98, 98, 22},
	{ 6, 22, 22, 22, 22, 22,22, 22, 22, 22, 22, 22,22,22,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 98, 98, 98, 22},
	{99, 99, 99, 99, 99, 99,99, 99, 99, 99, 99, 99,23,23,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,26, 7, 7, 7, 7, 7, 7, 7, 7, 7, 98, 98, 98, 99},
	{13, 13, 13, 13, 13, 13,13, 13, 13, 13, 13, 13,13,13,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 98, 98, 98, 13}
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

	return tableOfTransitions[state][simbolo];
}

par_token * get_par_token(char * string) {
	if (!string)
		return NULL;
}	
