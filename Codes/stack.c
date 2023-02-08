#include<stdio.h>
#include<stdlib.h>
#define STACK_SIZE 40
struct stack
{
    int arr[STACK_SIZE];
    int top;
};


struct stack* create_stack()
{
    struct stack* s = (struct stack*) malloc(sizeof(struct stack));
    s->top = -1;
    return s;
}

int peek(struct stack* s)
{
    return s->arr[s->top];
}

int is_full(struct stack* s)
{
    return STACK_SIZE == s->top+1 ? 1 : 0;
}

int is_empty(struct stack* s)
{
    return -1 == s->top ? 1 : 0;
}

void pop(struct stack* s)
{
    if (is_empty(s))
        printf("Stack is empty can't pop!\n");
    else
    {
        printf("%d is popped\n", peek(s));
        s->top --;
    }
}

void push(struct stack* s, int data)
{
    if (is_full(s))
        printf("Stack is full can't push!\n");
    else
    {
        s->top ++;
        s->arr[s->top] = data;
        printf("%d is pushed\n", peek(s));
    }
}

void main()
{
    struct stack* s = create_stack();
    push(s, 2);
    push(s, 3);
    push(s, 4);
    printf("%d is top right now.\n", peek(s));
    pop(s);
    pop(s);
    pop(s);
    pop(s);

}