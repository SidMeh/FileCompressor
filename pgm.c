#include <stdio.h>
#include <stdlib.h>
#include "max_heap.h"
#include "stack.h"

typedef struct pgm_Image{
	char type[4];
	int height;
	int width;
	int max_gray_scale;
	int **pixel_array;
}pgm_Image;

int dictionary[11][4];
void init_dictionary();
int numlen(int num);
void makestring(FILE *fp, int num);

void init_pgm_image_from_file(FILE *fp, pgm_Image *img);
void convert_image_from_pgm_to_txt(pgm_Image img);
void bit_encode_image(FILE *fp);
void bit_decode_image();
void convert_txt_into_pgm();

int main(){
	FILE *fp = fopen("pgmimg.pgm", "rb");
	pgm_Image Image;
	init_pgm_image_from_file(fp,&Image);
	convert_image_from_pgm_to_txt(Image);
	convert_txt_into_pgm();
	return 0;
}

void init_pgm_image_from_file(FILE *fp, pgm_Image *Image){
	if(fp == NULL)
		return;
	
	FILE *fr = fopen("image_read.txt","w");
	fscanf(fp,"%s",Image->type);
	printf("Image type:%s\n",Image->type);
	fscanf(fp,"%d",&Image->width);
	fscanf(fp,"%d",&Image->height);
	fscanf(fp,"%d",&Image->max_gray_scale);
	printf("Image width: %d\n",Image->width);
	printf("Image height: %d\n",Image->height);
	printf("Image maximum gray scale: %d\n",Image->max_gray_scale);
	Image->pixel_array = (int**)malloc(sizeof(int*)*Image->height);
	int i = 0,j;
	for(i=0;i<Image->height;i++)
		*(Image->pixel_array + i) = (int*)malloc(sizeof(int)*Image->width);
	for(i = 0; i < Image->height;i++){
		for(j=0;j < Image->width;j++){
			fscanf(fp,"%d",&Image->pixel_array[i][j]);
		//	printf("%d ",Image.pixel_array[i][j]);
			fprintf(fr,"%d ",Image->pixel_array[i][j]);
		}
	//	printf("\n");
	}


}

void convert_image_from_pgm_to_txt(pgm_Image Image){
	max_heap h;
	init_max_heap(&h);
	int code_arr[256][2];
	int i, j, temp;
	for(i=0;i<256;i++){
		code_arr[i][0] = 0;
		code_arr[i][1] = 1;
	}
	for(i=0;i<Image.height;i++){
		for(j=0;j<Image.width;j++){
			temp = Image.pixel_array[i][j];
	//		printf("%d ",temp);
			code_arr[temp][0]++;
		}
	}	

	for(i=0;i<256;i++)
		insert_max_heap(&h,code_arr[i][0],i);
	map_code_via_heap(h,code_arr);
	for(i=0;i<256;i++){
	//	printf("\n%d %d",i,code_arr[i][1]);		
		if(code_arr[i][1] > 255)
			printf("ERROR");
	}
	FILE *fp = fopen("image_read.txt","w");
	for(i=0;i<Image.height;i++){
		for(j=0;j<Image.width;j++){
			temp = Image.pixel_array[i][j];
			makestring(fp,code_arr[temp][1]);
			//fprintf(fp,"%d ",code_arr[temp][1]);
		}
	}	
	fprintf(fp,"%c",'e');
	fclose(fp);
	FILE *fc = fopen("image_info.txt","w");
	
	fprintf(fc,"%s\n",Image.type);
	fprintf(fc,"%d %d\n",Image.height,Image.width);
	fprintf(fc,"%d\n",Image.max_gray_scale);
	
	for(i=0;i<256;i++)
		fprintf(fc,"%d %d\n",i, code_arr[i][1]);
	fclose(fc);
	
	fp = fopen("image_read.txt","r");
	bit_encode_image(fp);
	bit_decode_image();
}


