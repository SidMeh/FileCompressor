#include <stdio.h>
#include <stdlib.h>
#include "max_heap.h"
#include "stack.h"
#include "functions_pgm.h"
#include "linked_list.h"
#include <string.h>
#include <math.h>

#define OFFSET 1
#define OFSET 3
#define BW_VALUE 0
#define R 0
#define G 1
#define B 2

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
//	Image->height = 3*Image->height;
//	Image->width = 3*Image->width;
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

void convert_image_from_pgm_to_txt(pgm_Image Image, char *str){
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
	bit_encode_image(fp,str);
//	bit_decode_image();
}


void bit_encode_image(FILE *fp,char *str) {
	init_dictionary();
	stack s;
	init_stack(&s,8);
	int dec, k;
	FILE *fr = fopen(str,"w");
	char ch;
	while(1){
		fscanf(fp,"%c",&ch);
//		printf("%c",ch);
		if(ch == 'e')
			break;
			if(ch == '-')
				continue;
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


void bit_decode_image(FILE *fr){
//	FILE *fr = fopen(str,"r");
//	printf("YES");
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

void convert_txt_into_pgm(FILE *fimg, FILE *ftxt){
	bit_decode_image(ftxt);
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
//		printf("\n%d %d",num1,num2);
	}
	fclose(fr);
	
	Image.pixel_array = (int**)malloc(sizeof(int*)*Image.height);

	for(i=0;i<Image.height;i++)
		*(Image.pixel_array + i) = (int*)malloc(sizeof(int)*Image.width);

	//writing txt back into image file
	FILE *ftxt1;
	ftxt1 = fopen("image_out.txt","r");
//	fimg = fopen("img.pgm","wb");
	
	fprintf(fimg,"%s\n",Image.type);
	fprintf(fimg, "%d %d\n", Image.width, Image.height);
	fprintf(fimg, "%d\n",Image.max_gray_scale);
	
	for(i=0;i<Image.height;i++){
		for(j=0;j<Image.width;j++){
			fscanf(ftxt1,"%d",&temp);
			Image.pixel_array[i][j] = code_arr[temp];
			fprintf(fimg,"%d ",Image.pixel_array[i][j]);
		}
		fprintf(fimg,"\n");
	}
			
	fclose(fimg);
	fclose(ftxt1);		

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


void reduce_image_size(FILE *fp, FILE *fop){
	printf("Enter the percentage to reduction of the .pgm image : ");
	int percentage;
	scanf("%d",&percentage);
	if(percentage == -1)
		return;
	percentage = percentage;
	float ratio = (1.0*percentage)/100;
	pgm_Image Image, Image_out;
//	FILE *fp = fopen("pgmimg.pgm","rb");
	fscanf(fp, "%s", Image.type);
	fscanf(fp, "%d %d", &Image.width, &Image.height);
	fscanf(fp, "%d", &Image.max_gray_scale);
	
	int x, x1, y, y1, i, j, i1 = -1, j1 = 0;
	float k, c;
	x = Image.width;
	y = Image.height;
	float k1 = ratio*x/y;
	k = sqrt(k1);
	c = ratio/k;
	x1 = k*x;
	y1 = c*y;
	Image_out.width = x1;
	Image_out.height = y1;
	
	int ***pixel_arr;
	pixel_arr = (int***)malloc(sizeof(int**)*Image.height);
	for(i=0;i<Image.height;i++)
		pixel_arr[i] = (int**)malloc(sizeof(int*)*Image.width);
	for(i=0;i<Image.height;i++){
		for(j=0;j<Image.width;j++){
			pixel_arr[i][j] = (int*)malloc(sizeof(int)*2);
		}
	}
	
	Image.pixel_array = (int**)malloc(sizeof(int*)*Image.height);
	for(i=0;i<Image.height;i++)
		Image.pixel_array[i] = (int*)malloc(sizeof(int)*Image.width);
	
	int X_REMOVAL = x - x1, Y_REMOVAL = y - y1, l = 0;
	int X_INTERVAL, Y_INTERVAL;
	X_INTERVAL = x/X_REMOVAL;
	Y_INTERVAL = y/Y_REMOVAL;
	printf("\nInput image header/type : %s", Image.type);
	printf("\nInput image height : %d", Image.height);
	printf("\nInput image width : %d", Image.width);
	printf("\nInput image maximum gray scale : %d",Image.max_gray_scale);
	
	strcpy(Image_out.type,Image.type);
	Image_out.height = y1;
	Image_out.width = x1;
	Image_out.max_gray_scale =  Image.max_gray_scale;
	printf("\nOutput image header/type : %s", Image_out.type);
	printf("\nOutput image height : %d", Image_out.height);
	printf("\nOutput image width : %d", Image_out.width);
	printf("\nOutput image maximum gray scale : %d",Image_out.max_gray_scale);
	
	printf("\nX_INTERVAL : %d",X_INTERVAL);
	printf("\nY_INTERVAL : %d",Y_INTERVAL);
	//Loading input image into structure/RAM
	for(i = 0; i < Image.height; i++){
		for(j = 0; j < Image.width; j++){
			fscanf(fp,"%d ",&Image.pixel_array[i][j]);
			pixel_arr[i][j][BW_VALUE] = Image.pixel_array[i][j];
			if( j%X_INTERVAL == 0){
				pixel_arr[i][j][OFFSET] = 0;
				l++;
			}
			else
				pixel_arr[i][j][OFFSET] = 1;
		}
	}
	printf(" %d ",l);
	//adjusting pixel values i
	int prev_i, prev_j, next_i, next_j;
	for(i=0;i< Image.height; i++){
		for(j = 0; j < Image.width; j++){
			if(pixel_arr[i][j][OFFSET] == 0){
				prev_i = i-1;
				next_i = i+1;
				prev_j = j-1;
				next_j = j+1;
				if(prev_i >= 0 && prev_j >= 0)
					pixel_arr[prev_i][prev_j][BW_VALUE] = (pixel_arr[prev_i][prev_j][BW_VALUE] + pixel_arr[prev_i][prev_j][BW_VALUE])/2;
				if(next_i <= Image.height-1 && next_j <= Image.width-1)
					pixel_arr[next_i][next_j][BW_VALUE] = (pixel_arr[next_i][next_j][BW_VALUE] + pixel_arr[next_i][next_j][BW_VALUE])/2;
			}	
		}
	}
	//assigning
	Image_out.pixel_array = (int**)malloc(sizeof(int*)*Image.height);
	for(i=0;i<Image.height;i++)
		Image_out.pixel_array[i] = (int*)malloc(sizeof(int)*Image.width);
		
	for(i=0;i<Image.height;i++){
		j1 = 0;
		for(j = 0; j< Image.width;j++){
			if(j == 0){
				i1++;
				j1 = 0;
			}
			if(pixel_arr[i][j][OFFSET] == 1)
				Image_out.pixel_array[i1][j1++] = pixel_arr[i][j][BW_VALUE];
		}
	}			
	
	//printing image;
	fclose(fp);
//	fp = fopen("imgg.pgm","wb");
	fprintf(fop, "%s\n",Image.type);
	fprintf(fop, "%d %d\n", x1, y1);
	fprintf(fop,"%d\n",Image_out.max_gray_scale);
	for(i = 0; i < Image_out.height; i++){
		for(j = 0; j < Image_out.width; j++){
//			if(pixel_arr[i][j][OFFSET] == 1)
				fprintf(fop, "%d ", Image_out.pixel_array[i][j]);
		}
	}
	fclose(fop);
	
}



void init_ppm_image_from_file(FILE *fp,ppm_Image* Image){
	fscanf(fp,"%s",Image->header);
	fscanf(fp,"%d %d",&Image->width,&Image->height);
	fscanf(fp,"%d",&Image->max_color_scale);
	printf("Image header :%s\n",Image->header);
	printf("Image height :%d\n",Image->height);
	printf("Image width :%d\n",Image->width);
	printf("Image max color scale :%d\n",Image->max_color_scale);
	
	// reading pixel array;
	int i = 0, j= 0;
	Image->pixel_array = (int***)malloc(sizeof(int**)*Image->height);
	for(i=0;i<Image->height;i++)
		Image->pixel_array[i] = (int**)malloc(sizeof(int*)*Image->width);
	
	for(i=0;i< Image->height;i++){
		for(j=0;j< Image->width;j++){
			Image->pixel_array[i][j] = (int*)malloc(sizeof(int*)*3);
		}
	}
	
	FILE *fr;
	fr = fopen("image_read.txt","w");
	
	for(i=0; i < Image->height; i++){
		for(j = 0;j < Image->width;j++){
			fscanf(fp,"%d %d %d ",&Image->pixel_array[i][j][R],&Image->pixel_array[i][j][G],&Image->pixel_array[i][j][B]);
			fprintf(fr,"%d %d %d ",Image->pixel_array[i][j][R],Image->pixel_array[i][j][G],Image->pixel_array[i][j][B]);
		}
//		printf("\n");
	}
}


void convert_image_from_ppm_to_txt(ppm_Image Image,char *str1){
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
			temp = Image.pixel_array[i][j][R];
			code_arr[temp][0]++;
			temp = Image.pixel_array[i][j][G];
			code_arr[temp][0]++;
			temp = Image.pixel_array[i][j][B];
			code_arr[temp][0]++;			
		}
	}
	for(i=0;i<256;i++)
		insert_max_heap(&h,code_arr[i][0],i);
	map_code_via_heap(h,code_arr);
	for(i=0;i<256;i++){
//		printf("\n%d %d",i,code_arr[i][1]);		
		if(code_arr[i][1] > 255)
			printf("ERROR");
	}
	FILE *fr = fopen("image_read.txt","w");	
	
	for(i=0;i<Image.height;i++){
		for(j=0;j<Image.width;j++){
			temp = Image.pixel_array[i][j][R];
			makestring(fr,code_arr[temp][1]);
			temp = Image.pixel_array[i][j][G];
			makestring(fr,code_arr[temp][1]);
			temp = Image.pixel_array[i][j][B];
			makestring(fr,code_arr[temp][1]);
			
		}
	}	
	fprintf(fr,"%c",'e');
	fclose(fr);
	
	FILE *ft = fopen("image_info.txt","w");
	fprintf(ft,"%s\n",Image.header);
	fprintf(ft,"%d %d\n",Image.height,Image.width);
	fprintf(ft,"%d\n",Image.max_color_scale);
	for(i = 0; i < 256 ; i++){
		fprintf(ft,"%d %d\n",i,code_arr[i][1]);
	} 
	fclose(ft);
	fr = fopen("image_read.txt","r");
	char *str;
	bit_encode_image(fr,str1);
}


void convert_txt_data_to_ppm(FILE *fp, FILE *ftxt){
	
//	FILE *fp = fopen("img.ppm","wb");
	ppm_Image Image;
	bit_decode_image(ftxt);
	FILE *fr = fopen("image_info.txt","r");
	fscanf(fr,"%s",Image.header);
	fscanf(fr,"%d %d", &Image.width, &Image.height);
	fscanf(fr,"%d", &Image.max_color_scale);
	
	fprintf(fp,"%s\n",Image.header);
	fprintf(fp,"%d %d\n", Image.width, Image.height);
	fprintf(fp,"%d\n",Image.max_color_scale);
	printf("Header :%s\n",Image.header);
	printf("Width & Height: %d %d\n", Image.width, Image.height);
	printf("Maximum colour scale :%d\n",Image.max_color_scale);
	int i, j, num1, num2, num3, code_arr[256];
	for(i =0; i < 256; i++){
		fscanf(fr,"%d %d", &num1, &num2);
		code_arr[num2] = num1;
	}
	
	Image.pixel_array = (int***)malloc(sizeof(int**)*Image.height);
	for(i=0;i<Image.height;i++)
		Image.pixel_array[i] = (int**)malloc(sizeof(int*)*Image.width);
	
	for(i=0;i< Image.height;i++){
		for(j=0;j< Image.width;j++){
			Image.pixel_array[i][j] = (int*)malloc(sizeof(int*)*3);
		}
	}
	
	FILE *ft = fopen("image_out.txt","r");
	for(i=0;i<Image.height;i++){
		for(j=0;j< Image.width;j++){
			fscanf(ft,"%d %d %d", &num1, &num2, &num3);
//			printf("%d %d %d ",num1,num2,num3);
			Image.pixel_array[i][j][R] = code_arr[num1];
			Image.pixel_array[i][j][G] = code_arr[num2];
			Image.pixel_array[i][j][B] = code_arr[num3];
			fprintf(fp,"%d %d %d ", Image.pixel_array[i][j][R], Image.pixel_array[i][j][G], Image.pixel_array[i][j][B]);
		}
	}
	
	fclose(fp);
}


void reduce_image_size_ppm(FILE *fp, FILE *fop){
	printf("Enter the percentage to reduction of the .ppm image : ");
	int percentage, i, j;
	scanf("%d",&percentage);
	float ratio = (1.0*percentage)/100;
//	FILE *fp = fopen("img.ppm","rb");
	ppm_Image Image;
	fscanf(fp, "%s", Image.header);
	fscanf(fp, "%d %d", &Image.width, &Image.height);
	fscanf(fp, "%d", &Image.max_color_scale);
	printf("%s %d %d %d ", Image.header, Image.width, Image.height, Image.max_color_scale);
	Image.pixel_array = (int***)malloc(sizeof(int**)*Image.height);
	for(i=0;i<Image.height;i++)
		Image.pixel_array[i] = (int**)malloc(sizeof(int*)*Image.width);
	
	for(i=0;i< Image.height;i++){
		for(j=0;j< Image.width;j++){
			Image.pixel_array[i][j] = (int*)malloc(sizeof(int*)*3);
		}
	}
	for(i = 0;i < Image.height; i++){
		for(j = 0;j < Image.width; j++){
			fscanf(fp,"%d %d %d ", &Image.pixel_array[i][j][R], &Image.pixel_array[i][j][G], &Image.pixel_array[i][j][B]);
		}
	}
	int x, x1, y, y1 ;
	float k, c;
	x = Image.width;
	y = Image.height;
	float k1 = ratio*x/y;
	k = sqrt(k1);
	c = ratio/k;
	x1 = k*x;
	y1 = c*y;
	int X_REMOVAL = x - x1, Y_REMOVAL = y - y1, l = -1, set;
	int X_INTERVAL, Y_INTERVAL;
	X_INTERVAL = x/X_REMOVAL;
	Y_INTERVAL = y/Y_REMOVAL;
	
	pixel_list *pixl;
	pixl = (pixel_list*)malloc(sizeof(pixel_list)*x1);
	for(i=0;i< x1;i++)
		init_pixel_list(&pixl[i]);
	
	for(i=0;i< x;i++){
		if(i%X_INTERVAL != 0)
			l++;
		for(j=0;j< y;j++){
			set = 1;
			if(j%Y_INTERVAL == 0)
				set = 0;
			if(i%X_INTERVAL != 0)
				insert_pixel_list(&pixl[l], Image.pixel_array[i][j][R], Image.pixel_array[i][j][G], Image.pixel_array[i][j][B], set);
		}
	}
			 
	for(i=0;i<x1;i++){
		pixel_list_modify(pixl[i]);
		pixel_list_remove_unwanted(&pixl[i]);
//		int k = pixel_list_length(pixl[i]);
//		printf(" %d",k);
	}
	
//	FILE *fop = fopen("imgg.ppm","wb");
	if(fop == NULL)
		return;
		
	fprintf(fop, "%s\n", Image.header);
	fprintf(fop, "%d %d\n", x1, y1);
	fprintf(fop, "%d\n", Image.max_color_scale);
	
	for(i=0;i<x1;i++)
		print_pixel_list_in_file(pixl[i],fop,y1);
		
	fclose(fop);
	
}














