#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "hashmap.h"
#include "analisador_lexico.h"

int main(int argc, char * argv[]) {
	/* Declaração do hashmap */
	map_t map;
	/* Inicialização do hashmap */
	map = hashmap_new();
	populate_hashmap(map);
	/* Verifica se devemos utilizar o arquivo de teste, ou um fornecido
								pelo usuário */
	char * arquivo = NULL;
	if(argc > 1)
		arquivo = argv[1];
	load_file(arquivo);

	return 0;
}
