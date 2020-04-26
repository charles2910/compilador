#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE* read_file_line();

void main(void) {
	read_file_line();

	return;
}

FILE* read_file_line(){
	char file_name[] = "meu_programa.txt";
	char * line = NULL;
	__ssize_t line_size;
  	size_t line_buf_size = 0;

	FILE *program = fopen(file_name, "r");

	if(program == NULL){
		printf("Your file was not found");
		exit(EXIT_FAILURE);
	}

	int line_count = 0;

	line_size = getline(&line, &line_buf_size, program);

	while(line_size > 0){
		printf("%d", line_size);
		printf("%s", line);
		printf("%c", line[0]);
		line_size = getline(&line, &line_buf_size, program);
		getchar();
	}

	free(line);

	fclose(program);

	return EXIT_SUCCESS;
}