void bit_encode_image(FILE *fp) {
	init_dictionary();
	stack s;
	init_stack(&s,8);
	int dec, k;
	FILE *fr = fopen("image_shrink.txt","w");
	char ch;
	while(1){
		fscanf(fp,"%c",&ch);
		printf("%c",ch);
		if(ch == 'e')
			break;
		if(isFull(s) == 0) {
			if(ch == ' ') {
				stack_push(&s,dictionary[10][3]);
				stack_push(&s,dictionary[10][2]);
				stack_push(&s,dictionary[10][1]);
				stack_push(&s,dictionary[10][0]);	 
			}
			else {
				k = ch - '0';
	//			printf("%d",k);
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
			fprintf(fr,"%c",dec);
//			printf("%c",dec);
			if(ch == ' ') {
				stack_push(&s,dictionary[10][3]);
				stack_push(&s,dictionary[10][2]);
				stack_push(&s,dictionary[10][1]);
				stack_push(&s,dictionary[10][0]);	 
			}
			else {
				k = ch - '0';
				stack_push(&s,dictionary[k][3]);
				stack_push(&s,dictionary[k][2]);
				stack_push(&s,dictionary[k][1]);
				stack_push(&s,dictionary[k][0]);
			}
		}			
		
	}
	fprintf(fr,"%c",EOF);
	fclose(fr);

}


void bit_decode_image(){
	
	FILE *fr = fopen("image_shrink.txt","r");
	FILE *fw = fopen("image_out.txt","w");
	
	int bin, bin1, bin2, bin3, bin4;
	char ch;
	fscanf(fr,"%c",&ch);
	int i =0;
	while(ch != EOF){
		
		bin = ch;
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
	//		printf(" ");
			fprintf(fw," ");
		}
		else {
//			printf("%d",bin4-1);
			fprintf(fw,"%d",bin4-1);
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
	//		printf(" ");
			fprintf(fw," ");
		}
		else{
//			printf("%d",bin4-1);		
			fprintf(fw,"%d",bin4-1);
		}
		fscanf(fr,"%c",&ch);
		i++;
	}	


}

void convert_txt_into_pgm(){
	pgm_Image Image;
	FILE *fr = fopen("image_info.txt","r");
	fscanf(fr,"%s",Image.type);
	fscanf(fr,"%d %d",&Image.height,&Image.width);
	fscanf(fr,"%d",&Image.max_gray_scale);
	int code_arr[256];
	int i, num1, num2, j, temp;
	
	for(i=0;i<256;i++){
		fscanf(fr,"%d %d",&num1, &num2);
		code_arr[num2] = num1;
		printf("\n%d %d",num1,num2);
	}
	fclose(fr);
	
	Image.pixel_array = (int**)malloc(sizeof(int*)*Image.height);

	for(i=0;i<Image.height;i++)
		*(Image.pixel_array + i) = (int*)malloc(sizeof(int)*Image.width);

	//writing txt back into image file
	FILE *ftxt, *fimg;
	ftxt = fopen("image_out.txt","r");
	fimg = fopen("img.pgm","wb");
	
	fprintf(fimg,"%s\n",Image.type);
	fprintf(fimg, "%d %d\n", Image.width, Image.height);
	fprintf(fimg, "%d\n",Image.max_gray_scale);
	
	for(i=0;i<Image.height;i++){
		for(j=0;j<Image.width;j++){
			fscanf(ftxt,"%d",&temp);
			Image.pixel_array[i][j] = code_arr[temp];
			fprintf(fimg,"%d ",Image.pixel_array[i][j]);
		}
		fprintf(fimg,"\n");
	}
			
	fclose(fimg);
	fclose(ftxt);		

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

void makestring(FILE *fp, int num){
	int k = numlen(num);
	char *s = (char*)malloc(sizeof(char)*k);
	int i;
	for(i = k-1;i >= 0;i--){
		s[i] = num%10 + '0';
		num = num/10;
	//	printf("%d %c ",num,s[i]);
	}
	fprintf(fp,"%s ",s);
}


