#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "analisador_lexico.h"
#include "analisador_sintatico.h"

table_tokens_seguidores_primeiros tabela[] = {
    {"<PROGRAMA>", "program", "λ"},
    {"<CORPO>", "const var procedure begin λ", "."},
    {"<DC>", "const var procedure λ", "begin"},
    {"<DC_C>", "const λ", "var  procedure  begin"},
    {"<DC_V>", "var λ", "procedure  begin"},
    {"<DC_P>", "procedure λ", "begin"},
    {"<DC_LOC>", "var λ", "begin"},
    {"<TIPO_VAR>", "real inteiro", ";  )"},
    {"<VARIAVEIS>", "ident", ":  )"},
    {"<MAIS_VAR>", ", λ", ":  )"},
    {"<PARAMETROS>", "( λ", ";"},
    {"<LISTA_PAR>", "ident", ")"},
    {"<MAIS_PAR>", "; λ", ")"},
    {"<CORPO_P>", "var λ begin", "procedure  begin"},
    {"<LISTA_ARG>", "( λ", ";"},
    {"<ARGUMENTOS>", "ident", ")"},
    {"<MAIS_IDENT>", "; λ", ")"},
    {"<PFALSA>", "else λ", ";"},
    {"<COMANDOS>", "read write while if ident begin for", "end"},
    {"<CMD>", "read write while if ident begin for", ";"},
    {"<CONDICAO>", "+  -  ident numero_int numero_real (", ")  then"},
    {"<ATRIBUICAO>", "( λ :=", ";"},
    {"<RELACAO>", "= | <> | >= | <= | > | <", "+  -  ident numero_int numero_real ("},
    {"<EXPRESSAO>", "+ - ident numero_int numero_real (", "= <> >= <= > < ) then"},
    {"<OP_UN>", "+ - λ", "ident numero_int numero_real ("},
    {"<OUTROS_TERMOS>" ," + - ", " =  <>  >=  <=  >  <  )  then"},
    {"<OP_AD>" ," + - ", " +  -  ident  numero_int numero_real  ("},
    {"<TERMO>" ," +  -  ident  numero_int numero_real  ( ", " + -"},
    {"<MAIS_FATORES>" ," * / ", " + -"},
    {"<OP_MUL>" ," * / ", " ident  numero_int numero_real  ("},
    {"<FATOR>" ," ident  numero_int numero_real  ( ", " * /"},
    {"<NUMERO>" ," numero_int numero_real ", " * /"}
};

par_token *current_token;

int is_token_a_first_of(char* token) {
	extern map_t map_tokens_seguidores_primeiros;
	
	table_tokens_seguidores_primeiros* tabela_seguidores_primeiros;
	int erro = hashmap_get(map_tokens_seguidores_primeiros, token, &tabela_seguidores_primeiros);

	if (erro)
		return 0;

	primeiros = tabela_seguidores_primeiros->primeiros;
	char *pch = strstr(primeiros, current_token.string);

	pch ? return 1 : return 0;
}

/**
 * Função inclui no hashmap o token com seu Primeiro e Seguidor. Retorna 0 em sucesso.
 */
int populate_hashmap_tokens_seguidores_primeiros(map_t in) {
	int ok = 0;

	for(int i = 0; i < SIZE_TAB_TOKENS; i++) {
		ok = hashmap_put(in, tab_reservados[i].string, &(tab_reservados[i]));
		if(ok) {
			printf("Erro em adicionar %d palavra no hashmap.\n", i);
			return -1;
		}
	}
	return 0;
}

int compare_token(char* token){
    strcmp(token, current_token->token) == 0 ? return 1 : return 0;
}

void consume_terminal(char* token){
    // consome um token terminal e vê se é o token esperado com base no parametro token passado (o current token é global)
    get_next_token();
    return compare_token(token)
}

void get_next_token(){
    current_token = get_token();
}


void start(){
    program();
}

void program(){
    if(!is_token_a_first_of("<PROGRAM>")){
        return;
    }
    get_next_token();
    consume_terminal(PROGRAM);    
    consume_terminal(IDENT);
    consume_terminal(PONTO_VIRGULA);
    
    body();
    
    consume_terminal(PONTO); 
}

void body(){
    if(!is_token_a_first_of("<CORPO>")){
        return;
    }

    dc();
    consume_terminal(BEGIN);
    commands();
    consume_terminal(END);
}

void dc(){
    if(!is_token_a_first_of("<DC>")){
        return;
    }

    get_next_token();
    dc_c();
    dc_v();
    dc_p();
}

void dc_c(){
    if(!is_token_a_first_of("<DC_C>"))
        return;
    consume_terminal(CONST);
    consume_terminal(IDENT);
    consume_terminal(IGUAL);
    number();
    consume_terminal(PONTO_VIRGULA);

    get_next_token();
    dc_c();
}

void dc_v(){
    if(!is_token_a_first_of("<DC_V>"))
        return;

    consume_terminal(VAR);

    get_next_token();
    variables();

    consume_terminal(DOIS_PONTOS);
    
    get_next_token();
    var_type();

    consume_terminal(PONTO_VIRGULA);

    get_next_token();
    dv_v();
}

