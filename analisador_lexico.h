#define SIZE_TAB_RESERVADAS 37		/* Tamanho da tabela de palavras reservadas. */ 
#define BUFFER_SIZE 4096
/* Define os tokens */
#define PROGRAM				1
#define IDENT				2
#define PONTO_VIRGULA		3
#define PONTO				4
#define BEGIN				5
#define END					6
#define CONST				7
#define IGUAL				8
#define VAR					9
#define DOIS_PONTOS			10
#define REAL				11
#define INTEGER				12
#define VIRGULA				13
#define PROCEDURE			14
#define ABRE_PARENTESIS		15
#define FECHA_PARENTESIS	16
#define ELSE				17
#define READ				18
#define WRITE				19
#define WHILE				20
#define DO					21
#define IF					22
#define THEN				23
#define FOR					24
#define TO					25
#define DOIS_PONTOS_IGUAL	26
#define DIFERENTE			27
#define MAIOR_IGUAL			28
#define MENOR_IGUAL			29
#define MAIOR				30
#define MENOR				31
#define MAIS				32
#define MENOS				33
#define MULT				34
#define DIV					35
#define NUM_INTEIRO			36
#define NUM_REAL			37

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

/**
 * Função que procura por um token relativo à string passada como argumento,
 * caso não encontre, retorna NULL. Se encontrar, retorna struct par_token.
 */
par_token * get_par_token(char * );

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
par_token * get_token(char ** , int * );

/**
 * Verifica se o estado passado é um erro. Se sim, retorna 1. Caso contrário,
 * retorna 0.
 */
int is_error(int );

/**
 * Função que informa o erro léxico na tela. Em caso de sucesso, retorna 0.
 */
int relata_erro(int , char * , int );

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
