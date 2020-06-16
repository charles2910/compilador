#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashmap.h"
#include "analisador_lexico.h"

par_token tab_reservados[] = {
	{"program", "<PROGRAM>", 1},
	{"ident", "<IDENT>", 2},
	{";", "<PONTO_VIRGULA>", 3},
	{".", "<PONTO>", 4},
	{"begin", "<BEGIN>", 5},
	{"end", "<END>", 6},
	{"const", "<CONST>", 7},
	{"=", "<IGUAL>", 8},
	{"var", "<VAR>", 9},
	{":", "<DOIS_PONTOS>", 10},
	{"real", "<REAL>", 11},
	{"integer", "<INTEGER>", 12},
	{",", "<VIRGULA>", 13},
	{"procedure", "<PROCEDURE>", 14},
	{"(", "<ABRE_PARENTESIS>", 15},
	{")", "<FECHA_PARENTESIS>", 16},
	{"else", "<ELSE>", 17},
	{"read", "<READ>", 18},
	{"write", "<WRITE>", 19},
	{"while", "<WHILE>", 20},
	{"do", "<DO>", 21},
	{"if", "<IF>", 22},
	{"then", "<THEN>", 23},
	{"for", "<FOR>", 24},
	{"to", "<TO>", 25},
	{":=", "<DOIS_PONTOS_IGUAL>", 26},
	{"<>", "<DIFERENTE>", 27},
	{">=", "<MAIOR_IGUAL>", 28},
	{"<=", "<MENOR_IGUAL>", 29},
	{">", "<MAIOR>", 30},
	{"<", "<MENOR>", 31},
	{"+", "<MAIS>", 32},
	{"-", "<MENOS>", 33},
	{"*", "<MULT>", 34},
	{"/", "<DIV>", 35},
	{"num_inteiro", "<NUM_INTEIRO>", 36},
	{"num_real", "<NUM_REAL>", 37},
	{"{", "<ABRE_CHAVE>", 38},
	{"}", "<FECHA_CHAVE>", 39}
};


