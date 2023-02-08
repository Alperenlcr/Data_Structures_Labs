#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 200

typedef struct node
{
    int size;
    char word[MAX];
    char files[MAX][MAX];;
    struct node* right;
    struct node* left;
}node;

node* search(node* root, char* key)
{
	if (root == NULL || strcmp(root->word, key) == 0)
	return root;

	if (strcmp(root->word, key) < 0)
    	return search(root->right, key);

	return search(root->left, key);
}

node* newNode(char* word)
{
    int i;
    node* temp = (node*)malloc(sizeof(node));
    strcpy(temp->word, word);
    temp->size = 0;
    strcpy(temp->files[0], "-1");
    temp->left = temp->right = NULL;
    return temp;
} 

node* insert(node* node, char* key)
{
    /* If the tree is empty, return a new node */
    if (node == NULL)
        return newNode(key);

    /* Otherwise, recur down the tree */
    if (strcmp(key, node->word) < 0)
        node->left = insert(node->left, key);
    else if (strcmp(key, node->word) > 0)
        node->right = insert(node->right, key);

    /* return the (unchanged) node pointer */
    return node;
}

/* Given a non-empty binary search
   tree, return the node
   with minimum key value found in
   that tree. Note that the
   entire tree does not need to be searched. */
node* minValueNode(node* n)
{
    node* current = n;
 
    /* loop down to find the leftmost leaf */
    while (current && current->left != NULL)
        current = current->left;

    return current;
}

struct node* deleteNode(node* root, char key[MAX])
{
    int i;
    // base case
    if (root == NULL)
        return root;

    // If the key to be deleted
    // is smaller than the root's
    // key, then it lies in left subtree
    if (strcmp(key, root->word) < 0)
        root->left = deleteNode(root->left, key);

    // If the key to be deleted
    // is greater than the root's
    // key, then it lies in right subtree
    else if (strcmp(key, root->word) > 0)
        root->right = deleteNode(root->right, key);

    // if key is same as root's key,
    // then This is the node
    // to be deleted
    else {
        // node with only one child or no child
        if (root->left == NULL) {
            node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            node* temp = root->left;
            free(root);
            return temp;
        }

        // node with two children:
        // Get the inorder successor
        // (smallest in the right subtree)
        node* temp = minValueNode(root->right);

        // Copy the inorder
        // successor's content to this node
        strcpy(root->word, temp->word);
        root->size = temp->size;
        for ( i = 0; i < root->size; i++)
            strcpy(root->files[i], temp->files[i]);

        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->word);
    }
    return root;
}

void print_tree(node* root)
{
    int i;
	if (root == NULL)
	    return;

    printf("\nWord : %s\tFiles (%d) : ", root->word, root->size);
    for ( i = 0; i < root->size; i++)
        printf("%s-", root->files[i]);

    // recur on left subtree
    print_tree(root->left);

    // recur on right subtree
    print_tree(root->right);
}

void delete_file(node* root, node* iter, char file[MAX])
{
    //print_tree(root);
    //printf("\n");

    if (iter == NULL)
        return;

    int i=0;
    while ( i < iter->size)
    {
        if (strcmp(iter->files[i], file) == 0)
        {
            while (i < iter->size)
            {
                strcpy(iter->files[i], iter->files[i+1]);
                i ++;
            }
            iter->size --;
        }
        i ++;
    }
    if (iter->size == 0)
        deleteNode(root, iter->word);

    // recur on left subtree
    delete_file(root, iter->left, file);

    // recur on right subtree
    delete_file(root, iter->right, file);
}

int in(char mat[][MAX], char str[MAX], int n)
{
    int i=0;
    while (i < n && strcmp(mat[i], str) != 0)
        i ++;
    if (i == n)
        return 0;
    return 1;
}

void filter (char mat[][MAX], char text[MAX])
{
    int i = 0, j=0, k=0;
    while (text[i] != '\0')
    {
        if (text[i] == ' ')
        {
            mat[j][k] = '\0';
            j ++;
            k = 0;
        }
        else if ( (text[i] <= 'z' && text[i] >= 'a') || (text[i] <= 'Z' && text[i] >= 'A') )
        {
            mat[j][k++] = text[i];
        }
        i ++;
    }
    strcpy(mat[i], "\0");
}

