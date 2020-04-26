#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "hashmap.h"

char* read_file_line(FILE* program);
void load_file(char * file);

void main(int argc, char * argv[]) {
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

void load_file(char * file){
	char file_name[] = "meu_programa.txt";
	char * line = NULL;

	FILE *program = fopen(file_name, "r");

	if(program == NULL){
		printf("Your file was not found");
		exit(EXIT_FAILURE);
	}

	line = read_file_line(program);
	while (line != NULL){
		printf("%s", line);
		// HERE WE'LL CALL THE LEXIC ANALIZER FUNCTION WITH 'LINE' PARAMETER 
		line = read_file_line(program);
	}
	
	fclose(program);
	free(line);
	free(program);

}

char* read_file_line(FILE* program){
	char * temp_line = NULL;
	__ssize_t line_size;
  	size_t line_buf_size = 0;

	line_size = getline(&temp_line, &line_buf_size, program);

	if(line_size > 0)
		return temp_line;
	
	free(temp_line);
	return NULL;
}
