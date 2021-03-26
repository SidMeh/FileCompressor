typedef struct queue{
int rear,size,front;
int *a;
}queue;


int dequeue(queue *q);
void init(queue *q, int d);
int isFullq(queue q);
int isEmptyq(queue q);
void enqueue(queue *q, int d);
