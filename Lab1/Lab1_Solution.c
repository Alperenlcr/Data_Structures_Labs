#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 1000


struct Node {
    int data;
    struct Node* next;
    struct Node* below;
};


int len(struct Node* head);
int len2(struct Node* head);
int in_list(int* Array, int value);
void merge(int* arr, int l, int m, int r);
void merge_sort(int* arr, int l, int r);
struct Node* random_list(struct Node *head);
struct Node* removeFirstNode(struct Node* head);
void append(struct Node** head_ref, int new_data, struct Node* below_ref);
void reverse(struct Node** head_ref);
void printList(struct Node* head);
void printList2(struct Node* head2);
void add_front(struct Node** head_ref, struct Node *new_head);
void create_levels(struct Node** head_ref, struct Node *new_head);
struct Node* init();
struct Node* init2(struct Node* head, int data);
int search(struct Node* head, int data);
int deletee(struct Node** head, int data);
void add(struct Node* head, int data);



/* Driver program to test above functions*/
int main()
{
    srand(time(0));
    /* Start with the empty list */
    struct Node* head = NULL;
    struct Node* neww = NULL;
    head = (struct Node*) malloc(sizeof(struct Node));
    head->next = init();
    create_levels(&head, head->next);
    reverse(&head);
    head = removeFirstNode(head);
    int choice = 0, temp, temp1;
    while (choice != 5)
    {
        printf("*************************************\n");
        printf("1 - Add\n");
        printf("2 - Delete\n");
        printf("3 - Search\n");
        printf("4 - Print\n");
        printf("5 - Quit\n\n");
        printf("Choice : ");
        scanf("%d", &choice);

        if (choice > 5 || choice < 1)
        {
            printf("\nWrong input !\n");
            continue;
        }
        switch (choice)
        {
        case 1:
            printf("Enter a value to add : ");
            scanf("%d", &temp);
            {
            struct Node* neeww = (struct Node*) calloc(1, sizeof(struct Node));
            neeww->data = temp;
            add_front(&head, neeww);
            }
            add(head->below, temp);
            if (head->next->data == head->below->next->data)
                head->next->below = head->below->next;
            else
                head->next->below = head->below->next->next;
            break;
        case 2:
            printf("Enter a value to delete : ");
            scanf("%d", &temp);
            if (deletee(&head, temp) == -1)
                printf("%d doesn't exist\n", temp);
            else
                printf("%d is removed successfully\n", temp);

            break;
        case 3:
            printf("Enter a value for search : ");
            scanf("%d", &temp);
            temp1 = search(head, temp);
            if (temp1 == -1)
                printf("%d doesn't exist\n", temp);
            else
                printf("%d is at level %d\n", temp, temp1);
            break;
        case 4:
            printList(head);
            printf("\n");
            break;
        default:
            break;
        }
    }
    return 0;
}


int in_list(int* Array, int value)
{
    int i=0;
    while (Array[i] != value && Array[i] != '\0')
        i++;
    if (Array[i] == value)
        return 1;
    else
        return 0;
}

void merge(int* arr, int l, int m, int r)
{
// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    /* create temp arrays */
    int L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
    are any */
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
    are any */
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void merge_sort(int* arr, int l, int r)
{
/* l is for left index and r is right index of the
sub-array of arr to be sorted */
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l + (r - l) / 2;
 
        // Sort first and second halves
        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);
 
        merge(arr, l, m, r);
    }
}

/* Given a reference (pointer to pointer) to the head
   of a DLL and an int, appends a new node at the end  */
void append(struct Node** head_ref, int new_data, struct Node* below_ref)
{
    /* 1. allocate node */
    struct Node* new_node
        = (struct Node*)malloc(sizeof(struct Node));
 
    struct Node* last = *head_ref; /* used in step 5*/

    /* 2. put in the data  */
    new_node->data = new_data;

    /* 3. This new node is going to be the last node, so
          make next of it as NULL*/
    new_node->next = NULL;

    /* 4. If the Linked List is empty, then make the new
          node as head */
    if (*head_ref == NULL) {
        new_node->below = below_ref;
        *head_ref = new_node;
        return;
    }

    /* 5. Else traverse till the last node */
    while (last->next != NULL)
        last = last->next;

    /* 6. Change the next of last node */
    last->next = new_node;

    /* 7. Make last node as previous of new node */
    new_node->below = below_ref;

    return;
}

// This function prints contents of linked list starting
// from the given node
void printList2(struct Node* head2)
{
    while (head2 != NULL)
    {
        printf(" %d ", head2->data);
        head2 = head2->next;
    }
}

void create_levels(struct Node** head_ref, struct Node *new_head)
{
    if (len(new_head) != 1)
        create_levels(head_ref, random_list(new_head));
    add_front(head_ref, new_head);
}

int search(struct Node* head, int data)
{
    int level = 0, level_size = len2(head), found = 0;

    struct Node* iter = head;
    while (!found)
    {
        if (iter->next == NULL)
        {
            if (iter->below == NULL)
                return -1;
            iter = iter->below;
            level ++;
        }
        else if (iter->next->data == data)
        {
            found = 1;
        }
        else if (iter->next->data < data)
        {
            if (iter->next->next == NULL)
            {
                if (iter->next->below == NULL)
                    return -1;
                iter = iter->next->below;
                level ++;
            }
            else
                iter = iter->next;
        }
        else if (iter->next->data > data)
        {
            if (iter->below == NULL)
                return -1;
            iter = iter->below;
            level ++;
        }
    }
    return level_size-level;
}

