#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "analisador_lexico.h"
#include "analisador_sintatico.h"
#include "hashmap.h"
#include "stack.h"

struct StackNode* root = NULL; 
struct StackNode* root_aux = NULL; 

table_tokens_seguidores_primeiros tabela[] = {
    {"<PROGRAMA>", "<PROGRAM>", "λ"},
    {"<CORPO>", "<CONST> <VAR> <PROCEDURE> <BEGIN> λ", "<PONTO>"},
    {"<DC>", "<CONST> <VAR> <PROCEDURE> λ", "<BEGIN>"},
    {"<DC_C>", "<CONST> λ", "<VAR>  <PROCEDURE>  <BEGIN>"},
    {"<DC_V>", "<VAR> λ", "<PROCEDURE>  <BEGIN>"},
    {"<DC_P>", "<PROCEDURE> λ", "<BEGIN>"},
    {"<DC_LOC>", "<VAR> λ", "<BEGIN>"},
    {"<TIPO_VAR>", "<REAL> <INTEGER>", "<PONTO_VIRGULA>  <ABRE_PARENTESIS>"},
    {"<VARIAVEIS>", "<IDENT>", "<DOIS_PONTOS>  <ABRE_PARENTESIS>"},
    {"<MAIS_VAR>", ", λ", "<DOIS_PONTOS>  <ABRE_PARENTESIS>"},
    {"<PARAMETROS>", "<ABRE_PARENTESIS> λ", "<PONTO_VIRGULA>"},
    {"<LISTA_PAR>", "<IDENT>", "<ABRE_PARENTESIS>"},
    {"<MAIS_PAR>", "<PONTO_VIRGULA> λ", "<ABRE_PARENTESIS>"},
    {"<CORPO_P>", "<VAR> λ <BEGIN>", "<PROCEDURE>  <BEGIN>"},
    {"<LISTA_ARG>", "<ABRE_PARENTESIS> λ", "<PONTO_VIRGULA>"},
    {"<ARGUMENTOS>", "<IDENT>", "<ABRE_PARENTESIS>"},
    {"<MAIS_IDENT>", "<PONTO_VIRGULA> λ", "<ABRE_PARENTESIS>"},
    {"<PFALSA>", "<ELSE> λ", "<PONTO_VIRGULA>"},
    {"<COMANDOS>", "<READ> <WRITE> <WHILE> <IF> <IDENT> <BEGIN> <FOR>", "<END>"},
    {"<CMD>", "<READ> <WRITE> <WHILE> <IF> <IDENT> <BEGIN> <FOR>", "<PONTO_VIRGULA>"},
    {"<CONDICAO>", "<MAIS>  <MENOS>  <IDENT> <NUM_INTEIRO> <NUM_REAL> <ABRE_PARENTESIS>", "<ABRE_PARENTESIS>  <THEN>"},
    {"<ATRIBUICAO>", "<ABRE_PARENTESIS> λ <DOIS_PONTOS_IGUAL>", "<PONTO_VIRGULA>"},
    {"<RELACAO>", "<IGUAL>  <DIFERENTE>  <MAIOR_IGUAL>  <MENOR_IGUAL>  <MAIOR>  <MENOR>", "<MAIS>  <MENOS>  <IDENT> <NUM_INTEIRO> <NUM_REAL> <ABRE_PARENTESIS>"},
    {"<EXPRESSAO>", "<MAIS> <MENOS> <IDENT> <NUM_INTEIRO> <NUM_REAL> <ABRE_PARENTESIS>", "<IGUAL> <DIFERENTE> <MAIOR_IGUAL> <MENOR_IGUAL> <MAIOR> <MENOR> <ABRE_PARENTESIS> <THEN>"},
    {"<OP_UN>", "<MAIS> <MENOS> λ", "<IDENT> <NUM_INTEIRO> <NUM_REAL> <ABRE_PARENTESIS>"},
    {"<OUTROS_TERMOS>" ," <MAIS> <MENOS> ", " <IGUAL>  <DIFERENTE>  <MAIOR_IGUAL>  <MENOR_IGUAL>  <MAIOR>  <MENOR>  <ABRE_PARENTESIS>  <THEN>"},
    {"<OP_AD>" ," <MAIS> <MENOS> ", " <MAIS>  <MENOS>  <IDENT>  <NUM_INTEIRO> <NUM_REAL>  <ABRE_PARENTESIS>"},
    {"<TERMO>" ," <MAIS>  <MENOS>  <IDENT>  <NUM_INTEIRO> <NUM_REAL>  <ABRE_PARENTESIS> ", " <MAIS> <MENOS>"},
    {"<MAIS_FATORES>" ," <MULT> <DIV> ", " <MAIS> <MENOS>"},
    {"<OP_MUL>" ," <MULT> <DIV> ", " <IDENT>  <NUM_INTEIRO> <NUM_REAL>  <ABRE_PARENTESIS>"},
    {"<FATOR>" ," <IDENT>  <NUM_INTEIRO> <NUM_REAL>  <ABRE_PARENTESIS> ", " <MULT> <DIV>"},
    {"<NUMERO>" ," <NUM_INTEIRO> <NUM_REAL> ", " <MULT> <DIV>"}
};



