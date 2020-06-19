#ifndef __ANALISADOR_LEXICO__
#define __ANALISADOR_LEXICO__

#define SIZE_TAB_RESERVADAS 37		/* Tamanho da tabela de palavras reservadas. */ 
#define BUFFER_SIZE 4096
#include "hashmap.h"

typedef struct {
	char * string;
	char * token;
	int id;
} par_token;

typedef struct {
	char * buffer;
	char * posicao;
	int size;
} controlador;

/**
 * Função inclui no hashmap as palavras reservadas. Retorna 0 em sucesso.
 */
int populate_hashmap(map_t );

/**
 * Função que carrega um arquivo fonte passado como parâmetro.
 */
int load_file(char * , char * );

/**
 * Função que lê e retorna uma linha do arquivo aberto.
 */
int fill_buffer(FILE * , char * );

/**
 * Função que recebe o estado atual e o símbolo lido, calcula a transição
 * e retorna o novo estado.
 */
int get_next_state(int , char );

par_token * get_par_token(char * );

char * new_buffer();

int consumir(int * , int );

par_token * get_token(char ** , int * );

int is_error(int );

int relata_erro(int , char * , int );

int verify_rollback_state(int );

int is_final_state(int );

int print_token(par_token * );

#endif __ANALISADOR_LEXICO__
