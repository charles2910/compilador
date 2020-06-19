#define SIZE_TAB_TOKENS 37		/* Tamanho da tabela de tokens. */ 

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
#define CASE_IDENT 2

typedef struct {
	char * token;
	char * primeiros;
	char * seguidores;
} table_tokens_seguidores_primeiros;
