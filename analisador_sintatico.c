#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "analisador_lexico.h"
#include "analisador_sintatico.h"
#include "hashmap.h"

table_tokens_seguidores_primeiros tabela[] = {
    {"<PROGRAMA>", "<PROGRAM>", "λ"},
    {"<CORPO>", "<CONST> <VAR> <PROCEDURE> <BEGIN> λ", "<PONTO>"},
    {"<DC>", "<CONST> <VAR> <PROCEDURE> λ", "<BEGIN>"},
    {"<DC_C>", "<CONST> λ", "<VAR>  <PROCEDURE>  <BEGIN>"},
    {"<DC_V>", "<VAR> λ", "<PROCEDURE>  <BEGIN>"},
    {"<DC_P>", "<PROCEDURE> λ", "<BEGIN>"},
    {"<DC_LOC>", "<VAR> λ", "<BEGIN>"},
    {"<TIPO_VAR>", "<NUM_REAL> <NUM_INTEIRO>", "<PONTO_VIRGULA>  <ABRE_PARENTESIS>"},
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
	char* primeiros;

	table_tokens_seguidores_primeiros* tabela_seguidores_primeiros;
	int erro = hashmap_get(compilador->map_tokens_seguidores_primeiros, token, &tabela_seguidores_primeiros);

	if (erro)
		return 0;

	primeiros = tabela_seguidores_primeiros->primeiros;
	char *pch = strstr(primeiros, compilador->current_token->token);
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
    return strcmp(token, compilador->current_token->token) == 0 ? 1 : 0;
}

void consume_terminal(char* token, controlador * compilador){
    // consome um token terminal e vê se é o token esperado com base no parametro token passado (o current token é global)
    compare_token(token, compilador);
    get_token_from_lexic(compilador);
    return;
}

void get_token_from_lexic(controlador * compilador){
    compilador->current_token = get_token(compilador);
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
    if(!is_token_a_first_of("<PROGRAMA>", compilador)){
        printf(compilador->current_token->string);
        return;
    }
    consume_terminal(PROGRAM, compilador);    
    consume_terminal(IDENT, compilador);
    consume_terminal(PONTO_VIRGULA, compilador);
    
    body(compilador);
    

    consume_terminal(PONTO, compilador); 
}

void body(controlador * compilador){
    if(!is_token_a_first_of("<CORPO>", compilador)){
        return;
    }

    dc(compilador);
    consume_terminal(BEGIN,compilador);
    commands(compilador);
    consume_terminal(END, compilador);
    return;
}

void dc(controlador * compilador){
    if(!is_token_a_first_of("<DC>", compilador))
        return;

    dc_c(compilador);
    dc_v(compilador);
    dc_p(compilador);
}

void dc_c(controlador * compilador){
    if(!is_token_a_first_of("<DC_C>", compilador))
        return;
    consume_terminal(CONST, compilador);
    consume_terminal(IDENT, compilador);
    consume_terminal(IGUAL, compilador);
    number(compilador);
    consume_terminal(PONTO_VIRGULA, compilador);

    get_token_from_lexic(compilador);
    dc_c(compilador);
}

void dc_v(controlador * compilador){
    if(!is_token_a_first_of("<DC_V>", compilador))
        return;

    consume_terminal(VAR, compilador);

    variables(compilador);

    consume_terminal(DOIS_PONTOS, compilador);
    
    var_type(compilador);

    consume_terminal(PONTO_VIRGULA, compilador);

    dc_v(compilador);
}

void dc_p(controlador * compilador){
    if(!is_token_a_first_of("<DC_P>", compilador))
        return;

    consume_terminal(IDENT, compilador);

    parameters(compilador);

    consume_terminal(PONTO_VIRGULA, compilador);

    program_body(compilador);

    get_token_from_lexic(compilador);
    dc_p(compilador);
}

void var_type(controlador * compilador){
    if(!(compare_token(NUM_INTEIRO, compilador) ||!compare_token(NUM_REAL, compilador))){
        get_token_from_lexic(compilador);
        return; // pq tem esse return aqui? tem q chamar a funcao de erro
    }
    get_token_from_lexic(compilador);
}

void number(controlador * compilador){}

void variables(controlador * compilador){
    if(!is_token_a_first_of("<VARIAVEIS>", compilador)){
        return;
    }
    
    consume_terminal(IDENT, compilador);
    if(compare_token(VIRGULA, compilador)){
        get_token_from_lexic(compilador);
        variables(compilador);
    }
}


void parameters(controlador * compilador){
    if(!is_token_a_first_of("<PARAMETROS>", compilador))
        return;

    get_variable:
    variables(compilador);
    
    consume_terminal(DOIS_PONTOS, compilador);

    var_type(compilador);

    get_token_from_lexic(compilador);
    if(compare_token(FECHA_PARENTESIS, compilador)){
        return;
    }
    if(!compare_token(PONTO_VIRGULA, compilador)){
        // deu erro
    }else{
        goto get_variable;
    }
}

