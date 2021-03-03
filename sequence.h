typedef struct sec_node{
	int prefix;
	char data;
	int count;
	struct sec_node *next, *prev;
}sec_node;

typedef sec_node* seq_holder;


void init_seq_holder(seq_holder *h);
void set_seq_holder(seq_holder *h);
void update_seq_holder(seq_holder *h,char *c);
int check_seq(seq_holder h,char *c);
void traverse(seq_holder h);
char* get_string(seq_holder h,int seq_no, char *ch);
int in_string_table(seq_holder h,int NEW);
int contained(int i);
int get_seq_number(seq_holder H,char *c);
int get_count();
