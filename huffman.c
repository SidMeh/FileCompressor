#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
typedef struct stack{
	int arr[8];
	int top;
	int size;
}stack;

void init_stack(stack *s);
void stack_push(stack *s,int n);
int pop_stack(stack *s);
int isEmpty(stack s);
int isFull(stack s);

int dictionary[11][4];
void init_dictionary();
int pow1(int i,int j);

int main() {
	FILE *fp, *fi;
	fp = fopen("huffman.txt","w");
	fi = fopen("intermediate.txt","r");
	
	stack s;
	init_stack(&s);
	init_dictionary();
//	printf("%lf",pow(2,5));
	char str[7000] = "54 66 11 4 11 33 44 99 67 12 34 56 00 34 23 12 67 90 34 12 45 56 89 34 12 23 87 12 34 76 89 89 65 12 34 56 78 9 99", enc[7000];
	
	int bin, dec,i = 0, j, k,st, l = 0;
	char ascii, ch; 
	fgets(str,7000,fi);
	// huffman encoding	
	printf("Input string - ");
	puts(str);
	while(str[i] != '\0'){
	
		// bin = binary representation of char
		//pushing binary representation into stack if stack is not full
		if(isFull(s) == 0) {
			if(str[i] == ' ') {
				stack_push(&s,dictionary[10][3]);
				stack_push(&s,dictionary[10][2]);
				stack_push(&s,dictionary[10][1]);
				stack_push(&s,dictionary[10][0]);	 
			}
			else {
				k = str[i] - '0';
				stack_push(&s,dictionary[k][3]);
				stack_push(&s,dictionary[k][2]);
				stack_push(&s,dictionary[k][1]);
				stack_push(&s,dictionary[k][0]);
			}
		}			
		
		else if(isFull(s) == 1) {
		
			dec = 0;
			dec = dec + pop_stack(&s)*128;
			dec = dec + pop_stack(&s)*64;
			dec = dec + pop_stack(&s)*32;
			dec = dec + pop_stack(&s)*16;
			dec = dec + pop_stack(&s)*8;
			dec = dec + pop_stack(&s)*4;
			dec = dec + pop_stack(&s)*2;
			dec = dec + pop_stack(&s)*1;
//			printf("%d %c ",dec,dec);
			fprintf(fp,"%c",dec);
			enc[l] = dec;
			l++;
			if(str[i] == ' ') {
				stack_push(&s,dictionary[10][3]);
				stack_push(&s,dictionary[10][2]);
				stack_push(&s,dictionary[10][1]);
				stack_push(&s,dictionary[10][0]);	 
			}
			else {
				k = str[i] - '0';
				stack_push(&s,dictionary[k][3]);
				stack_push(&s,dictionary[k][2]);
				stack_push(&s,dictionary[k][1]);
				stack_push(&s,dictionary[k][0]);
			}
		}					
			
		i++;

	}
	fclose(fp);
	fp = fopen("huffman1.txt","w");
	printf("\nEncoded string - ");
	puts(enc);
	strcat(enc,"\0");
	printf("\nDecoded string - ");
	//huffman decoding
	i = 0;
	int bin1, bin2, bin3, bin4,sum;
	while(enc[i] != '\0') {
		
		bin = enc[i];
		if(bin < 0)
			bin = bin + 256;

		bin1 = bin%2 * 1;
		bin = bin/2;
		bin2 = bin1 + bin%2 * 2;
		bin = bin/2;
		bin3 = bin2 + bin%2 * 4;
		bin = bin/2;
		bin4 = bin3 + bin%2 * 8;
		if(bin4 == 11){
			printf(" ");
			fprintf(fp," ");
		}
		else {
			printf("%d",bin4-1);
			fprintf(fp,"%d",bin4-1);
		}
		bin = bin/2;
		bin1 = bin%2 * 1;
		bin = bin/2;
		bin2 = bin1 + bin%2 * 2;
		bin = bin/2;
		bin3 = bin2 + bin%2 * 4;
		bin = bin/2;
		bin4 = bin3 + bin%2 * 8;
		if(bin4 == 11){
			printf(" ");
			fprintf(fp," ");
		}
		else{
			printf("%d",bin4-1);		
			fprintf(fp,"%d",bin4-1);
		}
		i++;
	}
	fprintf(fp," %d",-1);
	
	return 0;
	
}

void init_stack(stack *s){
	int i;
	for(i=0;i<8;i++){
		s->arr[i] = 0;
	}
	s->top = -1;
	s->size = 8;
}

int isEmpty(stack s){

	if(s.top == -1)
		return 1;
		
	else
		return 0;
		
}

int isFull(stack s){

	if(s.top == 7){
		return 1;
	}	
	else
		return 0;
		
}

int pop_stack(stack *s){

	if(s->top == -1)
		return 0;
		
	 int k = s->arr[s->top];
	 s->top = s->top - 1;
	 return k;
	 
}

void stack_push(stack *s,int k){

	if(s->top == 7)
		return;
		
	s->top = s->top + 1;
	s->arr[s->top] = k;
	return ;
	
}

void init_dictionary(){

//index 0          DEC 1   ||  16
dictionary[0][0] = 0;
dictionary[0][1] = 0;
dictionary[0][2] = 0;
dictionary[0][3] = 1;

//index 1			DEC 2   ||  32
dictionary[1][0] = 0;
dictionary[1][1] = 0;
dictionary[1][2] = 1;
dictionary[1][3] = 0;

//index 2            DEC 3  ||  48
dictionary[2][0] = 0;
dictionary[2][1] = 0;
dictionary[2][2] = 1;
dictionary[2][3] = 1;

//index 3            DEC  4 ||  64
dictionary[3][0] = 0;
dictionary[3][1] = 1;
dictionary[3][2] = 0;
dictionary[3][3] = 0;

//index 4           DEC 5 || 65
dictionary[4][0] = 0;
dictionary[4][1] = 1;
dictionary[4][2] = 0;
dictionary[4][3] = 1;

//index 5          DEC 6 || 96
dictionary[5][0] = 0;
dictionary[5][1] = 1;
dictionary[5][2] = 1;
dictionary[5][3] = 0;

//index 6         DEC 7  ||  112
dictionary[6][0] = 0;
dictionary[6][1] = 1;
dictionary[6][2] = 1;
dictionary[6][3] = 1;

//index 7           DEC 8   ||   128
dictionary[7][0] = 1;
dictionary[7][1] = 0;
dictionary[7][2] = 0;
dictionary[7][3] = 0;

//index 8          DEC  9  ||    144
dictionary[8][0] = 1;
dictionary[8][1] = 0;
dictionary[8][2] = 0;
dictionary[8][3] = 1;

//index 9         DEC 10    ||   160
dictionary[9][0] = 1;
dictionary[9][1] = 0;
dictionary[9][2] = 1;
dictionary[9][3] = 0;

//index 10/space     DEC 11  ||      176
dictionary[10][0] = 1;
dictionary[10][1] = 0;
dictionary[10][2] = 1;
dictionary[10][3] = 1;

}

int pow1(int i,int j) {

	if(j == 0)
		return 1;
		
	int k = 1;
	for(k = j;k>0;k--)
		k = k*i;
	printf("%d ",k);
	return k;
	
}
	
	
	
	
	
	
	
	
	
	
	
	
	
