#include <stdio.h>
#include <stdlib.h>
#include "functions_pgm.h"
#include "max_heap.h"




void makestring(FILE *fp, int num);
int numlen(int num);

int main(){
//	FILE *fp = fopen("pgmimg.pgm", "rb");
//	pgm_Image Image;
//	init_pgm_image_from_file(fp,&Image);
//	convert_image_from_pgm_to_txt(Image);
//	convert_txt_into_pgm();
	FILE *fp = fopen("tm.ppm","rb");
	ppm_Image Image;
	init_ppm_image_from_file(fp,&Image);
	convert_image_from_ppm_to_txt(Image);
	convert_txt_data_to_ppm();
	return 0;
}


/*
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
*/































