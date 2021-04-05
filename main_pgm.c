#include <stdio.h>
#include "functions_pgm.h"




int main(){
	FILE *fp = fopen("pgmimg.pgm", "rb");
	pgm_Image Image;
	init_pgm_image_from_file(fp,&Image);
	convert_image_from_pgm_to_txt(Image);
	convert_txt_into_pgm();
	return 0;
}



