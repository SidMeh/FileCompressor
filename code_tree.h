typedef struct code_node{
	
	int data;
	char code[8];
	struct code_node *left, *right;
	
}code_node;

typedef code_node* code_tree;

void init_code_tree(code_tree *t);
code_node* get_code_node(int data, int code);
void insert_code_tree(code_tree *t, int data, int code);
void inorder_traverse(code_tree t);
void preorder_traverse(code_tree t);
void postorder_traverse(code_tree t);
char* get_code_for_data(code_tree t, int data);
void generate_code();
void generate_tree(code_tree *t);
int height(code_tree t);
void detect_error(code_tree t);


