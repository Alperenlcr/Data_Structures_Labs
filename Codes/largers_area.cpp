
#include <iostream>
#include <stdio.h>

/*Stack*/
#define MAX_STACK_SIZE 100

struct Stack {
	int s[MAX_STACK_SIZE];
	int Top;
} _stack;
bool IsEmpty()
{
    return _stack.Top == -1 ? true : false;
}
bool IsFull()
{
    return _stack.Top == MAX_STACK_SIZE ? true : false;
}
int Pop()
{
	if (!IsEmpty()) {
		return _stack.s[_stack.Top--];
	}
}
void Push(int data)
{
	if (!IsFull()) {
		_stack.s[++_stack.Top] = data;
	}
}
int Top()
{
	return _stack.s[_stack.Top];
}
/*Finding Max Area*/
int GetMaxArea(int hist[], int size)
{
    int max_area = 0; 
    int tp;  
    int area_with_top;               
    int i = 0;

    while (i < size)
    {
        if (IsEmpty() || hist[Top()] <= hist[i])
            Push(i++);
        else
        {
            tp = Pop(); 
            area_with_top = hist[tp] * (IsEmpty() ? i : i - Top() - 1);
            if (max_area < area_with_top)
                max_area = area_with_top;
        }
    }
    while (!IsEmpty())
    {
        tp = Pop();
        area_with_top = hist[tp] * (IsEmpty() ? i : i - Top() - 1);
        if (max_area < area_with_top)
            max_area = area_with_top;
    }
    return max_area;
}
/*Driver Code*/
int main()
{
    int hist[] = { 6, 2, 5, 4, 5, 1, 6 };
    int size = sizeof(hist) / sizeof(hist[0]);
    printf("Max Area: %d", GetMaxArea(hist, size));
}