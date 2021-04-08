#include <stdio.h>

typedef struct pixel_node{
	int OFFSET;
	int Red, Green, Blue;
	struct pixel_node *next, *prev;
}pixel_node;

typedef pixel_node* pixel_list;

void init_pixel_list(pixel_list *l);
void insert_pixel_list(pixel_list *l, int R, int G, int B,int set);
void traverse_pixel_list(pixel_list l);
int pixel_list_length(pixel_list l);
void pixel_list_remove_unwanted(pixel_list *l);
void pixel_list_modify(pixel_list l);
void delete_pixel_list(pixel_list *l);
void print_pixel_list_in_file(pixel_list l, FILE *fp, int dimension);
