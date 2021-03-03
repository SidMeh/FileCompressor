#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"




void encode(FILE *fp, char *str){
	printf("\n|%s|\n",str);
//	int y = check_string(&T,P1);
	Trie T;
	init(&T);
	int arr[1000];
	int l = 0;
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
	int y = check_string(&T,"my");
	printf(" %d ",y);
	char P1[10] = "",nil[1] = "\0",P[10] ,C;
	int i = 0,k = 0,m,f,j = 0;
	P[0] = str[0];
	P1[0] = str[0];
	printf("\n%d\n",k);
	while(i < 5){
		i++;
		C = str[i];		
		strncat(P1,&C,1);
		m = check_string(&T,P1);
		if(m != -1)
			strncat(P,&C,1);
		else{
			k = insert_pattern(&T,P);
			strncat(P,&C,1);
			insert_pattern(&T,P);
			arr[l++] = k;
			strcpy(P,nil);
			strcpy(P1,nil);
			strncat(P,&C,1);
			strncat(P1,&C,1);		
			printf("%d ",k);
			fprintf(fp,"%d ",k);			
		}
	}
	arr[l++] = m;
	T = NULL;
	printf("\n%d k = %d %d\n",l,k,i);
	return ;
}
