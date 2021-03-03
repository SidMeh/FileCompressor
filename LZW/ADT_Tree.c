#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count = 0;

typedef struct node_tree{
	char data;
	int key;
	int root_key;
	struct node_tree *next, *prev;
	struct node_tree *branch;
}node_tree;

typedef node_tree* list_tree;

void init_tree(list_tree *l);
void append_node(list_tree *l, char *c);
void traverse_root_list(list_tree);
int find_pattern(list_tree l, char *c);
void delete_tree(list_tree *l);
void make_dictionary(list_tree *l);
/*
int main(){
	list_tree L;
	init_tree(&L);
//	append_node(&L,"a");
	printf("\n");
	append_node(&L,"b");
	append_node(&L,"a");
	append_node(&L,"ab");
	append_node(&L,"ac");
	append_node(&L,"abd");
	append_node(&L,"abd ");
	append_node(&L,"abdj");
	append_node(&L,"bb");
	append_node(&L,"bd");
	append_node(&L,"bdd");
	append_node(&L,"bdf");
	append_node(&L,"bdfr");
	append_node(&L,"bdft");
	append_node(&L,"bdfrt");
	append_node(&L,"bdfrp");
	traverse_root_list(L->next->branch->branch->branch);
	printf("\nSuccessfull");
	printf("%c",L->next->data);
	int k = find_pattern(L,"bdf");
	printf("%d",k);
	delete_tree(&L);
//	traverse_root_list(L->next->branch->branch->branch);
	printf("Yes");
	return 0;
}
*/
void init_tree(list_tree *l){
	*l = NULL;
	return ;
}



void traverse_root_list(list_tree l){
	while(l){
		printf("%c",l->data);
		l = l->next;
	}
}
//printf("step clear\n");

void append_node(list_tree *l, char *c) {
	
	if(*l == NULL){
		count++;
		list_tree t;
		t = (node_tree*)malloc(sizeof(node_tree));
		t->data = c[0];
		t->next = NULL;
		t->prev = NULL;
		t->branch = NULL;
		t->key = count;
		*l = t;
		return;
	}
	
	//finding appropriate position for the end character of the input string
	int len = strlen(c), i = 0, flag = 0;
	list_tree p = *l, q = NULL;
	
	while(p){
		flag = 0;
		if(p->data == c[i]){
			flag = 1;
			i++;
			q = p;
			p = p->branch;
		}
		else{
			q = p;
			p = p->next;
			flag = 0;
		}
	}
	printf("%d",i);
		count++;
		list_tree t;
		t = (node_tree*)malloc(sizeof(node_tree));
		t->data = c[i];
		t->next = NULL;
		t->prev = NULL;
		t->branch = NULL;
		t->key = count;
		
	if(flag == 1)
		q->branch = t;
	else if(flag == 0)
		q->next = t;
	
}

int find_pattern(list_tree l, char *c){

	int len = strlen(c), i = 0, flag = 0;
	list_tree p = l, q = NULL;
	
	while(p){
		flag = 0;
		if(p->data == c[i]){
			flag = 1;
			i++;
			q = p;
			p = p->branch;
		}
		else{
			q = p;
			p = p->next;
			flag = 0;
		}
	}
	if(flag == 1){
		if(q->branch == NULL && c[i] == '\0')
			return 1;
		else 
			return 0;
	}
	if(flag == 0){
		if(q->next == NULL && c[i] == '\0')
			return 1;
		else 
			return 0;
	}
}

void delete_tree(list_tree *l){
	if(*l == NULL)
		return;
	list_tree p = *l;
	if(p->branch == NULL && p->next == NULL){
		if(p->prev == NULL){
			free(p);
			return;
		}
		list_tree q = p->prev;
		q->next = NULL;
		q->branch = NULL;
		free(p);
		return;
	}
	delete_tree(&p->branch);
	delete_tree(&p->next);
	return;
}



















