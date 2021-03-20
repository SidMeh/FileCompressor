#include <stdio.h>
#include <stdlib.h>
#include "trie.h"
int count1 = -1;
void init(Trie *t){
	count1 = -1;
	trieNode *node = (trieNode*)malloc(sizeof(trieNode));
	*t = node;
	node->count = 0;
	node->flag = 0;
	int i;
	for(i=0;i<128;i++)
		node->child[i] = NULL;
}

trieNode* get_node(char c){
	trieNode *node = (trieNode*)malloc(sizeof(trieNode));
	node->count = count1;
	node->c = c;
	int i;
	for(i=0;i<128;i++){
		node->child[i] = NULL;
		node->flag = 0;
	}
	return node;
}

int insert_pattern(Trie *t,char *c){
//	printf("%d ",count1);
	if(c[0] == '\0')
		return (*t)->count;
	int ln = strlen(c);
	int pos = c[0];
	if((*t)->child[pos] == NULL){
		count1++;
		trieNode *n = get_node(c[0]);
		(*t)->child[pos] = n;
//		if(strlen(c) == 1)
//			return (*t)->count;
		 char *p = &c[1];
		 insert_pattern(&((*t)->child[pos]),p);
	}
	else if((*t)->child[pos]->c == c[0]){
//		if(strlen(c) == 1)
//			return (*t)->count;
		 char *p = &c[1];
		 insert_pattern(&((*t)->child[pos]),p);
	}	
}

int check_string(Trie *t,char *c){
	if(c[0] == '\0')
		return (*t)->count;
	int pos = c[0] ;
	if((*t)->child[pos] == NULL)
		return -1;
	if((*t)->child[pos]->c == c[0]){
		if(strlen(c) == 1){
			if((*t)->flag == 0)
				(*t)->flag = 1;
			}
		 char *p = &c[1];
		 int k = check_string(&((*t)->child[pos]),p);
		 return k;
	}	
	if((*t)->child[pos]->c != c[0]){
	return -1;
}
}









