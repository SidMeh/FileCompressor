typedef struct stack{
	int *arr;
	int top;
	int size;
}stack;
void init_stack(stack *s,int n);
void stack_push(stack *s,int n);
int pop_stack(stack *s);
int isEmpty(stack s);
int isFull(stack s);
int peek_stack(stack s);
