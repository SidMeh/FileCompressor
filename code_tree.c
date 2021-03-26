#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "code_tree.h"

int arr1[11] = {1,2,3,4,5,6,7,8,9,10,11};
int arr2[11] = {16,32,48,64,80,96,112,128,144,160,176};
int arr3[121][2];

code_node default_node = {-1,"0101010",NULL,NULL};


void init_code_tree(code_tree *t) {

	*t = NULL;
	return;
}

code_node* get_code_node(int data,int code) {
	
	code_node *dn = &default_node;	
		
	if(code == 0) {
		printf("\nError code for data : %d\n",data);
		return dn;
	}
	
	code_node *nn;
	nn = (code_node*)malloc(sizeof(code_node));
	if(nn == NULL)
		return dn;
		
	nn->left = NULL;
	nn->right = NULL;
	nn->data = data;
	strcpy(nn->code,"0000000");
	
	int i = 6;
	int bit, num = code;
	while(i >= 0){
		bit = num%2;
		nn->code[i] = bit + '0';
		num = num/2;
		i--;
	}
	
	return nn;
	
}

void insert_code_tree(code_tree *t, int data, int code) {

	code_node *p = *t, *q = NULL;
	code_node *nn = get_code_node(data,code);
	code_node *dn = &default_node;
	if(nn == dn) {
		printf("\nError in inserting code for data.\n");
		return;
	}
	
	if(*t == NULL) {
		*t = nn;
		return;
	}
	
	while(p != NULL) {
		
		q = p;
		if(data > p->data)
			p = p->right;
		else if(data < p->data)
			p = p->left;
		else if(p->data == data)
			return;
			
	}
	
	if(data > q->data)
		q->right = nn;
	else if(data < q->data)
		q->left = nn;
	return;
	
}

void inorder_traverse(code_tree t) {
	
	if(t == NULL)
		return;
	
	inorder_traverse(t->left);
	printf("\n %d %s ",t->data,t->code);
	inorder_traverse(t->right);

}

void preorder_traverse(code_tree t) {
	
	if(t == NULL)
		return;
	
	printf("\n %d %s ",t->data,t->code);
	preorder_traverse(t->left);
	preorder_traverse(t->right);

}

void postorder_traverse(code_tree t) {
	
	if(t == NULL)
		return;
	
	postorder_traverse(t->left);
	postorder_traverse(t->right);
	printf("\n %d %s ",t->data,t->code);

}

void generate_code() {
	int i, j, k = 0;
	for(i = 0;i<11;i++){
		for(j=10;j>=0;j--){
			arr3[k][0] = arr1[i]+arr2[j];
			arr3[k][1] = k + 1;
//			printf("\n %d %d ",arr3[k][0],arr3[k][1]);
			k++;
		}
	}
}

void generate_tree(code_tree *t) {
	
	int k;
	for(k = 0; k < 121; k++) {
		insert_code_tree(t,arr3[k][0],arr3[k][1]);
	}
	
	return;
}

int height(code_tree t) {
	
	if(t == NULL)
		return -1;
		
	int h1 = height(t->left);
	int h2 = height(t->right);
	
	if(h1 > h2)
		return h1 + 1;
		
	else
		return h2 + 1;
		
}

char* get_code_for_data(code_tree t, int data) {

	code_node *p = t;
	int flag = 0;
	
	while(p != NULL) {
	
		if(data > p->data)
			p = p->right;
		else if(data < p->data)
			p = p->left;
		else if(data == p->data){
			flag = 1;
			break;
		}
	}
	
	if(flag == 0) {
		printf("Your algorithm is wrong !");
		return "\0";
	}
	
	else if(flag == 1) {
		return p->code;
	}
	
}
		
void detect_error(code_tree t){

	if(t == NULL)
		return;
		
	int sum = 0, i = 0;
	while(i < 7){
		sum = sum + (t->code[i] - '0');
		i++;
	}
	
	if(sum == 0)
		printf("Error");
	
	detect_error(t->left);
	detect_error(t->right);
	
}










