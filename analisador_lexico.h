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

par_token * get_token(char * , char ** , int );

int is_error(int );

int relata_erro(int , char * , int );

int verify_rollback_state(int );

int is_final_state(int );

int print_token(par_token * );
