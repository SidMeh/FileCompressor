#include <stdio.h>
#include <stdlib.h>
#include "Circular_Queue.h"

void init(queue *q, int d) {
	q->size = d;
	q->rear = -1;
	q->front = -1;
	q->a = (int*)malloc(sizeof(int)*d);
}

int isFullq(queue q) {
	if((q.front == -1 && q.rear == q.size-1)|| q.rear + 1 == q.front) {
		printf("The queue is FULL.");
		return 1;
}
	return 0;
}

int isEmptyq(queue q) {
	if(q.front == -1 ) {
		printf("The queue is empty.");	
		return 1;
	}
	return 0;
}

void enqueue(queue *q, int d) {
	if(isFullq(*q)) {
			return;
	}
	if(q->rear != q->size-1) {
		q->rear = q->rear + 1;
		q->a[q->rear] = d;	
	}
	else if(q->rear == q->size-1) {
		q->rear = 0;
		q->a[q->rear] = d;
	}
	if(q->front == -1)
		q->front = 0;
}

int dequeue(queue *q) {
	if(isEmptyq(*q)) {
		return -1;
	}
	int data = q->a[q->front];
	if(q->front == q->rear) {
		q->front = -1;
		q->rear = -1;
		return data;
	}
	if(q->front == q->size-1)
		q->front == 0;
	else
		q->front = q->front + 1;
	return data;
	
	
}
