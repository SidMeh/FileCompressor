#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sequence.h"
/*
typedef struct sec_node{
	int prefix;
	char data;
	int count;
	struct sec_node *next, *prev;
}sec_node;

typedef sec_node* seq_holder;


void init_seq_holder(seq_holder *h);                   //working fine
void set_seq_holder(seq_holder *h);                        // working fine
void update_seq_holder(seq_holder *h,char *c);           // working fine
int check_seq(seq_holder h,char *c);                   // working fine
void traverse(seq_holder h);
char* get_string(seq_holder h,int seq_no,char *ct);  */          

int count_seq = -1;
/*
int main(){
	seq_holder H;
	init_seq_holder(&H);
	set_seq_holder(&H);
	update_seq_holder(&H,"AA");
	update_seq_holder(&H,"AAA");
	update_seq_holder(&H,"AAAA");
	update_seq_holder(&H,"AAAAA");
	int k = check_seq(H,"OR");
	if(k == 1){
		printf("yes %d",k);
	}
	else
		printf("no");
	traverse(H);
	printf("\n");
	char ct[9];

	strcpy(ct,get_string(H,27,ct));
	printf("%s ",ct);
	strcpy(ct,get_string(H,28,ct));
	printf("%s",ct);
	return 0;
}
*/
void init_seq_holder(seq_holder *h){
	count_seq = -1;
	*h = NULL;
	return ;
}

void set_seq_holder(seq_holder *h){
	int i;
	sec_node *nn, *p;
	for(i=97;i<123;i++){
		nn = (sec_node*)malloc(sizeof(sec_node));
		if(!nn)
			return;
		nn->next = NULL;
		nn->prev= NULL;
		nn->data = i;
		nn->prefix = -1;
		nn->count = ++count_seq;
		if(*h == NULL){
			*h = nn;
			continue;
		}
		p = *h;
		while(p->next)
			p = p->next;
		p->next = nn;
		nn->prev = p;
	}
}

void traverse(seq_holder h){
	sec_node *p = h;
	while(p){
		printf("[ %c %d %d ] ",p->data,p->count,p->prefix);
		p = p->next;
	}
}

void update_seq_holder(seq_holder *h,char *c){
	sec_node *p = *h, *q = NULL,*nn;
	while(p->data != c[0]){
		q = p;
		p = p->next;
	}
	char ch = c[1];
	int cnt = p->count,i = 1;
	//traversing till known part of string
//	printf("%d",strlen(c));
	while(p){
		while(p && p->prefix != cnt){
			q = p;
			p = p->next;
		}
		i++;
		if(!p)
			break;
//		printf("%d",strlen(c));
		if(i >strlen(c)-1)
			break;
		ch = c[i];
		cnt = p->count;
	}

	// adding unknown part of string
	int j;
	for(j = i-1;j < strlen(c);j++){
		nn = (sec_node*)malloc(sizeof(sec_node));
		if(!nn)
			return;
		nn->data = c[j];
		nn->count = ++count_seq;
	//	printf("\n%d %c\n",count_seq,c[j]); 
		nn->next = NULL;
		nn->prev = q;
		nn->prefix = cnt;
		q->next = nn;
		q = nn;
		cnt = q->count;
//		printf("%c",c[j]);
	}
}

int check_seq(seq_holder h,char *c){
	int i,flag = 1;
	sec_node *p = h,*q = NULL;
	for(i=97;i<123;i++){
		if(p->data == c[0]){
			printf("yeah");
			if(strlen(c) == 1){
			printf("ret");
				flag = 0;
				return p->count;
			}
			flag = 0;
			break;
		}
		q = p;
		p = p->next;	
	}
	if(flag == 1)
		return -1;
	i = 1;
	int cnt = p->count;
	p = p->next;
	if(p == NULL)
		return 0;
	q = p;
	while(c[i] != '\0'){
	
		if(p == NULL)
			return -1;
		if(c[i] == p->data && p->prefix == cnt){
			cnt = p->count;
			i++;
		}
		q = p;
		p = p->next;
	}
	return q->count;
}

char* get_string(seq_holder h,int seq_no,char *ct){

	if(seq_no > count_seq)
		return ct;
	strcpy(ct,"\0");
	sec_node *p = h;
	char c[109];
	while(p){
		if(p->count == seq_no){
			c[0] = p->data;
			break;
		}
		p = p->next;
	}
	int cnt = p->prefix;
	int i = 1;
	p = p->prev;
	int k;
	while(p){
		if(p->count == cnt){
//			printf("\n%c",p->data);
			c[i] = p->data;
			i++;
			cnt = p->prefix;
		}
		p = p->prev;
	}
	while(c[i] != '\0')
	{
		c[i] = '\0';
		i++;
	}
//	printf("%s",c);
	int j = i;
	i++;
	int eh = strlen(c);
	char ch[eh+1];

	for(i=0;i<eh;i++){
		ct[i] = c[eh-i-1];
	}
	while(ct[i] != '\0')
	{
		ct[i] = '\0';
		i++;
	}
//	printf("\nA %s A\n",ct);
//	strcpy(ct,c);
	return ct;
}



int get_count(){
	return count_seq;
}