void dc_p(){
    if(!is_token_a_first_of("<DC_P>"))
        return;

    consume_terminal(IDENT);

    get_next_token();
    parameters();

    consume_terminal(PONTO_VIRGULA);

    get_next_token();
    program_body();

    get_next_token();
    dc_p();
}

void var_type(){
    if(!(compare_token(NUM_INTEIRO) ||!compare_token(NUM_REAL))){
        return; // pq tem esse return aqui? tem q chamar a funcao de erro
    }
}

void number(){}

void variables(){
    if(!is_token_a_first_of("<VARIAVEIS>")){
        return;
    }
    
    consume_terminal(IDENT);
    get_next_token();
    if(compare_token(VIRGULA)){
        get_next_token();
        variables();
    }
}


void parameters(){
    if(!is_token_a_first_of("<PARAMETROS>"))
        return;

    get_variable:
    variables();
    
    consume_terminal(DOIS_PONTOS);

    get_next_token();
    var_type();

    get_next_token();
    if(compare_token(FECHA_PARENTESIS)){
        return;
    }
    if(!compare_token(PONTO_VIRGULA)){
        // deu erro
    }else{
        goto get_variable
    }
}
void program_body(){
    if(!is_token_a_first_of("<CORPO_P>")){
        return;
    }

    dc_v();

    consume_terminal(BEGIN);

    get_next_token();
    commands();

    consume_terminal(END);
    consume_terminal(PONTO_VIRGULA);
}

void list_arg(){
    if(!is_token_a_first_of("<LISTA_ARG>")){
        return;
    }
    consume_terminal(ABRE_PARENTESIS);
    ident:
    consume_terminal(IDENT);
    get_next_token();
    if(!compare_token(PONTO_VIRGULA)){
        consume_terminal(FECHA_PARENTESIS);
        return;
    }
    get_next_token();
    if(!compare_token(FECHA_PARENTESIS)){
        goto ident;
    }
}

void commands(){
    if(!is_token_a_first_of("<COMANDOS>")){
        return;
    }
    cmd();
    consume_terminal(PONTO_VIRGULA);
    
    get_next_token();
    commands();
}

void cmd(){
    if(!is_token_a_first_of("<CMD>"))
        return;

    switch(current_token->token){
        case FOR:
            get_next_token();
            atribuition();
            consume_terminal(TO);
            number();
            consume_terminal(DO);
            get_next_token();
            cmd();
            return;
        case BEGIN:
            get_next_token();
            commands();
            consume_terminal(END);
            return;
        case WRITE:
            consume_terminal(ABRE_PARENTESIS);
            variables();
            consume_terminal(FECHA_PARENTESIS);
            return;
        case READ:
            consume_terminal(ABRE_PARENTESIS);
            variables();
            consume_terminal(FECHA_PARENTESIS);
            return;
        case WHILE:
            consume_terminal(ABRE_PARENTESIS);
            get_next_token();
            condition();
            consume_terminal(FECHA_PARENTESIS);
            consume_terminal(DO);
            get_next_token();
            cmd();
            return;
        case IF:
            get_next_token();
            condition();
            consume_terminal(THEN);
            get_next_token();
            cmd();
            consume_terminal(ELSE);
            get_next_token();
            cmd();
        case IDENT:
            get_next_token();
            atribuition();
        case default:
        //da erro
    }
}

void atribuition(){
    if(!is_token_a_first_of("<ATRIBUICAO>"))
        return;
    
    if(is_token_a_first_of("<LISTA_ARG>")){
        list_arg();
    }

    consume_terminal(DOIS_PONTOS_IGUAL);
    get_next_token();
    expressao();
}

void condition(){
    if(!is_token_a_first_of("<CONDICAO>"))
        return;
    
    get_next_token();
    expression();    

    get_next_token();
    if(compare_token(IGUAL) || 
        compare_token(MAIOR_IGUAL) ||
        compare_token(MENOR_IGUAL) ||  
        compare_token(MAIOR) || 
        compare_token(MENOR) || 
        compare_token(DIFERENTE)){

        get_next_token();

    } else{
        //da erro
    }
    
    get_next_token();
    expression();

}

void expression(){
    if(!is_token_a_first_of("<EXPRESSAO>"))
        return;

    term();
    get_next_token();

    if(compare_token(MAIS) || compare_token(MENOS)){
        get_next_token();
        term();
    }
}

void term(){
    if(!is_token_a_first_of("<TERMO>"))
        return;

    get_next_token();
    if(compare_token(MAIS) || compare_token(MENOS))
        get_next_token();
    
    factor();
    if(!(compare_token(MULT) || compare_token(DIV)))
        return;
    
    get_next_token();
    factor();

    get_next_token();
    if((compare_token(MULT) || compare_token(DIV)){
        get_next_token();
        factor();
    }
}

void factor(){
    if(!is_token_a_first_of("<TERMO>"))
        return;
    
    if(compare_token(ABRE_PARENTESIS)){
        get_next_token();
        expression();
        consume_terminal(FECHA_PARENTESIS);
    }
}
