#include<stdio.h>
#include<stdlib.h>
#define STACK_SIZE 40
struct stack
{
    int arr[STACK_SIZE];
    int top;
};


struct stack* s;

void create_stack()
{
    s->top = -1;
}

int peek()
{
    return s->arr[s->top];
}

int is_full()
{
    return STACK_SIZE == s->top+1 ? 1 : 0;
}

int is_empty()
{
    return -1 == s->top ? 1 : 0;
}

void pop()
{
    if (is_empty(s))
        printf("Stack is empty can't pop!\n");
    else
    {
        printf("%d is popped\n", peek(s));
        s->top --;
    }
}

void push(int data)
{
    if (is_full(s))
        printf("Stack is full can't push!\n");
    else
    {
        s->top ++;
        s->arr[s->top] = data;
    }
}

void main()
{
    s = (struct stack*) malloc(sizeof(struct stack));
    create_stack();
    push(2);
    push(3);
    push(4);
    printf("%d is top right now.\n", peek());
    pop();
    pop();
    pop();
    pop();

}