#include <stdio.h>
#include <stdlib.h>
#include "max_heap.h"

/*
int main() {
	max_heap h;
	init_max_heap(&h);
	insert_max_heap(&h,12,34);
	insert_max_heap(&h,32,34);
	traverse_max_heap(h);
	return 0;
}*/

void init_max_heap(max_heap *h){
	h->rear = -1;
	int i;
	for(i=0;i<256;i++){
		h->arr[i][0] = 0;
		h->arr[i][1] = 0;
	}
}

void insert_max_heap(max_heap *h, int key, int ascii) {
	
	if(h->rear == -1){
		h->arr[++h->rear][0] = key;
		h->arr[h->rear][1] = ascii;
		return;
	}
	
	if(h->rear >= 256)
		return;
		
	h->arr[++h->rear][0] = key;
	h->arr[h->rear][1] = ascii;	
	int i = h->rear, j = (i-1)/2;
	int temp_key, temp_ascii;
	while(i >= 0 && h->arr[i][0] >= h->arr[j][0]){
		temp_key = h->arr[i][0];
		h->arr[i][0] = h->arr[j][0];
		h->arr[j][0] = temp_key;
		temp_ascii = h->arr[i][1];
		h->arr[i][1] = h->arr[j][1];
		h->arr[j][1] = temp_ascii;
		i = j;
		j = (i-1)/2;
		if(i == 0)
			break;
	}
}		
		
void traverse_max_heap(max_heap h){
	
	int i,j;
	for(i=0;i<=h.rear;i++){
		j = (i-1)/2;
		printf("\n%d %d %d",h.arr[i][0], h.arr[i][1],h.arr[j][0]);
		if(h.arr[i][0] > h.arr[j][0]){
			printf("ERROR");
			break;
		}
	}

}
			
void map_code_via_heap(max_heap h,int code_arr[256][2]){
	
	int i;
	for(i=0;i<256;i++){
		code_arr[h.arr[i][1]][1] = i;
	}
}		
		
		
		
		
		
		
		
		
		
		