int is_token_a_first_of(char * token, controlador * compilador) {
    if(!compilador->current_token) return 0;
	char* primeiros;

	table_tokens_seguidores_primeiros* tabela_seguidores_primeiros;
	int erro = hashmap_get(compilador->map_tokens_seguidores_primeiros, token, &tabela_seguidores_primeiros);

	if (erro)
		return 0;

	primeiros = tabela_seguidores_primeiros->primeiros;
	char *pch = strstr(primeiros, compilador->current_token->token);
	return pch ? 1 : 0;
}

int is_token_a_follower_of(char * token, controlador * compilador) {
	char* followers;

	table_tokens_seguidores_primeiros* tabela_seguidores_primeiros;
	int erro = hashmap_get(compilador->map_tokens_seguidores_primeiros, token, &tabela_seguidores_primeiros);

	if (erro)
		return 0;

	followers = tabela_seguidores_primeiros->seguidores;
	char *pch = strstr(followers, compilador->current_token->token);
	return pch ? 1 : 0;
}

/**
 * Função inclui no hashmap o token com seu Primeiro e Seguidor. Retorna 0 em sucesso.
 */
int populate_hashmap_tokens_seguidores_primeiros(map_t in) {
	int ok = 0;

	for(int i = 0; i < SIZE_TAB_TOKENS; i++) {
		ok = hashmap_put(in, tabela[i].token, &(tabela[i]));
		if(ok) {
		 	printf("Erro em adicionar %d palavra no hashmap.\n", i);
		 	return -1;
		}
	}
	return 0;
}

int compare_token(char* token, controlador * compilador){
    if(!compilador->current_token) return 0;
    // printf("%s, %s\n", compilador->current_token->string, compilador->current_token->token);
    return strcmp(token, compilador->current_token->token) == 0 ? 1 : 0;
}

int consume_terminal(char* token, controlador * compilador){
    // consome um token terminal e vê se é o token esperado com base no parametro token passado (o current token é global)
    if(!compilador->current_token) return 0;
    int result = compare_token(token, compilador);
    if(!result){
        error_procedure(token, compilador);
        return 0;
    }
    get_token_from_lexic(compilador);
    return 1;
}

void get_token_from_lexic(controlador * compilador){
    compilador->current_token = get_token(compilador);
	// Em caso de erro léxico, busca o próximo token
	if (!compilador->current_token) {
		compilador->current_token = get_token(compilador);
	}
}

void error_procedure(char* token, controlador* compilador){
    printf("%d: Erro -> esperava: %s -- recebi: %s\n", compilador->line, token, compilador->current_token->token);
    struct StackNode* temp_stack;
    // while is not the end of the file
    while (compilador->current_token != NULL)
    {
        temp_stack = compilador->stack_aux;
        if(temp_stack == NULL){ // if got in the end of the stack
            get_token_from_lexic(compilador);

            if(compilador->current_token == NULL)
                return;

            compilador->stack_aux = compilador->stack;
            temp_stack = compilador->stack_aux;
        }

        int is_follower = is_token_a_follower_of(tabela[temp_stack->data].token, compilador);
        if(is_follower){ // if found a follower, current_token is the follower and temp_stack is the new stack
            compilador->stack = temp_stack;
            break;
        }
        pop_from_stack_aux(compilador);
    }
}

int push_compilador(int value, controlador* compilador) {
    push(&root, value);
    push(&root_aux, value);
    compilador->stack = peek(root);
    compilador->stack_aux = peek(root_aux);
}

