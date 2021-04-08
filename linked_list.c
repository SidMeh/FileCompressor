#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

/*
int main(){
	pixel_list l;
	init_pixel_list(&l);
	int i;
	for(i=0;i< 90;i++){
	insert_pixel_list(&l,7,8,9,0);
	insert_pixel_list(&l,17,48,99,1);
	}
	pixel_list_modify(l);
	pixel_list_remove_unwanted(&l);
	delete_pixel_list(&l);
	traverse_pixel_list(l);
	printf("\n Length : %d",pixel_list_length(l));
	
	return 0;
}*/

void init_pixel_list(pixel_list *l){
	*l = NULL;
	return;
}

void insert_pixel_list(pixel_list *l, int R, int G, int B,int set){
	pixel_node *temp, *p;
	temp = (pixel_node*)malloc(sizeof(pixel_node));
	temp->next = NULL;
	temp->prev = NULL;
	temp->OFFSET = set;
	temp->Red = R;
	temp->Green = G;
	temp->Blue = B;
	
	if(*l == NULL){
		*l = temp;
		return;
	}
	
	p = *l;
	while(p->next)
		p = p->next;
	p->next = temp;
	temp->prev = p;
	return;
}
	
void traverse_pixel_list(pixel_list l){
	pixel_node *p = l;
	while(p){
		printf("%d %d %d %d \n",p->Red, p->Green,p->Blue,p->OFFSET);
		p = p->next;
	}
}
	
int pixel_list_length(pixel_list l){
	pixel_node *p = l;
	if(p == NULL)
		return 0;
		
	int len = 0;
	while(p){
		p = p->next;
		len = len + 1;
	}
	return len;
}	
	
void pixel_list_remove_unwanted(pixel_list *l){
	if(*l == NULL)
		return;
	
	pixel_node *p = *l;
	while(p){
		if(p->OFFSET == 0){
			if(p == *l){
				*l = p->next;
				free(p);
			}
			else if(p->next == NULL){
				p->prev = NULL;
				free(p);
			}
			else{
				p->prev->next = p->next;
				free(p);
			}
		}
		p = p->next;
	}	
	return;
}
	
void pixel_list_modify(pixel_list l){	
	pixel_node *p = l;
	while(p){
		if(p->OFFSET == 0){
			if(p->prev){
				p->prev->Red = (p->Red + p->prev->Red)/2;
				p->prev->Green = (p->Red + p->prev->Green)/2;
				p->prev->Blue = (p->Red + p->prev->Blue)/2;
			}
			if(p->next){
				p->next->Red = (p->Red + p->next->Red)/2;
				p->next->Green = (p->Red + p->next->Green)/2;
				p->next->Blue = (p->Red + p->next->Blue)/2;
			}	
		}
		
		p = p->next;
	}
	return;
}
	
void delete_pixel_list(pixel_list *l){
	if(*l == NULL)
		return;
	
	pixel_node *p = *l;
	while(*l){
		p = *l;
		*l = (*l)->next;
		free(p);
	}
	*l = NULL;
	return;
}	

void print_pixel_list_in_file(pixel_list l, FILE *fp, int dimension){
	int i;
	if(pixel_list_length(l) == 0){
		for(i=0;i< dimension;i++){
			fprintf(fp, "255 255 255 ");
		}
		return;
	}
	for(i=0;i<dimension;i++){
		if(l == NULL)
			fprintf(fp, "255 255 255 ");
		else{
			fprintf(fp, "%d %d %d ", l->Red, l->Green, l->Blue);
			l = l->next;
		}
	}
	return;
}	
	
	
	
	
	
	
	
	
	
	
