#include <stdio.h>
#include <limits.h>
#include <math.h>  

void main() 
{ 

    int i, j, temp = 0; 
	float temp1;
    int width = 50, height = 50; 

  

    // Suppose the 2D Array to be converted to Image is as given below 

  
  

    FILE* pgmimg; 

    pgmimg = fopen("tm.ppm", "wb"); 

  

    // Writing Magic Number to the File 

    fprintf(pgmimg, "P3\n");  

  
	int image[20][20];
    // Writing Width and Height 

    fprintf(pgmimg, "%d %d\n", width, height);  

  	FILE *fp = fopen("tm.txt","w");

    // Writing the maximum gray value 

    fprintf(pgmimg, "255\n");  

    int count = 0; 

    for (i = 0; i < height; i++) { 

        for (j = 0; j < width; j++) { 

            temp = image[i][j]; 

  	//		temp1 = 0.00023;
		temp = ((i * j)%255);
            // Writing the gray values in the 2D array to the file 

            fprintf(pgmimg, "%d %d %d ",(i + j)%255,abs(i-j)%255, (i*j)%255); 
            printf("%d %d %d |", (i + j)%255,abs(i-j)%255,(i*j)%255); 
	//		fprintf(pgmimg, "%d ", temp);
		fprintf(fp, "%d %d %d ", (i + j)%255,abs(i-j)%255,(i*j)%255);
        } 

        fprintf(pgmimg, "\n"); 
		printf("\n");
    } 

    fclose(pgmimg);
    fclose(fp);
    pgmimg = fopen("tm1.ppm", "wb"); 
    int num1, num2, num3;
    fprintf(pgmimg, "P3\n"); 
    fp = fopen("img.txt","r");
 
       fprintf(pgmimg, "%d %d\n", width, height);  
        fprintf(pgmimg, "255\n");
       for (i = 0; i < height; i++) { 

        for (j = 0; j < width; j++) { 
        		fscanf(fp,"%d %d %d ",&num1,&num2,&num3);
    fprintf(pgmimg, "%d %d %d ", num1,num2,num3); 
    
    }
    }
    
    
    
    
    
    
    
} 