int pop_from_stack_aux(controlador* compilador) {
    pop(&root_aux);
    if(isEmpty(root_aux)){
        compilador->stack_aux = NULL;
        return;
    }
    compilador->stack_aux = peek(root_aux);
}
void pop_from_stack(controlador* compilador){
    pop(&root);
    if(isEmpty(root)){
        compilador->stack = NULL;
        return;
    }
    compilador->stack = peek(root);
}

void start(int argc, char* argv[]){
    controlador * compilador = (controlador *) malloc(sizeof(controlador));

    /* Inicialização do hashmap */
	compilador->map_par_token = hashmap_new();
	compilador->map_tokens_seguidores_primeiros = hashmap_new();
	populate_hashmap_par_token(compilador->map_par_token);
	populate_hashmap_tokens_seguidores_primeiros(compilador->map_tokens_seguidores_primeiros);

	/* Inicialização do Buffer */
	compilador->buffer = new_buffer();
	if (!compilador->buffer) {
		printf("Erro na criação do buffer.\n");
		return;
	}
	/* Verifica se devemos utilizar o arquivo de teste, ou um fornecido
								pelo usuário */
	char * arquivo = NULL;
	if(argc > 1)
		arquivo = argv[1];
	int size = load_file(arquivo, compilador->buffer);

	compilador->line = 0;

	compilador->posicao = compilador->buffer;
	//while (posicao != (buffer + size)) {
    // get_token(&posicao, &line);
    get_token_from_lexic(compilador);
    program(compilador);
    return;
}

void program(controlador * compilador){
    // if(!is_token_a_first_of("<PROGRAMA>", compilador)){
    //     // printf(compilador->current_token->string);
    //     //seguidor de pai e o proximo depois dele, tipo id
    //     return;
    // }

    push_compilador(0, compilador);

    if(!consume_terminal(PROGRAM, compilador))
        return;

    if(!consume_terminal(IDENT, compilador))
        return;

    if(!consume_terminal(PONTO_VIRGULA, compilador))
        return;

    body(compilador);
    
    if(!consume_terminal(PONTO, compilador))
        return;
    pop_from_stack(compilador);
}

void body(controlador * compilador){
    if(!is_token_a_first_of("<CORPO>", compilador)){
        return;
    }

    push_compilador(1, compilador);

    dc(compilador);

    if(!consume_terminal(BEGIN,compilador))
        return;

    commands(compilador);

    if(!consume_terminal(END, compilador))
        return;
    pop_from_stack(compilador);
}

void dc(controlador * compilador){
    if(!is_token_a_first_of("<DC>", compilador))
        return;

    push_compilador(2, compilador);
    dc_c(compilador);
    dc_v(compilador);
    dc_p(compilador);
    pop_from_stack(compilador);
}

void dc_c(controlador * compilador){
    if(!is_token_a_first_of("<DC_C>", compilador))
        return;

    push_compilador(3, compilador);

    if(!consume_terminal(CONST, compilador)){
        return;
    }
    if(!consume_terminal(IDENT, compilador)){
        return;
    }
    if(!consume_terminal(IGUAL, compilador)){
        return;
    }
    number(compilador);
    if(!consume_terminal(PONTO_VIRGULA, compilador)){
        return;
    }

    dc_c(compilador);
    pop_from_stack(compilador);
}

void dc_v(controlador * compilador){
    if(!is_token_a_first_of("<DC_V>", compilador))
        return;

    push_compilador(4, compilador);
    if(!consume_terminal(VAR, compilador))
        return;

    if(!variables(compilador)){
        error_procedure(IDENT, compilador);
        return;
    }

    if(!consume_terminal(DOIS_PONTOS, compilador))
        return;
    
    if(!var_type(compilador))
        return;

    if(!consume_terminal(PONTO_VIRGULA, compilador))
        return;

    dc_v(compilador);
    pop_from_stack(compilador);
}

void dc_p(controlador * compilador){
    if(!is_token_a_first_of("<DC_P>", compilador))
        return;

    push_compilador(5, compilador);
    if(!consume_terminal(PROCEDURE, compilador))
        return;

    if(!consume_terminal(IDENT, compilador))
        return;

    parameters(compilador);

    if(!consume_terminal(PONTO_VIRGULA, compilador))
        return;

    program_body(compilador);

    // get_token_from_lexic(compilador);
    dc_p(compilador);
    pop_from_stack(compilador);
}

