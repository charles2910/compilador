#ifndef __ANALISADOR_SINTATICO_H__
#define __ANALISADOR_SINTATICO_H__

#include "analisador_lexico.h"
#include "analisador_sintatico.h"
#include "stack.h"

#define SIZE_TAB_TOKENS 32		/* Tamanho da tabela de tokens. */ 

#define PROGRAM "<PROGRAM>"
#define IDENT "<IDENT>"
#define PONTO_VIRGULA "<PONTO_VIRGULA>"
#define PONTO "<PONTO>"
#define BEGIN "<BEGIN>"
#define END "<END>"
#define CONST "<CONST>"
#define IGUAL "<IGUAL>"
#define VAR "<VAR>"
#define DOIS_PONTOS "<DOIS_PONTOS>"
#define REAL "<REAL>"
#define INTEGER "<INTEGER>"
#define VIRGULA "<VIRGULA>"
#define PROCEDURE "<PROCEDURE>"
#define ABRE_PARENTESIS "<ABRE_PARENTESIS>"
#define FECHA_PARENTESIS "<FECHA_PARENTESIS>"
#define ELSE "<ELSE>"
#define READ "<READ>"
#define WRITE "<WRITE>"
#define WHILE "<WHILE>"
#define DO "<DO>"
#define IF "<IF>"
#define THEN "<THEN>"
#define FOR "<FOR>"
#define TO "<TO>"
#define DOIS_PONTOS_IGUAL "<DOIS_PONTOS_IGUAL>"
#define DIFERENTE "<DIFERENTE>"
#define MAIOR_IGUAL "<MAIOR_IGUAL>"
#define MENOR_IGUAL "<MENOR_IGUAL>"
#define MAIOR "<MAIOR>"
#define MENOR "<MENOR>"
#define MAIS "<MAIS>"
#define MENOS "<MENOS>"
#define MULT "<MULT>"
#define DIV "<DIV>"
#define NUM_INTEIRO "<NUM_INTEIRO>"
#define NUM_REAL "<NUM_REAL>"

#define CASE_FOR 24
#define CASE_BEGIN 5
#define CASE_WRITE 19
#define CASE_READ 18
#define CASE_WHILE 20
#define CASE_IF 22
#define CASE_IDENT 0

typedef struct {
	char * token;
	char * primeiros;
	char * seguidores;
} table_tokens_seguidores_primeiros;

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


int is_token_a_first_of(char* token, controlador *);
int is_token_a_follower_of(char * token, controlador * compilador);

/**
 * Função inclui no hashmap o token com seu Primeiro e Seguidor. Retorna 0 em sucesso.
 */
int populate_hashmap_tokens_seguidores_primeiros(map_t in); 

int compare_token(char* token, controlador *);

int consume_terminal(char* token, controlador *);

void get_token_from_lexic(controlador *);
void error_procedure(char* token, controlador* compilador);

void start(int argc, char* argv[]);

void program(controlador *);

void body(controlador *);

void dc(controlador *);

void dc_c(controlador *);

void dc_v(controlador *);

void dc_p(controlador *);

int var_type(controlador *);

void number(controlador *);

int variables(controlador *);

void parameters(controlador *);

void program_body(controlador *);

void list_arg(controlador *);

void commands(controlador *);

void cmd(controlador *);

void atribuition(controlador *);

void condition(controlador *);

void expression(controlador *);

int term(controlador *);

int factor(controlador *);

#endif __ANALISADOR_SINTATICO_H__
