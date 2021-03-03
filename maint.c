#include <stdio.h>
#include <stdlib.h>
#include "trie.h"
#include <string.h>

int numlen(int num);
void makestring(int num);

int main(){
//	Trie T;
//	init(&T);
	makestring(1455);
	trieNode *t = get_node('a');
	int k = insert_pattern(&T,"yess");
	printf("%d",k);
	k = insert_pattern(&T,"yep");
	printf("%d",k);
	k = insert_pattern(&T,"yes");
	printf("%d",k);
	k = insert_pattern(&T,"aaa");
	printf("%d",k);
	k = insert_pattern(&T,"aa");
	printf("%d",k);
	k = insert_pattern(&T,"aabb");
	printf("%d",k);
	k = check_string(&T,"aab");
	printf("\n%d",k);
	insert_pattern(&T,"a");
	insert_pattern(&T,"b");
	insert_pattern(&T,"c");
	insert_pattern(&T,"d");
	insert_pattern(&T,"e");
	insert_pattern(&T,"f");
	insert_pattern(&T,"g");
	insert_pattern(&T,"h");
	insert_pattern(&T,"i");
	insert_pattern(&T,"j");
	insert_pattern(&T,"k");
	insert_pattern(&T,"l");
	insert_pattern(&T,"m");
	insert_pattern(&T,"n");
	insert_pattern(&T,"o");
	insert_pattern(&T,"p");
	insert_pattern(&T,"q");
	insert_pattern(&T,"r");
	insert_pattern(&T,"s");
	insert_pattern(&T,"t");
	insert_pattern(&T,"u");
	insert_pattern(&T,"v");
	insert_pattern(&T,"w");
	insert_pattern(&T,"x");
	insert_pattern(&T,"y");
	insert_pattern(&T,"z");
	
	FILE *fs, *fd;
	
	fs = fopen("source.txt",r);
	fd = fopen("destination.txt",w);
	if(fs == NULL || fp == NULL)
		return;
	
	
	char output[1000],P1[10] = "",temp[100],nil[1] = "\0",P[10] ,C,K[2];
	int i = 0,k,m,f,j = 0;
	P[0] = sample[0];
	P1[0] = sample[0];
//	i++;
	while(sample[i] != '\0'){
		i++;
		C = sample[i];
		strncat(P1,&C,1);
		m = check_string(&T,P1);
		if(m)
			strncat(P,&C,1);
		else{
			k = check_string(&T,P);
			strncat(P,&C,1);
			insert_pattern(&T,P);

			strcpy(P,nil);
			strcpy(P1,nil);
			strncat(P,&C,1);
			strncat(P1,&C,1);		
			printf("%d ",k);			
		}

	}
//	printf("%d",m)	;
	
	return 0;
}

int numlen(int num){
	if(num == 0)
		return 1;
	int i = 0;
	while(num > 0){
		num = num/10;
		i++;
	}
	return i;
}

void makestring(int num){
	int k = numlen(num);
	char *s = (char*)malloc(sizeof(char)*k);
	int i;
	for(i = k-1;i >= 0;i--){
		s[i] = num%10 + '0';
		num = num/10;
	//	printf("%d %c ",num,s[i]);
	}
	printf("%s",s);
}














