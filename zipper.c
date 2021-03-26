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
		fd = fopen("compressed.txt","w");
		
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
		fdc = fopen("decompressed.txt","w");

		decode(ft,fdc);
		fclose(ft);
		fclose(fdc);		
		
		printf("Input file - %s\n",argv[2]);
		printf("Decompressed file - decompressed.txt\n");
		
	}

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
	
	int i = 0, num, j, curr, dec, k;
	char str[5000], *code;
	fscanf(fp,"%s",str);
	
	while(str[i] != '\0') {
		
		num = str[i];
		if(num < 0)
			num = num + 256;
		code = get_code_for_data(C,num);	
		
		j = 0;
		while(j < 7){
			if(isFull(s) == 1){
				dec = 0;
				k = 1;
				while(isEmpty(s) != 1){
					curr = pop_stack(&s);
					dec = dec + curr*k;
					k = 2*k;
				}
			//	if((int)dec != 0)
				fprintf(fd,"%c",dec);
				printf("%c ",dec);
				if(dec > 255)
					printf("\nERROR\n");
			}
			stack_push(&s,code[j] - '0');
			j++;
		}
	i++;
	}	
i = pow(4,2);
printf("%d",i);
}


void generate_key() {
	int i, j, k = 0;
	for(i = 0;i<11;i++){
		for(j=10;j>=0;j--){
			key[k][1] = key1[i]+key2[j];
			key[k][0] = k + 1;
//			printf("\n %d %d ",arr3[k][0],arr3[k][1]);
			k++;
		}
	}
	
}


void decode(FILE *fp, FILE *fd) {
	
	char str[5000],ch[2] = "\n", str1[1000];
	int i = 0;
	for(i=0;i<50;i++){
		fscanf(fp,"%s",str1);
		strcat(str,str1);
		strcat(str,ch);
	}
	puts(str);
	i = 0;
/*	while(str[i] != '\0'){
		printf("%d ",str[i];
		i++;
	}
*/		
}












