#ifndef __ANALISADOR_LEXICO__
#define __ANALISADOR_LEXICO__

#define SIZE_TAB_RESERVADAS 37		/* Tamanho da tabela de palavras reservadas. */ 
#define BUFFER_SIZE 4096
#include "hashmap.h"
#include "stack.h"

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
	struct StackNode* stack;
	struct StackNode* stack_aux;
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

/**
 * Função que procura por um token relativo à string passada como argumento,
 * caso não encontre, retorna NULL. Se encontrar, retorna struct par_token.
 */
par_token * get_par_token(char *, map_t);


/**
 * Cria um novo buffer e retorna o endereço.
 */
char * new_buffer();

/**
 * Verifica se deve-se consumir o caracter. Se sim, retorna 1. Caso contrário,
 * retorna 0.
 */
int consumir(int * , int );

/**
 * Retorna o próximo token contido no buffer. No caso, retorna uma
 * struct par_token.
 */
par_token * get_token(controlador *);

/**
 * Verifica se o estado passado é um erro. Se sim, retorna 1. Caso contrário,
 * retorna 0.
 */
int is_error(int );

/**
 * Função que informa o erro léxico na tela. Em caso de sucesso, retorna 0.
 */
int relata_erro(int , char * , int, int);


/**
 * Verifica se o estado é de retorno. Se sim, retorna 1. Caso contrário,
 * retorna 0.
 */
int verify_rollback_state(int );

/**
 * Verifica se o estado é final. Se sim, retorna 1. Caso contrário,
 * retorna 0.
 */
int is_final_state(int );

/**
 * Função que printa o token na tela. Retorna 0 em sucesso e -1 caso contrário.
 */
int print_token(par_token * );

#endif __ANALISADOR_LEXICO__
