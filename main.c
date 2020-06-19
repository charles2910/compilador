#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "hashmap.h"
#include "analisador_lexico.h"

/* Declaração do hashmap */
map_t map_par_token = NULL;
map_t map_tokens_seguidores_primeiros = NULL;

int main(int argc, char * argv[]) {
	/* Inicialização do hashmap */
	map_par_token = hashmap_new();
	map_tokens_seguidores_primeiros = hashmap_new();
	populate_hashmap_par_token(map_par_token);
	populate_hashmap_tokens_seguidores_primeiros(map_tokens_seguidores_primeiros);

	/* Inicialização do Buffer */
	char * buffer = new_buffer();
	if (!buffer) {
		printf("Erro na criação do buffer.\n");
		return -1;
	}
	/* Verifica se devemos utilizar o arquivo de teste, ou um fornecido
								pelo usuário */
	char * arquivo = NULL;
	if(argc > 1)
		arquivo = argv[1];
	int size = load_file(arquivo, buffer);

	int line = 0;

	char * posicao = buffer;
	while (posicao != (buffer + size)) {
		get_token(&posicao, &line);
	}
	return 0;
}
