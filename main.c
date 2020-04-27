#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "hashmap.h"
#include "analisador_lexico.h"

/* Declaração do hashmap */
map_t map = NULL;

int main(int argc, char * argv[]) {
	/* Inicialização do hashmap */
	map = hashmap_new();
	populate_hashmap(map);
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
	printf("Size of buffer: %d\n", size);

	return 0;
}
