#include <stdlib.h>
#include "stack.h"


void init_stack(stack *s,int n){
	int i;
	s->arr = (int*)malloc(sizeof(int)*n);
	for(i=0;i<n;i++){
		s->arr[i] = 0;
	}
	s->top = -1;
	s->size = n;
}

int isEmpty(stack s){

	if(s.top == -1)
		return 1;
		
	else
		return 0;
		
}

int isFull(stack s){

	if(s.top == s.size-1){
		return 1;
	}	
	else
		return 0;
		
}

int pop_stack(stack *s){

	if(s->top == -1)
		return 0;
		
	 int k = s->arr[s->top];
	 s->top = s->top - 1;
	 return k;
	 
}

void stack_push(stack *s,int k){

	if(s->top == s->size-1)
		return;
		
	s->top = s->top + 1;
	s->arr[s->top] = k;
	return ;
	
}

int peek_stack(stack s){
	return s.arr[s.top];
}
