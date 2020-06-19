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


#ifndef __CONTROLADOR__
#define __CONTROLADOR__
typedef struct {
	map_t map_par_token;
    map_t map_tokens_seguidores_primeiros;
	par_token * current_token;
	int line;
	char * posicao;
	char * buffer;
} controlador;
#endif

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

par_token * get_par_token(char *, map_t);

char * new_buffer();

int consumir(int * , int );

par_token * get_token(controlador *);

int is_error(int );

int relata_erro(int , char * , int );

int verify_rollback_state(int );

int is_final_state(int );

int print_token(par_token * );

#endif __ANALISADOR_LEXICO__
