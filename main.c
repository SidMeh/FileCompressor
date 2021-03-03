#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "trie.h"
#include "sequence.h"
void encode(FILE *fp, char *str);
void decode(FILE *fp, int *arr);


int main() {

	FILE *fd, *fs, *fi;
	
	fs = fopen("source.txt","r+");
	
	if(fs == NULL){
		printf("Problem in opening File !!!\n");
//		return 0;
	}
	
	fd = fopen("destination.txt","w");
	
	if(fd == NULL){
		printf("Problem in compressing File1 !!!\n");
	//	return 0;
	}	
	
	fi = fopen("intermediate.txt","w+");
	
	if(fi == NULL){
		printf("Problem in compressing File2 !!!\n");
	//	return 0;
	}	
	// encoding
	char str[5] = "stat",st[6],ch = '\0';
	int i = 0,j;
	while(i <= 190){
	fgets(str,4,fs);
	encode(fi,str);
	i = i + 4;
	}
	fclose(fi);
	fi = fopen("intermediate.txt","r+");
	//decoding
	i = 0;
	int arr[4];
	while(i <= 160){
		fscanf(fi,"%d %d %d %d",&arr[0],&arr[1],&arr[2],&arr[3]);
		printf("%d %d %d %d",arr[0],arr[1],arr[2],arr[3]);
		decode(fd,arr);
		printf("yes");
		i = i + 4;
	}
	
	
	
	
	
	return 0;
}



void encode(FILE *fp, char *str){
	printf("\n|%s|\n",str);
//	int y = check_string(&T,P1);
	Trie T;
	init(&T);
	int arr[1000];
	int l = 0, j1;
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
	char ch[2];
/*	for(j1 = 1;j1 < 128;j1++){
		ch[0] = j1;
		insert_pattern(&T,ch);
	} */
	char P1[10] = "",nil[1] = "\0",P[10] ,C;
	int i = 0,k = 0,m,f,j = 0;
	P[0] = str[0];
	P1[0] = str[0];
	printf("\n%d\n",k);
	while(str[i]!='\0'){
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
	fprintf(fp,"%d ",m);
	T = NULL;
	printf("\n%d k = %d %d\n",l,k,i);
	return ;
}



void decode(FILE *fp, int *arr){
	int y = 0;
	seq_holder H;
	init_seq_holder(&H);
	

	set_seq_holder(&H);            //initialized table with single character strings
//		traverse(H);
	char ct[500], S[500],cm[200];
	char c[2] = "";

	int OLD_CODE = arr[0],NEW_CODE;
	printf("%s",get_string(H,OLD_CODE,ct));
	fprintf(fp,"%s",get_string(H,OLD_CODE,ct));
	strcpy(ct,get_string(H,OLD_CODE,ct));
	c[0] = '\0';
//	printf("%s",c);
	int i;
	i = 1;
	int flag = 1;  
	while(i < 4){
		NEW_CODE = arr[i];
//		printf("\n%d %d\n",NEW_CODE,get_count());
		if(NEW_CODE > get_count()){
			strcpy(S,get_string(H,OLD_CODE,S));
			strcat(S,c);
//			printf("%s",S);
			flag = 0;
		}
		else{
			strcpy(S,get_string(H,NEW_CODE,S));
			flag = 1;
		}
		printf("%s",S);
		fprintf(fp,"%s",S);
		c[0] = S[0];
		strcpy(ct,get_string(H,OLD_CODE,ct));
		if(flag == 1);
		strcat(ct,c);
		update_seq_holder(&H,ct);
		OLD_CODE = NEW_CODE;
		i++;
	}

//	printf("%s",get_string(H,34,ct));			
		traverse(H);
		
	update_seq_holder(&H,"aabc");

}

