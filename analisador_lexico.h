#define SIZE_TAB_RESERVADAS 39		/* Tamanho da tabela de palavras reservadas. */ 

typedef struct {
	char * string;
	char * token;
} par_token;

int populate_hashmap(map_t);

void load_file(char *);

char * read_file_line(FILE *);

int get_next_state(int, char);

par_token * get_par_token(char *);
