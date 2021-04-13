#include <stdio.h>
#include <stdlib.h>
#include "functions_pgm.h"
#include "max_heap.h"
#include <string.h>



void makestring(FILE *fp, int num);
int numlen(int num);

int main(int argc , char **argv){
//	FILE *fp = fopen("pgmimg.pgm", "rb");
//	pgm_Image Image;
//	init_pgm_image_from_file(fp,&Image);
//	convert_image_from_pgm_to_txt(Image);
//	convert_txt_into_pgm();
/*	FILE *fp = fopen("pgmimg.ppm","rb");
	if(fp == NULL)
		return 0;
	ppm_Image Image;
	init_ppm_image_from_file(fp,&Image);
	convert_image_from_ppm_to_txt(Image);
	convert_txt_data_to_ppm();*/
	
	FILE *fint, *fimg, *fimg1, *ftxt;
	
	if(strcmp(argv[1],"compress") == 0){
	
		if(strcmp(argv[3],".pgm") == 0) {
			pgm_Image Image;
			fimg = fopen(argv[4],"rb");
			ftxt = fopen(argv[6],"w");
			fint = fopen("image_read.txt","w");
			init_pgm_image_from_file(fimg, &Image);
			convert_image_from_pgm_to_txt(Image,argv[6]);
	
		}
		
		else if(strcmp(argv[1],"compress") == 0){
		
			if(strcmp(argv[3],".ppm") == 0){
				ppm_Image Image1;
				fimg = fopen(argv[4],"rb");
				ftxt = fopen(argv[6],"w");
				fint = fopen("image_read.txt","w");
				init_ppm_image_from_file(fimg,&Image1);
				convert_image_from_ppm_to_txt(Image1,argv[6]);		
			}
		}
	
	}
	
	
	else if(strcmp(argv[1],"decompress") == 0){
		if(strcmp(argv[3],".pgm") == 0){
			pgm_Image Image;
			fimg = fopen(argv[6],"wb");
			ftxt = fopen(argv[4],"r");			
			convert_txt_into_pgm(fimg,ftxt);
		}
		
		else if(strcmp(argv[3],".ppm") == 0){
			printf("YES");
			ppm_Image Image1;
			fimg = fopen(argv[6],"wb");
			ftxt = fopen(argv[4],"r");			
			convert_txt_data_to_ppm(fimg,ftxt);
		}
		
	}
	
	else if(strcmp(argv[1],"reduction") == 0){
		if(strcmp(argv[3],".ppm") == 0){
			fimg = fopen(argv[4],"rb");
			fimg1 = fopen(argv[6],"wb");
			reduce_image_size_ppm(fimg,fimg1);
		}
		
		if(strcmp(argv[3],".pgm") == 0){
			fimg = fopen(argv[4],"rb");
			fimg1 = fopen(argv[6],"wb");
			reduce_image_size(fimg,fimg1);
		}
		
	}	
	
	return 0;
}

//compress/decompress
// argv     1             2            3              4              5          6.

//meaning  comp/dcomp   mode          .pgm/.ppm      source file     to         destination

//size reduction
// argv     1             2             3            4             5          6     
//meaning   rediction    mode       .pgm/.ppm      source file    to          destination 























