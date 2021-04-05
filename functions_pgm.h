#include <stdio.h>
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
void reduce_image_size(int percentage);