void program_body(controlador * compilador){
    if(!is_token_a_first_of("<CORPO_P>", compilador)){
        return;
    }

    dc_v(compilador);

    consume_terminal(BEGIN, compilador);

    commands(compilador);

    consume_terminal(END, compilador);
    consume_terminal(PONTO_VIRGULA, compilador);
}

void list_arg(controlador * compilador){
    if(!is_token_a_first_of("<LISTA_ARG>", compilador)){
        return;
    }
    consume_terminal(ABRE_PARENTESIS, compilador);
    ident:
    consume_terminal(IDENT, compilador);
    if(!compare_token(PONTO_VIRGULA, compilador)){
        consume_terminal(FECHA_PARENTESIS, compilador);
        return;
    }
    if(!compare_token(FECHA_PARENTESIS, compilador)){
        goto ident;
    }
}

void commands(controlador * compilador){
    if(!is_token_a_first_of("<COMANDOS>", compilador)){
        return;
    }
    cmd(compilador);
    consume_terminal(PONTO_VIRGULA, compilador);
    
    commands(compilador);
}

void cmd(controlador * compilador){
    if(!is_token_a_first_of("<CMD>", compilador))
        return;

    switch(compilador->current_token->id){
        case CASE_FOR:
            get_token_from_lexic(compilador);
            atribuition(compilador);
            consume_terminal(TO, compilador);
            number(compilador);
            consume_terminal(DO, compilador);
            cmd(compilador);
            return;
        case CASE_BEGIN:
            get_token_from_lexic(compilador);
            commands(compilador);
            consume_terminal(END, compilador);
            return;
        case CASE_WRITE:
            get_token_from_lexic(compilador);
            consume_terminal(ABRE_PARENTESIS, compilador);
            variables(compilador);
            consume_terminal(FECHA_PARENTESIS, compilador);
            return;
        case CASE_READ:
            get_token_from_lexic(compilador);
            consume_terminal(ABRE_PARENTESIS, compilador);
            variables(compilador);
            consume_terminal(FECHA_PARENTESIS, compilador);
            return;
        case CASE_WHILE:
            get_token_from_lexic(compilador);
            consume_terminal(ABRE_PARENTESIS, compilador);
            get_token_from_lexic(compilador);
            condition(compilador);
            consume_terminal(FECHA_PARENTESIS, compilador);
            consume_terminal(DO, compilador);
            cmd(compilador);
            return;
        case CASE_IF:
            get_token_from_lexic(compilador);
            condition(compilador);
            consume_terminal(THEN, compilador);
            cmd(compilador);
            consume_terminal(ELSE, compilador);
            cmd(compilador);
            return;
        case CASE_IDENT:
            get_token_from_lexic(compilador);
            atribuition(compilador);
            return;
        default:
            break;
        //da erro
    }
}

void atribuition(controlador * compilador){
    if(!is_token_a_first_of("<ATRIBUICAO>", compilador))
        return;
    
    if(is_token_a_first_of("<LISTA_ARG>", compilador)){
        list_arg(compilador);
    }

    consume_terminal(DOIS_PONTOS_IGUAL, compilador);
    expression(compilador);
}

void condition(controlador * compilador){
    if(!is_token_a_first_of("<CONDICAO>", compilador))
        return;
    
    get_token_from_lexic(compilador);
    expression(compilador);    

    get_token_from_lexic(compilador);
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

}

void expression(controlador * compilador){
    if(!is_token_a_first_of("<EXPRESSAO>", compilador))
        return;

    term(compilador);
    get_token_from_lexic(compilador);

    if(compare_token(MAIS, compilador) || compare_token(MENOS, compilador)){
        get_token_from_lexic(compilador);
        term(compilador);
    }
}

void term(controlador * compilador){
    if(!is_token_a_first_of("<TERMO>", compilador))
        return;

    get_token_from_lexic(compilador);
    if(compare_token(MAIS, compilador) || compare_token(MENOS, compilador))
        get_token_from_lexic(compilador);
    
    factor(compilador);
    if(!(compare_token(MULT, compilador) || compare_token(DIV, compilador)))
        return;
    
    get_token_from_lexic(compilador);
    factor(compilador);

    get_token_from_lexic(compilador);
    if(compare_token(MULT, compilador) || compare_token(DIV, compilador)){
        get_token_from_lexic(compilador);
        factor(compilador);
    }
}

void factor(controlador * compilador){
    if(!is_token_a_first_of("<TERMO>", compilador))
        return;
    
    if(compare_token(ABRE_PARENTESIS, compilador)){
        get_token_from_lexic(compilador);
        expression(compilador);
        consume_terminal(FECHA_PARENTESIS, compilador);
    }
}
