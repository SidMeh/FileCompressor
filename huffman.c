#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
	char str[100] = "55 66 11 4 11 33 44 99 67 12 34 56 00 34", enc[21];
	
	int bin, dec,i = 0, j, k,st, l = 0;
	char ascii, ch; 
	
	// huffman encoding	
	
	while(i<40){
	
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
			printf("%d %c ",dec,dec);
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
	puts(enc);
	//huffman decoding
	i = 0;
	int bin1, bin2, bin3, bin4;
	while(enc[i] != '\0') {
		
		bin = enc[i];
		if(bin < 0)
			bin = bin + 256;
//		printf("%d",bin);
		bin1 = bin%2 * 1;
		bin = bin/10;
		bin2 = bin1 + bin%2 * 2;
		bin = bin/10;
		bin3 = bin2 + bin%2 * 4;
		bin = bin/10;
		bin4 = bin3 + bin%2 * 8;
		printf("%d ",bin4);
		bin = bin/10;
		bin1 = bin%2 * 1;
		bin = bin/10;
		bin2 = bin1 + bin%2 * 2;
		bin = bin/10;
		bin3 = bin2 + bin%2 * 4;
		bin = bin/10;
		bin4 = bin3 + bin%2 * 8;
		printf("%d ",bin4);		
	
	
		i++;
	}
	
	
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

//index 0
dictionary[0][0] = 0;
dictionary[0][1] = 0;
dictionary[0][2] = 0;
dictionary[0][3] = 1;

//index 1
dictionary[1][0] = 0;
dictionary[1][1] = 0;
dictionary[1][2] = 1;
dictionary[1][3] = 0;

//index 2
dictionary[2][0] = 0;
dictionary[2][1] = 0;
dictionary[2][2] = 1;
dictionary[2][3] = 1;

//index 3
dictionary[3][0] = 0;
dictionary[3][1] = 1;
dictionary[3][2] = 0;
dictionary[3][3] = 0;

//index 0
dictionary[4][0] = 0;
dictionary[4][1] = 1;
dictionary[4][2] = 0;
dictionary[4][3] = 1;

//index 5
dictionary[5][0] = 0;
dictionary[5][1] = 1;
dictionary[5][2] = 1;
dictionary[5][3] = 0;

//index 6
dictionary[6][0] = 0;
dictionary[6][1] = 1;
dictionary[6][2] = 1;
dictionary[6][3] = 1;

//index 7
dictionary[7][0] = 1;
dictionary[7][1] = 0;
dictionary[7][2] = 0;
dictionary[7][3] = 0;

//index 8
dictionary[8][0] = 1;
dictionary[8][1] = 0;
dictionary[8][2] = 0;
dictionary[8][3] = 1;

//index 9
dictionary[9][0] = 1;
dictionary[9][1] = 0;
dictionary[9][2] = 1;
dictionary[9][3] = 0;

//index 10/space
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
	
	
	
	
	
	
	
	
	
	
	
	
	