node* new_file(node* root, char texti[MAX], char file[MAX])
{
    char text[MAX][MAX];
    filter(text, texti);
    int i = 0, j=0;
    while (strcmp(text[i], "\0") != 0)
    {
        node* temp = search(root, text[i]);
        if ( temp == NULL )
        {
            if (root == NULL)
            {
                root = newNode(text[i]);
                strcpy(root->files[root->size++], file);
                strcpy(root->files[root->size], "-1");
            }
            else
            {
                temp = insert(root, text[i]);
                temp = search(root, text[i]);
                strcpy(temp->files[temp->size++], file);
                strcpy(temp->files[temp->size], "-1");
            }
        }
        else
        {
            if (!in(temp->files, file, temp->size))
            {
                strcpy(temp->files[temp->size++], file);
                strcpy(temp->files[temp->size], "-1");
            }
        }
        j = 0;
        while (text[i][j] != '\0')
        {
            text[i][j] = '\0';
            j ++;
        }
        i ++;
    }
    return root;
}

void multi_tok(char *input, char *delimiter, char r[MAX]) {
    static char *string;
    if (input != NULL)
        string = input;

    if (string == NULL)
    {
        strcpy(r, string);
        return;
    }

    char *end = strstr(string, delimiter);
    if (end == NULL) {
        char *temp = string;
        string = NULL;
        strcpy(r, temp);    
        return;
    }

    char *temp = string;

    *end = '\0';
    string = end + strlen(delimiter);
    strcpy(r, temp);
}

int len(char* Array)
{
    int count = 0;
    while (Array[count] != '\0')
    {
        count++;
    }
    return count+1;
}

int main ()
{
    node* root = NULL;
    char file[MAX];
    char text[MAX];
    char temp[MAX], temp2[MAX];
    char line[MAX*2];
    char *token;
// dosyadaki satirlar okunup new_file cagir
    FILE *fptr;
    fptr = fopen("test.txt", "r");
    int i = 0;
    while (fgets (line, MAX*2, fptr)!=NULL)
    {
        multi_tok(line, ": ", file);
        multi_tok(NULL, "abc", text);        
        i = len(text);
        (text[i-3] == '\r') ? text[i-3] = '\0' : printf(" ");
        //printf("%s-%s\n", file, text);
        root = new_file(root, text, file);
    }

    fclose(fptr);

    int choice = 0;
    while (choice != 5)
    {
        printf("\n*************************************\n");
        printf("1 - Add New File\n");
        printf("2 - Delete File\n");
        printf("3 - Search Word\n");
        printf("4 - Print Tree\n");
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
// dosya pointerini sona al ve bir satir ekle ayrica new_file da cagir
                printf("File name : ");
                scanf("%s", file);
                printf("File content : ");
                scanf(" %[^\n]s", text);
                root = new_file(root, text, file);
                FILE* fa;
                fa = fopen("test.txt", "a");
                fprintf(fa, "\n%s: %s", file, text);
            break;
            case 2:
// silenecek dosyanin wordlerini bul txt den
// her wordun file listesinden silinen file i cikar bos kalirsa wordu agactan cikar
                printf("Enter a file for deletion : ");
                scanf("%s", temp);
                delete_file(root, root, temp);
                delete_file(root, root, temp);
                delete_file(root, root, temp);
            break;
            case 3:
// search word and print files
                printf("Enter a word to search in tree : ");
                scanf("%s", temp);
                node* tempA = search(root, temp);
                if (tempA == NULL)
                    printf("%s is not in tree.\n", temp);
                else
                {
                    printf("File names : ");
                    for ( i = 0; i < tempA->size; i++)
                        printf("%s - ", tempA->files[i]);
                    printf("\n");
                }
            break;
            case 4:
                print_tree(root);
            break;
        }
    }
    return 0;
}