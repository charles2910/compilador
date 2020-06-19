#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "analisador_lexico.h"
#include "analisador_sintatico.h"
#include "hashmap.h"

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
/* Declaração do hashmap */
map_t map_par_token = NULL;
map_t map_tokens_seguidores_primeiros = NULL;

char * posicao;
int line;

int is_token_a_first_of(char* token) {
	extern map_t map_tokens_seguidores_primeiros;
	char* primeiros;

	table_tokens_seguidores_primeiros* tabela_seguidores_primeiros;
	int erro = hashmap_get(map_tokens_seguidores_primeiros, token, &tabela_seguidores_primeiros);

	if (erro)
		return 0;

	primeiros = tabela_seguidores_primeiros->primeiros;
	char *pch = strstr(primeiros, current_token->string);

	return pch ? 1 : 0;
}

/**
 * Função inclui no hashmap o token com seu Primeiro e Seguidor. Retorna 0 em sucesso.
 */
int populate_hashmap_tokens_seguidores_primeiros(map_t in) {
	int ok = 0;


	for(int i = 0; i < SIZE_TAB_TOKENS; i++) {
        printf("teste");
		ok = hashmap_put(in, tabela[i].token, &(tabela[i]));
		// if(ok) {
		// 	printf("Erro em adicionar %d palavra no hashmap.\n", i);
		// 	return -1;
		// }
	}
	return 0;
}

int compare_token(char* token){
    return strcmp(token, current_token->token) == 0 ? 1 : 0;
}

void consume_terminal(char* token){
    // consome um token terminal e vê se é o token esperado com base no parametro token passado (o current token é global)
    get_token_from_lexic();
    return compare_token(token);
}

void get_token_from_lexic(){
    current_token = get_token(&posicao, &line);
}


void start(int argc, char* argv[]){
    /* Inicialização do hashmap */
	map_par_token = hashmap_new();
    printf("oi 1");
	map_tokens_seguidores_primeiros = hashmap_new();
	populate_hashmap_par_token(map_par_token);
	populate_hashmap_tokens_seguidores_primeiros(map_tokens_seguidores_primeiros);
    printf("teste");
    return;

	/* Inicialização do Buffer */
	char * buffer = new_buffer();
	if (!buffer) {
		printf("Erro na criação do buffer.\n");
		return;
	}
	/* Verifica se devemos utilizar o arquivo de teste, ou um fornecido
								pelo usuário */
	char * arquivo = NULL;
	if(argc > 1)
		arquivo = argv[1];
	int size = load_file(arquivo, buffer);

	line = 0;

	posicao = buffer;
	//while (posicao != (buffer + size)) {
    // get_token(&posicao, &line);
    printf("oiu");
    get_token_from_lexic();
    program();
    return;
}

void program(){
    if(!is_token_a_first_of("<PROGRAM>")){
        return;
    }
    get_token_from_lexic();
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
    return;
}

void dc(){
    if(!is_token_a_first_of("<DC>"))
        return;

    get_token_from_lexic();
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

    get_token_from_lexic();
    dc_c();
}

void dc_v(){
    if(!is_token_a_first_of("<DC_V>"))
        return;

    consume_terminal(VAR);

    get_token_from_lexic();
    variables();

    consume_terminal(DOIS_PONTOS);
    
    get_token_from_lexic();
    var_type();

    consume_terminal(PONTO_VIRGULA);

    get_token_from_lexic();
    dc_v();
}

void dc_p(){
    if(!is_token_a_first_of("<DC_P>"))
        return;

    consume_terminal(IDENT);

    get_token_from_lexic();
    parameters();

    consume_terminal(PONTO_VIRGULA);

    get_token_from_lexic();
    program_body();

    get_token_from_lexic();
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
    get_token_from_lexic();
    if(compare_token(VIRGULA)){
        get_token_from_lexic();
        variables();
    }
}


void parameters(){
    if(!is_token_a_first_of("<PARAMETROS>"))
        return;

    get_variable:
    variables();
    
    consume_terminal(DOIS_PONTOS);

    get_token_from_lexic();
    var_type();

    get_token_from_lexic();
    if(compare_token(FECHA_PARENTESIS)){
        return;
    }
    if(!compare_token(PONTO_VIRGULA)){
        // deu erro
    }else{
        goto get_variable;
    }
}
void program_body(){
    if(!is_token_a_first_of("<CORPO_P>")){
        return;
    }

    dc_v();

    consume_terminal(BEGIN);

    get_token_from_lexic();
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
    get_token_from_lexic();
    if(!compare_token(PONTO_VIRGULA)){
        consume_terminal(FECHA_PARENTESIS);
        return;
    }
    get_token_from_lexic();
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
    
    get_token_from_lexic();
    commands();
}

void cmd(){
    if(!is_token_a_first_of("<CMD>"))
        return;

    switch(current_token->id){
        case CASE_FOR:
            get_token_from_lexic();
            atribuition();
            consume_terminal(TO);
            number();
            consume_terminal(DO);
            get_token_from_lexic();
            cmd();
            return;
        case CASE_BEGIN:
            get_token_from_lexic();
            commands();
            consume_terminal(END);
            return;
        case CASE_WRITE:
            consume_terminal(ABRE_PARENTESIS);
            variables();
            consume_terminal(FECHA_PARENTESIS);
            return;
        case CASE_READ:
            consume_terminal(ABRE_PARENTESIS);
            variables();
            consume_terminal(FECHA_PARENTESIS);
            return;
        case CASE_WHILE:
            consume_terminal(ABRE_PARENTESIS);
            get_token_from_lexic();
            condition();
            consume_terminal(FECHA_PARENTESIS);
            consume_terminal(DO);
            get_token_from_lexic();
            cmd();
            return;
        case CASE_IF:
            get_token_from_lexic();
            condition();
            consume_terminal(THEN);
            get_token_from_lexic();
            cmd();
            consume_terminal(ELSE);
            get_token_from_lexic();
            cmd();
        case CASE_IDENT:
            get_token_from_lexic();
            atribuition();
        default:
            break;
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
    get_token_from_lexic();
    expression();
}

void condition(){
    if(!is_token_a_first_of("<CONDICAO>"))
        return;
    
    get_token_from_lexic();
    expression();    

    get_token_from_lexic();
    if(compare_token(IGUAL) || 
        compare_token(MAIOR_IGUAL) ||
        compare_token(MENOR_IGUAL) ||  
        compare_token(MAIOR) || 
        compare_token(MENOR) || 
        compare_token(DIFERENTE)){

        get_token_from_lexic();

    } else{
        //da erro
    }
    
    get_token_from_lexic();
    expression();

}

void expression(){
    if(!is_token_a_first_of("<EXPRESSAO>"))
        return;

    term();
    get_token_from_lexic();

    if(compare_token(MAIS) || compare_token(MENOS)){
        get_token_from_lexic();
        term();
    }
}

void term(){
    if(!is_token_a_first_of("<TERMO>"))
        return;

    get_token_from_lexic();
    if(compare_token(MAIS) || compare_token(MENOS))
        get_token_from_lexic();
    
    factor();
    if(!(compare_token(MULT) || compare_token(DIV)))
        return;
    
    get_token_from_lexic();
    factor();

    get_token_from_lexic();
    if(compare_token(MULT) || compare_token(DIV)){
        get_token_from_lexic();
        factor();
    }
}

void factor(){
    if(!is_token_a_first_of("<TERMO>"))
        return;
    
    if(compare_token(ABRE_PARENTESIS)){
        get_token_from_lexic();
        expression();
        consume_terminal(FECHA_PARENTESIS);
    }
}