int var_type(controlador * compilador){
    if(!is_token_a_first_of("<TIPO_VAR>", compilador)){
        error_procedure("<TIPO_VAR>", compilador);
        return 0;
    }
        //da erro

    // if(!(compare_token(NUM_INTEIRO, compilador) ||compare_token(NUM_REAL, compilador))){
    //     if(compare)
    //     return; // pq tem esse return aqui? tem q chamar a funcao de erro
    // }
    
    push_compilador(7, compilador);
    get_token_from_lexic(compilador);
    pop_from_stack(compilador);
    return 1;
}

void number(controlador * compilador){
    if(!is_token_a_first_of("<NUMERO>", compilador))
        //da erro
        return;

    push_compilador(31, compilador);
    get_token_from_lexic(compilador);
}

int variables(controlador * compilador){
    if(!is_token_a_first_of("<VARIAVEIS>", compilador)){
        return 0;
    }

    push_compilador(8, compilador);
    if(!consume_terminal(IDENT, compilador))
        return 0;
    if(compare_token(VIRGULA, compilador)){
        get_token_from_lexic(compilador);
        variables(compilador);
    }
    pop_from_stack(compilador);
    return 1;
}

void parameters(controlador * compilador){
    if(!is_token_a_first_of("<PARAMETROS>", compilador))
        return;

    push_compilador(10, compilador);
    if(!consume_terminal(ABRE_PARENTESIS, compilador))
        return;

    get_variable:
    variables(compilador);
    
    if(!consume_terminal(DOIS_PONTOS, compilador))
        return;

    if(!var_type(compilador))
        return;

    if(compare_token(FECHA_PARENTESIS, compilador)){
        consume_terminal(FECHA_PARENTESIS, compilador);
    }else{
        if(!consume_terminal(PONTO_VIRGULA, compilador))
            return;
        goto get_variable;
    }
    pop_from_stack(compilador);
}

void program_body(controlador * compilador){
    if(!is_token_a_first_of("<CORPO_P>", compilador)){
        return;
    }

    push_compilador(13, compilador);
    dc_v(compilador);

    if(!consume_terminal(BEGIN, compilador))
        return;

    commands(compilador);

    if(!consume_terminal(END, compilador))
        return;
    if(!consume_terminal(PONTO_VIRGULA, compilador))
        return;
    pop_from_stack(compilador);
}

void list_arg(controlador * compilador){
    if(!is_token_a_first_of("<LISTA_ARG>", compilador)){
        return;
    }

    push_compilador(14, compilador);
    if(!consume_terminal(ABRE_PARENTESIS, compilador))
        return;
    ident:
    if(!consume_terminal(IDENT, compilador))
        return;
    if(!compare_token(PONTO_VIRGULA, compilador)){
        consume_terminal(FECHA_PARENTESIS, compilador);
        return;
    }
    if(!compare_token(FECHA_PARENTESIS, compilador)){
        goto ident;
    }
    pop_from_stack(compilador);
}

void commands(controlador * compilador){
    if(!is_token_a_first_of("<COMANDOS>", compilador)){
        return;
    }

    push_compilador(18, compilador);
    cmd(compilador);
    if(!consume_terminal(PONTO_VIRGULA, compilador))
        return;
    
    commands(compilador);
    pop_from_stack(compilador);
}

