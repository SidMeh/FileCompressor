#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct trieNode{
	int count;
	char c;
	struct trieNode *child[127];
	int flag;
}trieNode;


typedef trieNode* Trie;

void init(Trie *t);
int insert_pattern(Trie *t,char *c);
trieNode* get_node(char c);
int check_string(Trie *t,char *c);