struct Node* init()
{
    struct Node* head = NULL;
    int list[MAX], count=0, tempi, i;
    char tempc;
    printf("\nEnter values for initial linked list.\nEnter space separated.\nInitial Linked List : ");
    do
    {
        scanf("%d", &tempi);
        list[count++] = tempi;
        tempc = getchar();
    } while (tempc != '\n');
    merge_sort(list, 0, count-1);
    for ( i = 0; i < count; i++)
        append(&head, list[i], NULL);
    return head;
}

struct Node* init2(struct Node* head, int data)
{
    struct Node* nnew = NULL;
    int list[MAX], count=0, i;
    while (head->below != NULL)
        head = head->below;

    head = head->next;
    while (head != NULL)
    {
        list[count++] = head->data;
        head = head->next;
    }
    list[count++] = data;
    merge_sort(list, 0, count-1);
    for ( i = 0; i < count; i++)
        append(&nnew, list[i], NULL);
    return nnew;
}

int deletee(struct Node** head, int data)
{
    int level = 0, level_size = len2(*head), found = 0;

    struct Node* iter = *head;
    while (!found)
    {
        if (iter->next == NULL)
        {
            if (iter->below == NULL)
                return -1;
            iter = iter->below;
            level ++;
        }
        else if (iter->next->data == data)
        {
            found = 1;
        }
        else if (iter->next->data < data)
        {
            if (iter->next->next == NULL)
            {
                if (iter->next->below == NULL)
                    return -1;
                iter = iter->next->below;
                level ++;
            }
            else
                iter = iter->next;
        }
        else if (iter->next->data > data)
        {
            if (iter->below == NULL)
                return -1;
            iter = iter->below;
            level ++;
        }
    }
    while (iter->below != NULL)
    {
        iter->next = iter->next->next;
        iter = iter->below;
        while (iter->next->data != data)
            iter = iter->next;
    }
    iter->next = iter->next->next;

    while ((*head)->next == NULL)
        *head = (*head)->below;

    return level_size-level;
}

void add(struct Node* head, int data)
{
    int level = 0, level_size = len2(head), done = 0;

    struct Node* iter = head;

    // iter.next NULL and iter.data < data    or   iter.next > data    or  iter.next > data and iter.data < data 
    struct Node*neew = (struct Node*) calloc(1, sizeof(struct Node));
    neew->data = data;
    int first = 1, check;
    while (!done)
    {
        check = 1;
        if (first && data < iter->next->data)
        {
            neew->next = iter->next;
            iter->next = neew;
            neew = (struct Node*) calloc(1, sizeof(struct Node));
            neew->data = data;
        }
        else if (iter->next == NULL && iter->data <= data)
        {
            neew->next = NULL;
            iter->next = neew;
            neew = (struct Node*) calloc(1, sizeof(struct Node));
            neew->data = data;
        }
        else if (iter->next->data > data && iter->data <= data)
        {
            neew->next = iter->next;
            iter->next = neew;
            neew = (struct Node*) calloc(1, sizeof(struct Node));
            neew->data = data;
        }
        else
        {
            check = 0;
            iter = iter->next;
            first = 0;
        }

        if (check)
        {
            if (iter->below == NULL)
                done = 1;
            else
            {
                iter->next->below = neew;
                iter = iter->below;
            }
        }
    }
}

// This function prints contents of linked list starting
// from the given node
void printList(struct Node* head)
{
    int level = len2(head);
    while (head != NULL)
    {
        printf("\nLevel %d : ", level--);
        printList2(head->next);
        head = head->below;
    }
}

struct Node* random_list(struct Node *head)
{
    struct Node* new_head = NULL;
    struct Node* temp = head;

    int Size = len(temp), i, num;
    int size = Size;
    // create size/2 + 1 len index list
    if (Size % 2 == 1)
        size ++;
    size /= 2;
    int* index_list = (int*) malloc(size*sizeof(int));
    for ( i = 0; i < size; i++)
    {
        do
        {
            num = (rand() % (Size))+1;
        } while (in_list(index_list, num-1));
        index_list[i] = num-1;
    }
    merge_sort(index_list, 0, size-1);
    i = 0;
    int count = 0;
    while (count < Size)
    {
        if (count == index_list[i])
        {
            i ++;
            append(&new_head, temp->data, temp);
        }
        temp = temp->next;
        count ++;
    }
    return new_head;
}

/* Given a reference (pointer to pointer) to the head of a list
   and an int,  inserts a new node on the front of the list. */
void add_front(struct Node** head_ref, struct Node *new_head)
{
    /* 1. allocate node */
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));

    /* 2. put in the data  */
    new_node->next  = new_head;

    /* 3. Make next of new node as head */
    new_node->below = (*head_ref);

    /* 4. move the head to point to the new node */
    (*head_ref) = new_node;
}

/* Counts no. of nodes in linked list */
int len(struct Node* head)
{
    int count = 0;  // Initialize count
    struct Node* current = head;  // Initialize current
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
}

int len2(struct Node* head)
{
    int count = 0;  // Initialize count
    struct Node* current = head;  // Initialize current
    while (current != NULL)
    {
        count++;
        current = current->below;
    }
    return count;
}

/* Function to reverse the linked list */
void reverse(struct Node** head_ref)
{
    struct Node* prev = NULL;
    struct Node* current = *head_ref;
    struct Node* next = NULL;
    while (current != NULL) {
        // Store next
        next = current->below;
 
        // Reverse current node's pointer
        current->below = prev;
 
        // Move pointers one position ahead.
        prev = current;
        current = next;
    }
    *head_ref = prev;
}
 
struct Node* removeFirstNode(struct Node* head)
{
    if (head == NULL)
        return NULL;

    // Move the head pointer to the next node
    struct Node* temp = head;
    head = head->below;

    free(temp);

    return head;
}
