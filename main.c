#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "hashmap.h"

char* read_file_line(FILE* program);
void lexic_analizer();

void main(void) {
	map_t map;

	map = hashmap_new();
	populate_hashmap(map);

	lexic_analizer();

	return;
}

void lexic_analizer(){
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
