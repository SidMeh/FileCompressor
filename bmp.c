#include <stdio.h>
#include <stdlib.h>
#include "max_heap.h"

int numlen(int num);
void makestring(FILE *fp, int num);
int code_arr[256][2];
void init_code_arr();

int main() {

int i, j;
char filename[] = "image.bmp";
int data = 0, offset, bpp = 0, width, height;
long bmpsize = 0, bmpdataoff = 0;
int** image;
int temp = 0;
init_code_arr();
// Reading the BMP File
FILE* image_file;
image_file = fopen(filename, "rb");
if (image_file == NULL)
{
    printf("Error Opening File!!");
    exit(1);
}
else 
{
  	
    // Set file position of the 
    // stream to the beginning
    // Contains file signature 
    // or ID "BM"
    offset = 0;
      
    // Set offset to 2, which 
    // contains size of BMP File
    offset = 2;
      
    fseek(image_file, offset, SEEK_SET);
      
    // Getting size of BMP File
    fread(&bmpsize, 4, 1, image_file);
      
    // Getting offset where the
    // pixel array starts
    // Since the information 
    // is at offset 10 from 
    // the start, as given 
    // in BMP Header
    offset = 10; 
      
    fseek(image_file, offset, SEEK_SET);
      
    // Bitmap data offset
    fread(&bmpdataoff, 4, 1, image_file);
      
    // Getting height and width of the image
    // Width is stored at offset 18 and height
    // at offset 22, each of 4 bytes
    fseek(image_file, 18, SEEK_SET);
      
    fread(&width, 4, 1, image_file);
      
    fread(&height, 4, 1, image_file);
      
    // Number of bits per pixel
    fseek(image_file, 2, SEEK_CUR);
      
    fread(&bpp, 2, 1, image_file);
      
    // Setting offset to start of pixel data
    fseek(image_file, bmpdataoff, SEEK_SET);
      
    // Creating Image array
    image = (int**)malloc(height * sizeof(int*));
    for (i = 0; i < height; i++)
    {
        image[i] = (int*)malloc(width * sizeof(int));
    }
      
    // int image[height][width] 
    // can also be done
    // Number of bytes in the 
    // Image pixel array
    int numbytes = (bmpsize - bmpdataoff) / 3; 
      
    // Reading the BMP File 
    // into Image Array
    max_heap h;
    init_max_heap(&h);
    FILE *fpr;
    fpr = fopen("image_read.txt","w");
    for (i = 0; i < height; i++) 
    {
        for (j = 0; j < width; j++)
        {
            fread(&temp, 3, 1, image_file);
              
            // the Image is a 
            // 24-bit BMP Image
            temp = temp & 0x0000FF; 
            image[i][j] = temp;
            code_arr[temp][0]++;
           // printf("%d ",temp);
     //      makestring(fpr,temp);
           // fprintf(fpr,"%d ",temp);
        }
    }
    for(i = 0;i< 256;i++)
    	insert_max_heap(&h,code_arr[i][0],i);
    	map_code_via_heap(h,code_arr);
    
    for (i = 0; i < height; i++) 
    {
        for (j = 0; j < width; j++)
        {    temp = image[i][j];
        		makestring(fpr,code_arr[temp][1]);
    		}
    	}
    fprintf(fpr,"%d ",-1);
    fclose(fpr);
    
    
}
	FILE *fc = fopen("code.txt","w");
	for(i=0;i<256;i++){
		printf("%d %d\n",i,code_arr[i][0]);
		fprintf(fc,"%d %d\n",i,code_arr[i][1]);	
	}
FILE *fpr = fopen("image_read.txt","r");
fscanf(fpr,"%d",&temp);
while(temp != -1){
fscanf(fpr,"%d",&temp);
if(temp == -1)
break;
printf("%d ",temp);
}
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

void init_code_arr(){
	int i;
	for(i = 0;i<256;i++){
		code_arr[i][0] = 0;
		code_arr[i][1] = 0;
	}
}





















