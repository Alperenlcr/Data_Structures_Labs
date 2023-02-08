#include <stdio.h>
#include <stdlib.h>

#define eight 128
#define sixteen 32768
#define twentyFour 8388608

// A structure to represent a stack
struct Stack
{
    int top;
    unsigned capacity;
    char* array;
};

// function to create a stack of given capacity. It initializes size of
// stack as 0
struct Stack* create_stack(unsigned capacity)
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (char*)malloc(stack->capacity * sizeof(char));
    return stack;
}

// Stack is empty when top is equal to -1
int is_empty(struct Stack* stack)
{
    return stack->top == -1;
}

// Function to add an item to stack. It increases top by 1
void push(struct Stack* stack, char item)
{
    stack->array[++stack->top] = item;
}

// Function to remove an item from stack. It decreases top by 1
char pop(struct Stack* stack)
{
    if (is_empty(stack))
        return 'n';
    return stack->array[stack->top--];
}

// Function to return the top from stack without removing it
char peek(struct Stack* stack)
{
    if (is_empty(stack))
        return 'n';
    return stack->array[stack->top];
}

int bit_count(int number)
{
    if (number < eight && number >= -eight)
        return 8;
    else if (number < sixteen && number >= -sixteen)
        return 16;
    else if (number < twentyFour && number >= -twentyFour)
        return 24;
    else
        return 32;
}

void decimal_to_binary_string(int n, int number, char* string)
{
    int i, k;
    // Size of an integer is assumed to be n bits
    for (i = n-1; i >= 0; i--) {
        k = number >> i;
        if (k & 1)
            string[i] = '1';
        else
            string[i] = '0';
    }
}

void solution_with_stack(char* string, int n)
{
    struct Stack* stack;
    int i;
    stack = create_stack(n);                 // create stack
    for ( i = 0; i < n; i++)
    {
        // if empty push what is next
        if (is_empty(stack))
        {
            push(stack, string[i]);
        }
        // if not empty
        else
        {
            // push if top is same with what is next
            if (peek(stack) == string[i])
            {
                push(stack, string[i]);
            }
            // pop if top is not same with what is next
            else
            {
                pop(stack);
            }
        }
    }
    if (stack->top == -1)
        printf("0s and 1s are equal.\n");
    else
        printf("%ds are more. Extra %d times %ds are needed.\n", peek(stack)-'0', stack->top + 1, (peek(stack)-'0')^1);
}

int main()
{
    int number, n;
    char* string;

    printf("Number : ");
    scanf("%d", &number);                   // get input as int

    n = bit_count(number);                  // find how many bit needed for representation
    string = (char*) malloc(n);             // allocate memory
    decimal_to_binary_string(n, number, string);         // convert int to string

    printf("string form : %s\n", string);
    // note: converting string and stack operations could be done at the same time but I infer from pdf that I should separete these.

    solution_with_stack(string, n);
    return 0;
}
