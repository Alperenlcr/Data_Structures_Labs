#include <stdio.h>
#include <stdlib.h>
#define QUEUE_SIZE 40

struct queue
{
    int rear, front, size, capacity;
    int arr[QUEUE_SIZE];
};

typedef struct queue queue;

queue* create_queue()
{
    queue* q = (queue*) malloc(sizeof(queue));
    q->front = 0;
    q->capacity = QUEUE_SIZE;
    q->rear = q->capacity - 1;
    q->size = 0;

    return q;
}

int is_empty(queue* q)
{
    return q->size == 0 ? 1 : 0;
}

int is_full(queue* q)
{
    return q->size == q->capacity-1 ? 1 : 0;
}

int front(queue* q)
{
    return q->arr[q->front];
}

int rear(queue* q)
{
    return q->arr[q->rear];
}

void enqueue(queue* q, int data)
{
    if (is_full(q))
        printf("Queue is empty can't enqueue!\n");
    else
    {
        q->rear = (q->rear + 1) % q->capacity;
        q->arr[q->rear] = data;
        q->size ++;
        printf("%d is enqueue to queue!\n", rear(q));
    }
}

void dequeue(queue* q)
{
    if (is_empty(q))
        printf("Queue is empty can't dequeue!\n");
    else
    {
        printf("%d is dequeued from queue!\n", front(q));
        q->front = (q->front + 1) % q->capacity;
        q->size --;
    }
}

void main()
{
    queue* q = create_queue();
    enqueue(q, 1);
    enqueue(q, 2);
    enqueue(q, 3);
    dequeue(q);
    dequeue(q);
    dequeue(q);
    dequeue(q);
}