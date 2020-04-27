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
int load_file(char * file, char * buffer){
	if (!file)
		file = "meu_programa.txt";

	int buffer_size = 0;

	FILE *program = fopen(file, "r");

	if(!program){
		printf("Your file was not found");
		exit(EXIT_FAILURE);
	}

	buffer_size = fill_buffer(program, buffer);

	char * pos = buffer;
	while (*pos != NULL || (pos - buffer) < buffer_size) {
		printf("%c", *pos);
		// HERE WE'LL CALL THE LEXIC ANALIZER FUNCTION WITH 'LINE' PARAMETER 
		//line = read_file_line(program);
		pos++;
		
	}
	
	fclose(program);
	return buffer_size;
}

/**
 * Função que lê e retorna uma linha do arquivo aberto.
 */
int fill_buffer(FILE * program, char * buffer){
	char c, * pos;
	int buffer_size = 0;

	pos = buffer;

	while (c != EOF || buffer_size < BUFFER_SIZE - 1) {
		c = getc(program);
		if (feof(program))
			break;
		*pos = c;
		pos++;
		buffer_size++;
	}

	*pos = 0;
	buffer_size++;

	return buffer_size;
}

/**
 * Função que recebe o estado atual e o símbolo lido, calcula a transição
 * 							e retorna o novo estado.
 */
int get_next_state(int state, char simbolo) {
	if (state < 0 || simbolo < 0)
		return -1;

	simbolo -= 32;

	return table_of_transitions[state][(int) simbolo];
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

char * new_buffer() {
	char * buffer = (char *) malloc(BUFFER_SIZE);
	return buffer;
}

char * analise_lexica(char * buffer, char * posicao, int buffer_size) {
	int 	current_state = 0, 
		str_length = 0, 
		current_char = 1,
		should_rollback,
		final_state;

	char str[64];

	while(current_char) {
		current_char = *posicao;

		switch(current_char) {
			case 0: /* NULL indica fim do buffer */
				break;
			case 8: /* BS ou \b => deve ser consumido */
				if (str_length == 0) break;
			case 9: /* HT ou \t => deve ser consumido */
				if (str_length == 0) break;
			case 10: /* LF ou \n => deve ser consumido */
				if (str_length == 0) break;
			case 11: /* VT ou \v => deve ser consumido */
				if (str_length == 0) break;
			case 12: /* FF ou \f => deve ser consumido */
				if (str_length == 0) break;
			case 13: /* CR ou \r => deve ser consumido */
				if (str_length == 0) break;
		}
		
		posicao++;

		current_state = get_next_state(current_state, current_char);

		if (current_state == 98) {
			par_token token_erro2;
			token_erro2.string = (char) current_char;
			token_erro2.token = "erro(\"caractere não permitido\")";
			//print_token(token_erro2);
			return posicao;
		} else if (current_state == 99) {
			par_token token_erro1;
			token_erro1.string = (char) current_char;
			token_erro1.token = "erro(\"caractere não permitido\")";
			//print_token(token_erro1);
			return posicao;
		}

		//final_state = is_final_state(current_state);

		if (!final_state) {
			str_length++;
			continue;
		}

		//should_rollback = verify_rollback_state(current_state);

		printf("\n VOLTO?? %d\n", should_rollback);

		if (should_rollback) {
			posicao--;
			//str_length--;
		}

		if (str_length > 0) {
			for(int i = 0; i < str_length; i++) {
				str[i] = *(posicao - str_length + i);
			}
			str[str_length] = '\0';
		}

		par_token * final_par_token;

		switch (current_state) {
			case 11: /* é um identificador*/
				/*cria e printa par_token */
				break;
			case 12: /* é um número inteiro */
				/*cria e printa par_token */
				break;
			case 13: /* é um número real */
				/*cria e printa par_token */
				break;
			default:
				final_par_token = get_par_token(str);
				//print_token(final_par_token)
				break;
		}
	}
	printf("lexic\n");
	return posicao;
}
