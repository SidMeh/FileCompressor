#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "code_tree.h"
#include "stack.h"
#include "Circular_Queue.h"

void encode(FILE *fp,FILE *fd);
void decode(FILE *fp,FILE *fd);

int key[121][2];
int key1[11] = {1,2,3,4,5,6,7,8,9,10,11};
int key2[11] = {16,32,48,64,80,96,112,128,144,160,176};

int main(int argc,char **argv) {


	
	if(strcmp(argv[1],"compress") == 0){

		FILE *fp;
		fp = fopen(argv[2],"r");
		FILE *fd;
		fd = fopen(argv[4],"w");
		
		encode(fp,fd);
		fclose(fd);
		fclose(fp);

		printf("Input file - %s\n",argv[2]);
		printf("Compressed file - compressed.txt\n");
 
	}
	
	if(strcmp(argv[1],"decompress") == 0) {
	
		FILE *ft;
		ft = fopen(argv[2],"r");
		FILE *fdc;
		fdc = fopen(argv[4],"w");

		decode(ft,fdc);
		fclose(ft);
		fclose(fdc);		
		
		printf("Input file - %s\n",argv[2]);
		printf("Decompressed file - decompressed.txt\n");
		
	}
/*	FILE *f1,*f2;
	f1 = fopen("reference.txt","r");
	f2 = fopen("o_reference.txt","w");
	char ch = '\0';
	int i = 0;
	while(i < 355){
		fscanf(f1,"%c",&ch);
		fprintf(f2,"%c",ch-'0');
		i++;
	}
	}*/
/*	char ch[5000];
	fscanf(fd,"%s",ch);
	printf("%s",ch);
	fscanf(fd,"%s",ch);
	printf("%s",ch);	
	fscanf(fd,"%s",ch);
	printf("%s",ch);	*/
	return 0;
}

void encode(FILE *fp,FILE *fd) {

	code_tree C;
	init_code_tree(&C);
	generate_code();
	generate_tree(&C);
	detect_error(C);	
	
	stack s;
	init_stack(&s,8);
	
	int i = 0, num, j, curr, dec, k, pos = 0,arrray[50];
	char str[50000], *code;
	fscanf(fp,"%s",str);
	int len = strlen(str);
	len = (len*7)/8 - 3;
	fprintf(fd,"%d ",len);
	while(str[i] != '\0') {
		
		num = str[i];
		if(num < 0)
			num = num + 256;
		code = get_code_for_data(C,num);	
//		printf("\n%d %s",num,code);
		j = 0;
		while(j < 7){
			if(isFull(s) == 1){
				dec = 0;
				k = 1;
/*				while(isEmpty(s) != 1){
					curr = pop_stack(&s);
					dec = dec + curr*k;
					k = 2*k;
				}*/
				dec = pop_stack(&s)*1;
				dec = dec + pop_stack(&s)*2;
				dec = dec + pop_stack(&s)*4;
				dec = dec + pop_stack(&s)*8;
				dec = dec + pop_stack(&s)*16;
				dec = dec + pop_stack(&s)*32;
				dec = dec + pop_stack(&s)*64;
				dec = dec + pop_stack(&s)*128;
				if(dec == 0){
		//			printf("\n Error \n");
					
				}
				if(dec == 0){
					arrray[pos++] = i;
					printf("YES ");
					fprintf(fd,"%c",dec);
				}
				else
					fprintf(fd,"%c",dec);
	//			printf("%d %d %c\n",dec,i,dec);
			//	if(dec > 256)
		//			printf("\nERROR\n");
		//			return;
			}
			stack_push(&s,code[j] - '0');
			j++;
		}
	i++;
	}	

}


void generate_key() {
	int i, j, k = 0;
	for(i = 0;i<11;i++){
		for(j=10;j>=0;j--){
			key[k][1] = key1[i]+key2[j];
			key[k][0] = k + 6;
	//		printf("\n %d %d ",key[k][0],key[k][1]);
			k++;
		}
	}
	
}

/*
void decode(FILE *fp, FILE *fd) {
	
	char str[5000],ch[2] = "\n", str1[1000],chr;
	int i = 0;

//	puts(str);
	i = 0;
	int k = 0,arr[10],curr = 0;
	FILE *fr;
	fr = fopen("reference.txt","r");
	fscanf(fr,"%d",&arr[0]);
	while(arr[k] != -1)
		fscanf(fr,"%d",&arr[++k]);	
	while(i < 2700){
		fscanf(fp,"%c",&chr);
		if(i == arr[curr]){
//			printf("%d SET",0);
			curr++;
		}
		k = chr;
		if(k < 0)
			k = k + 256;
		printf("%d %d %c\n",k,i,k);
		i++;
	}
		
}*/

void decode(FILE *fp,FILE *fd) {
	char ch, code[9] = "00000000", ref_code[9] = "00000000";
	int i = 0, j, num, k, bin, num1, dec, ele, limit, flag = 0;

	stack s;
	init_stack(&s,7);
	
	queue q;
	init(&q,56);
	
	generate_key();
	char str[50000];
//	fread(str,1,1000,fp);
	fscanf(fp,"%d ",&limit);
	while(i < limit-1){  
	
		j = 0;
		while(j < 7){
//			ch = str[i];
			fscanf(fp,"%c",&ch);
			if(ch == ' ' && flag == 0)
				continue;
			flag = 1;
			num = ch;
			if(num < 0)
				num = num + 256;
			num1 = num;
			strcpy(code,ref_code);
//			printf("%d ",num);

			for(k = 7;k >= 0 ;k--){
				bin = num%2;
				code[k] = bin + '0';
				num = num/2;
			}
//				if(j == 0)
//					printf(" %s %d",code,num1);			
			for(k = 0;k < 8; k++){
				bin = code[k] - '0';
				enqueue(&q,bin);
			}
			
			j++;
		}			
		
		while(isEmptyq(q) != 1){
			
			while(isFull(s) != 1){
				ele = dequeue(&q);
				stack_push(&s,ele);
			}
			
			dec = 0;
			dec = pop_stack(&s)*1;
			dec = dec + pop_stack(&s)*2;
			dec = dec + pop_stack(&s)*4;
			dec = dec + pop_stack(&s)*8;
			dec = dec + pop_stack(&s)*16;
			dec = dec + pop_stack(&s)*32;
			dec = dec + pop_stack(&s)*64;
		
			dec = dec - 6;
			char ch = key[dec][1] ;
			fprintf(fd,"%c",ch);
	//		fprintf(fd,"sd");
			
		}	
		
		i = i + 7;
	}
	char chhh = '\"';
//printf("%d",chhh);
}









