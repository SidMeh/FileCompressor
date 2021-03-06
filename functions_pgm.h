#include <stdio.h>
typedef struct pgm_Image{
	char type[4];
	int height;
	int width;
	int max_gray_scale;
	int **pixel_array;
}pgm_Image;

typedef struct ppm_Image{
	char header[4];
	int height, width;
	int max_color_scale;
	int ***pixel_array;
}ppm_Image;

int dictionary[11][4];
void init_dictionary();
int numlen(int num);
void makestring(FILE *fp, int num);

void init_pgm_image_from_file(FILE *fp, pgm_Image *img);
void convert_image_from_pgm_to_txt(pgm_Image img,char *str);
void bit_encode_image(FILE *fp,char *str);
void bit_decode_image(FILE *fp);
void convert_txt_into_pgm(FILE *fp, FILE *ft);
void reduce_image_size(FILE *fp, FILE *fop);


void init_ppm_image_from_file(FILE *fp,ppm_Image* Image);
void convert_image_from_ppm_to_txt(ppm_Image Image, char *str);
void convert_txt_data_to_ppm();
void reduce_image_size_ppm(FILE *fp, FILE *fop);