void cmd(controlador * compilador){
    if(!is_token_a_first_of("<CMD>", compilador))
        return;

    push_compilador(19, compilador);
    switch(compilador->current_token->id){
        case CASE_FOR:
            get_token_from_lexic(compilador);
            if(!consume_terminal(DOIS_PONTOS_IGUAL, compilador))
                return;
            expression(compilador);
            if(!consume_terminal(TO, compilador))
                break;
            number(compilador);
            if(!consume_terminal(DO, compilador))
                break;
            cmd(compilador);
            break;
        case CASE_BEGIN:
            get_token_from_lexic(compilador);
            commands(compilador);
            if(!consume_terminal(END, compilador))
                break;
            break;
        case CASE_WRITE:
            get_token_from_lexic(compilador);
            if(!consume_terminal(ABRE_PARENTESIS, compilador))
                break;
            if(!variables(compilador)){
                consume_terminal(IDENT, compilador);
                break;
            }
            if(!consume_terminal(FECHA_PARENTESIS, compilador))
                break;
            break;
        case CASE_READ:
            get_token_from_lexic(compilador);
            if(!consume_terminal(ABRE_PARENTESIS, compilador))
                break;
            if(!variables(compilador)){
                consume_terminal(IDENT, compilador);
                break;
            }
            if(!consume_terminal(FECHA_PARENTESIS, compilador))
                break;
            break;
        case CASE_WHILE:
            get_token_from_lexic(compilador);
            if(!consume_terminal(ABRE_PARENTESIS, compilador))
                break;
            // get_token_from_lexic(compilador);
            condition(compilador);
            if(!consume_terminal(FECHA_PARENTESIS, compilador))
                break;
            if(!consume_terminal(DO, compilador))
                break;
            cmd(compilador);
            break;
        case CASE_IF:
            get_token_from_lexic(compilador);
            condition(compilador);
            if(!consume_terminal(THEN, compilador))
                break;
            cmd(compilador);
            if(!consume_terminal(PONTO_VIRGULA, compilador))
                break;
            if(!consume_terminal(ELSE, compilador))
                break;
            cmd(compilador);
            break;
        case CASE_IDENT:
            get_token_from_lexic(compilador);
            atribuition(compilador);
            break;
        default:
            break;
        //da erro
    }
    pop_from_stack(compilador);
}

void atribuition(controlador * compilador){
    if(!is_token_a_first_of("<ATRIBUICAO>", compilador))
        return;
    
    push_compilador(21, compilador);
    if(is_token_a_first_of("<LISTA_ARG>", compilador)){
        list_arg(compilador);
        return;
    }

    if(!consume_terminal(DOIS_PONTOS_IGUAL, compilador))
        return;
    expression(compilador);
    if(compare_token(PONTO_VIRGULA, compilador))
        return;
    pop_from_stack(compilador);
}

void condition(controlador * compilador){
    if(!is_token_a_first_of("<CONDICAO>", compilador))
        return;
    
    push_compilador(20, compilador);
    get_token_from_lexic(compilador);
    expression(compilador);    

    // get_token_from_lexic(compilador);
    if(compare_token(IGUAL, compilador) || 
        compare_token(MAIOR_IGUAL, compilador) ||
        compare_token(MENOR_IGUAL, compilador) ||  
        compare_token(MAIOR, compilador) || 
        compare_token(MENOR, compilador) || 
        compare_token(DIFERENTE, compilador)){

        get_token_from_lexic(compilador);

    } else{
        //da erro
    }
    
    get_token_from_lexic(compilador);
    expression(compilador);
    pop_from_stack(compilador);
}

void expression(controlador * compilador){
    if(!is_token_a_first_of("<EXPRESSAO>", compilador))
        return;

    push_compilador(23, compilador);
    if(!term(compilador))
        return;
    get_token_from_lexic(compilador);

    if(compare_token(MAIS, compilador) || compare_token(MENOS, compilador)){
        get_token_from_lexic(compilador);
        if(!term(compilador)){
            error_procedure("<TERMO>", compilador);
            return;
        }
    }
    pop_from_stack(compilador);
}

int term(controlador * compilador){
    if(!is_token_a_first_of("<TERMO>", compilador))
        return 0;

    push_compilador(27, compilador);
    get_token_from_lexic(compilador);

    if(compare_token(MAIS, compilador) || compare_token(MENOS, compilador)){
        get_token_from_lexic(compilador);
    }else if(compare_token(PONTO_VIRGULA, compilador)){
        return 1;
    }

    
    if(!factor(compilador)){
        error_procedure("<FATOR>", compilador);
        return 0;
    }
    if(!(compare_token(MULT, compilador) || compare_token(DIV, compilador)))
        return 1;
    
    get_token_from_lexic(compilador);
    factor(compilador);

    // get_token_from_lexic(compilador);
    if(compare_token(MULT, compilador) || compare_token(DIV, compilador)){
        get_token_from_lexic(compilador);
        factor(compilador);
    }
    pop_from_stack(compilador);
    return 1;
}

int factor(controlador * compilador){
    if(!is_token_a_first_of("<TERMO>", compilador))
        return 0;
    
    push_compilador(30, compilador);

    if(compare_token(ABRE_PARENTESIS, compilador)){
        get_token_from_lexic(compilador);
        expression(compilador);
        if(!consume_terminal(FECHA_PARENTESIS, compilador))
            return 0;
    }
    pop_from_stack(compilador);
    return 1;
}
