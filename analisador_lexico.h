#define SIZE_TAB_RESERVADAS 39		/* Tamanho da tabela de palavras reservadas. */ 
#define BUFFER_SIZE 4096

typedef struct {
	char * string;
	char * token;
	int id;
} par_token;

int populate_hashmap(map_t);

int load_file(char *, char *);

int fill_buffer(FILE *, char *);

int get_next_state(int, char);

par_token * get_par_token(char *);

char * new_buffer();

char * analise_lexica(char *, char *, int);

int verify_rollback_state(int);

par_token * get_par_token(char *);

int is_final_state(int state);

int print_token_erro(par_token *);

int print_token(par_token *);
