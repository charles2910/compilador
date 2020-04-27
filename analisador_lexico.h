#define SIZE_TAB_RESERVADAS 39		/* Tamanho da tabela de palavras reservadas. */ 
#define BUFFER_SIZE 4096

typedef struct {
	char * string;
	char * token;
} par_token;

int populate_hashmap(map_t);

int load_file(char *, char *);

int fill_buffer(FILE *, char *);

int get_next_state(int, char);

par_token * get_par_token(char *);

char * new_buffer();

char * analise_lexica(char *, char *, int);