int table_of_transitions[9][94] = {
    { 0, 98, 98, 98, 98, 98, 98, 98, 19, 20, 29, 27, 18, 28, 16, 21,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  2, 17,  3, 32,  4, 98, 98,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 98, 98, 98, 98, 98, 98,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  8, 98, 97},
	{11, 98, 98, 98, 98, 98, 98, 98, 11, 11, 11, 11, 11, 11, 11, 11,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 11, 11, 11, 11, 11, 98, 98,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 98, 98, 98, 98, 98, 98,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 11, 98, 97},
	{15, 98, 98, 98, 98, 98, 98, 98, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 14, 15, 98, 98, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 98, 98, 98, 98, 98, 98, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 98, 97},
	{25, 98, 98, 98, 98, 98, 98, 98, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 26, 24, 98, 98, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 98, 98, 98, 98, 98, 98, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 98, 97},
	{23, 98, 98, 98, 98, 98, 98, 98, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 22, 23, 98, 98, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 98, 98, 98, 98, 98, 98, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 98, 97},
	{12, 98, 98, 98, 98, 98, 98, 98, 12, 12, 12, 12, 12, 12,  6, 12,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5, 12, 12, 12, 12, 12, 98, 98, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 98, 98, 98, 98, 98, 98, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 12, 98, 97},
	{99, 98, 98, 98, 98, 98, 98, 98, 99, 99, 99, 99, 99, 99, 99, 99,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 99, 99, 99, 99, 99, 98, 98, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 98, 98, 98, 98, 98, 98, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 98, 97},
	{13, 98, 98, 98, 98, 98, 98, 98, 13, 13, 13, 13, 13, 13, 13, 13,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 13, 13, 13, 13, 13, 98, 98, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 13, 13, 99, 99, 99, 99, 98, 98, 98, 98, 98, 98, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 13, 98, 97},
	{ 8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  0}
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
 * e retorna o novo estado.
 */
int get_next_state(int state, char simbolo) {
	if (state < 0)
		return -1;
	if (simbolo < 0 && state != 8)
		return 0;
	else if (simbolo < 0)
		return 8;
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

int consumir(int * current_char, int str_length) {
	int consome = 0;
	switch(*current_char) {
		case 0: /* NULL indica fim do buffer */
			break;
		case 8: /* BS ou \b => deve ser consumido */
			if (str_length == 0)
				consome = 1;
			else
				*current_char = (char) 32;
			break;
		case 9: /* HT ou \t => deve ser consumido */
			if (str_length == 0)
				consome = 1;
			else
				*current_char = (char) 32;
			break;
		case 10: /* LF ou \n => deve ser consumido */
			if (str_length == 0)
				consome = 1;
			else
				*current_char = (char) 32;
			break;
		case 11: /* VT ou \v => deve ser consumido */
			if (str_length == 0)
				consome = 1;
			else
				*current_char = (char) 32;
			break;
		case 12: /* FF ou \f => deve ser consumido */
			if (str_length == 0)
				consome = 1;
			else
				*current_char =  (char) 32;
			break;
		case 13: /* CR ou \r => deve ser consumido */
			if (str_length == 0)
				consome = 1;
			else
				*current_char = (char) 32;
			break;
		case 32: /* (espaço) => deve ser consumido */
			if (str_length == 0)
				consome = 1;
			break;
	}

	if (current_char < 0)
		consome = 1;

	return consome;
}


char * analise_lexica(char * buffer, char * posicao, int buffer_size) {
	int 	current_state = 0, 
		str_length = 0, 
		current_char = 1,
		should_rollback = 0,
		final_state = 0,
		consome = 0,
		erro = 0;

	char str[64], caracter[2], caracter2[3];

	while(current_char) {
		current_char = *posicao;

		consome = consumir(&current_char, str_length);

		/* Checagem para ver se não é um símbolo q não pertence à linguagem */
		if(((current_char > 32 && current_char < 40) || current_char == 63 || current_char == 64 || current_char == 124 || current_char == 126 || (current_char > 90 && current_char < 97)) &&(str_length > 0)) {
			current_char = 32;
		}

		posicao++;
		if (current_state == 8)
			consome = 0;

		if (consome) {
			if (current_char < 0)
				str_length++;
			consome = 0;
			continue;
		}

		current_state = get_next_state(current_state, current_char);

		erro = is_error(current_state);

		if (erro) {
			relata_erro(current_state, posicao, str_length);
			return posicao;
		}

		final_state = is_final_state(current_state);

		if (!final_state) {
			if ((!consome && current_state != 8)) {
				if (current_state != 8 && current_char == 125)
					continue;
				str_length++;
			}
			continue;
		}

		str_length++;

		should_rollback = verify_rollback_state(current_state);

		if (should_rollback) {
			posicao--;
			str_length--;
			if(current_state == 1)
				str_length++;
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
				final_par_token = get_par_token(str);
				if (!final_par_token) {
					final_par_token = (par_token *) malloc(sizeof(par_token));
					final_par_token->string = str;
					final_par_token->token = "<IDENT>";
				}
				print_token(final_par_token);
				return posicao;
			case 12: /* é um número inteiro */
				final_par_token = (par_token *) malloc(sizeof(par_token));
				final_par_token->string = str;
				final_par_token->token = "<NUM_INTEIRO>";
				print_token(final_par_token);
				return posicao;
				break;
			case 13: /* é um número real */
				final_par_token = (par_token *) malloc(sizeof(par_token));
				final_par_token->string = str;
				final_par_token->token = "<NUM_REAL>";
				print_token(final_par_token);
				return posicao;
				break;
		}

		if (str_length > 1) {
			strncpy(caracter2, str, 3);
			final_par_token = get_par_token(caracter2);
			print_token(final_par_token);
			return posicao;
		} else {
			strncpy(caracter, str, 2);
			final_par_token = get_par_token(caracter);
			print_token(final_par_token);
			return posicao;
		}
	}
	return posicao;
}

int is_error(int state) {
	int error_states[] = {97, 98, 99};
	for(int i = 0; i <  3; i++){
		if(error_states[i] == state)
			return 1;
	}
	return 0;
}

int relata_erro(int state, char * posicao, int str_length) {
	char str[64];
	if (state == 97) {
		par_token * token_erro1 = (par_token *) malloc(sizeof(par_token));
		str[0] = (char) *(posicao - 1);
		str[1] = '\0';
		token_erro1->string = (char *) calloc(sizeof(char), 2);
		strncpy(token_erro1->string, str, 2);
		token_erro1->token = "erro(\"fecha chaves deve vir após abre chaves\")";
		print_token(token_erro1);
		return 0;
	} else if (state == 98) {
		par_token * token_erro1 = (par_token *) malloc(sizeof(par_token));
		str[0] = (char) *(posicao - 1);
		str[1] = '\0';
		token_erro1->string = (char *) calloc(sizeof(char), 2);
		strncpy(token_erro1->string, str, 2);
		token_erro1->token = "erro(\"caractere não permitido\")";
		print_token(token_erro1);
		return 0;
	} else if (state == 99) {
		par_token * token_erro2 = (par_token *) malloc(sizeof(par_token));
		str_length++;
		for(int i = 0; i < str_length; i++) {
			str[i] = *(posicao - str_length + i);
		}
		str[str_length] = '\0';
		token_erro2->string = str;
		token_erro2->token = "erro(\"Má formação de número\")";
		print_token(token_erro2);
		return 0;
	}
}

int verify_rollback_state(int state)
{
	int roll_back_states[6] = {11, 12, 13, 15, 23, 25};
	int i;
	for(i = 0; i <  6; i++){
		if(roll_back_states[i] == state)
			return 1;
	}
	return 0;
}

int is_final_state(int state)
{
	return (state >= 11 && state <= 32);
}

int print_token(par_token * par) {
	if (!par)
		return -1;
	printf("%s, %s\n", par->string, par->token);
	return 0;
}
