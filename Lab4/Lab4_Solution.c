/*
Solution:
First create a graph from txt file
We know that this graph is a tree which means no cycle in it
When we add given edge to graph, our graph must include a cycle in it
What we should do is cut or don't append the max weighted edge in that cycle

//////////////////////////////////////////////////////////////////////////////

Before start coding:
Graph will be repesented in matrix which is NxN and the N is line count in txt
Init all values in matrix as 0
Then line by line change values with weights
At this point Graph is created
Then we add given edge to graph
update_graph() function will include:
    for example a,b,w is given is input
    max_value[3] = {w,a,b}
    we'll find max_value in path which is a to b at tree.
    Stack and DFS will be used
    After max_value is found:
        if it is equal to input edge then we do nothing
        else we cut max_value edge and also append input edge
*/


#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_CAP 100
// A structure to represent a stack
struct Stack {
	int top;
	unsigned capacity;
	int* array;
};

// creates a stack of given capacity
struct Stack* createStack(unsigned capacity)
{
	struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
	stack->capacity = capacity;
	stack->top = -1;
	stack->array = (int*)malloc(stack->capacity * sizeof(int));
	return stack;
}

int isFull(struct Stack* stack)
{
	return stack->top == stack->capacity - 1;
}

// Stack is empty when top is equal to -1
int isEmpty(struct Stack* stack)
{
	return stack->top == -1;
}

// Function to add an item to stack. It increases top by 1
void push(struct Stack* stack, int item)
{
	if (isFull(stack))
		return;
	stack->array[++stack->top] = item;
}

// Function to remove an item from stack. It decreases top by 1
int pop(struct Stack* stack)
{
	if (isEmpty(stack))
		return -1;
	return stack->array[stack->top--];
}

// Function to return the top from stack without removing it
int peek(struct Stack* stack)
{
	if (isEmpty(stack))
		return -1;
	return stack->array[stack->top];
}

int number_of_lines(char* file_name)
{
    FILE *fileptr;
    int count_lines = 0;
    char chr;
    fileptr = fopen(file_name, "r");
    chr = getc(fileptr);
    while (chr != EOF)
    {
        if (chr == '\n')
            count_lines = count_lines + 1;
        chr = getc(fileptr);
    }
    fclose(fileptr);
    return count_lines;
}

// returns NxN matrix filled with 0s
int** init_matrix(int N)
{
    int** mat = (int**) calloc(N, sizeof(int*));
    int i;
    for ( i = 0; i < N; i++)
        mat[i] = (int*) calloc(N, sizeof(int));
    return mat;
}

int** create_a_graph_from_txt(char* file_name, int N)
{
    int i, a, b, w;
    int** mat = init_matrix(N);
    FILE *fileptr;
    fileptr = fopen(file_name, "r");
    for ( i = 0; i < N; i++)
    {
        fscanf(fileptr, "%d %d %d\n", &w, &a, &b);
        mat[a-1][b-1] = w;
        mat[b-1][a-1] = w;
    }
    fclose(fileptr);
    return mat;
}

void print_graph(int** mat, int N)
{
    int i, j, m;
    for ( i = 0; i < N; i++)
        for ( j = 0; j <= i; j++)
            if (mat[i][j] != 0)
                printf("%10d <---%3d ---> %d\n", j+1, mat[i][j], i+1);
}

void print_mat(int** mat, int N)
{
    int i, j, m;
    for ( i = 0; i < N; i++)
    {
        for ( j = 0; j < N; j++)
            printf("%d ", mat[i][j]);
        printf("\n");
    }
}

// works with dfs and stack
void find_path_a2b(struct Stack* stack, int** graph_matrix, int *memory, int N, int end, int i)
{
    if (i == end)       // end of recursion
    {
        push(stack, i);
        return;
    }
    while ((graph_matrix[i][memory[i]] == 0 || memory[i] == peek(stack)) && memory[i] < N)  // To find next node available 
        memory[i] ++;

    if (memory[i] == N)  // dead end
    {
        i = pop(stack);
        memory[i] ++;       // increase the latest coloum count
        find_path_a2b(stack, graph_matrix, memory, N, end, i);
    }
    else
    {
        push(stack, i);
        find_path_a2b(stack, graph_matrix, memory, N, end, memory[i]);
    }
}

void update_graph(int** graph_matrix, int N, int a, int b, int w)
{
	struct Stack* stack = createStack(MAX_STACK_CAP);
    int max_value[3] = {a, w, b};
    int* memory = (int*) calloc(N, sizeof(int));
    find_path_a2b(stack, graph_matrix, memory, N, a-1, b-1);
    push(stack, b-1);

    // Now stack is the cycle
    // printf("\n");
    int x, y, i, size = stack->top;
    for ( i = 0; i < size; i++)
    {
        x = pop(stack)+1;
        y = peek(stack)+1;
        // printf("%d-%d\n", x, y);
        if (max_value[1] < graph_matrix[x-1][y-1])
        {
            max_value[0] = x;
            max_value[1] = graph_matrix[x-1][y-1];
            max_value[2] = y;
        }
    }
    // printf("\n%d %d %d\n", max_value[0], max_value[1], max_value[2]);
    if (!(max_value[0] == a && max_value[1] == w && max_value[2] == b))     // check if max weighted edge is input edge
    {
        // check if smallest edge is new and cycle occurs with two nodes
        if ((max_value[0] == a && max_value[2] == b || (max_value[0] == b && max_value[2] == a)))
        {
            // append new edge
            graph_matrix[a-1][b-1] = w;
            graph_matrix[b-1][a-1] = w;
        }
        else
        {
            // append new edge
            graph_matrix[a-1][b-1] = w;
            graph_matrix[b-1][a-1] = w;
            // cut max in cycle
            graph_matrix[max_value[0]-1][max_value[2]-1] = 0;
            graph_matrix[max_value[2]-1][max_value[0]-1] = 0;
        }
    }
}

int main()
{
    char* file_name = "Sample_MST.txt";
    int a, b, w, N = number_of_lines(file_name) + 1;
    int** graph_matrix = create_a_graph_from_txt(file_name, N);
    printf("\tInitial Graph from txt:\n\t-----------------------\n");
    print_graph(graph_matrix, N);
    printf("Enter edges to append\nTo quit enter (-1 -1 -1)\nFormat should be space separeted (node1 weight node2)\n");

    printf("Enter edge : ");
    scanf("%d %d %d", &a, &w, &b);
    while (a >= 0 && b >= 0 && w >= 0)
    {
        // print_mat(graph_matrix, N);
        update_graph(graph_matrix, N, a, b, w);
        // print_mat(graph_matrix, N);
        print_graph(graph_matrix, N);
        printf("Enter edge : ");
        scanf("%d %d %d", &a, &w, &b);

    }
	return 0;
}
