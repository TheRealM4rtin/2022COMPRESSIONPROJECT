#include <stdio.h>
#include <stdlib.h>

// Parfait
typedef struct node
{
    char data;
    int freq;
    struct node *next;
} * node;

// Parfait
node Construct(int freq, char data, node next)
{
    node new = (node)malloc(sizeof(struct node));
    // if(!new) return 0;
    new->freq = freq;
    new->data = data;
    new->next = next;
    return new;
}

void print(struct node *head)
{
    for (; head; head = head->next)
        printf(" - frequence of %c is %d\n", head->data, head->freq);
}

void Push(struct node **head, char data, int frequence)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->data = data;
    temp->freq = frequence;
    temp->next = NULL; // pq égal à NULL et pas *head ?
    *head = temp;
}

void Pop(struct node** headRef) {
    struct node* head;
    head = *headRef;
    *headRef = head->next; // unlink the head node for the caller
    free(head); // free the head node
}

int Length(struct node* head) {
    int count = 0;
    struct node* current = head;
    while (current != NULL) {
        count++;
        current = current->next;   
    }
    return(count);
}

void SortedInsert(struct node** headRef, struct node* newNode) {
    struct node* current = *headRef;
    // Special case for the head end
    if (*headRef == NULL || (*headRef)->freq >= newNode->freq) {
        newNode->next = *headRef;
        *headRef = newNode;
    }
    else {
        // Locate the node before the point of insertion
        while (current->next!=NULL && current->next->freq<newNode->freq) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Given a list, change it to be in sorted order (using SortedInsert()).
void InsertSort(struct node** headRef) {
    struct node* result = NULL; // build the answer here
    struct node* current = *headRef; // iterate over the original list
    struct node* next;
    while (current!=NULL) {
        next = current->next; // save the next pointer before we change it
        SortedInsert(&result, current);
        current = next;
    }
    *headRef = result;
}

void add_freq(struct node *head, char letter, int newfreq)
{

    for (; head; head = head->next)
    {
        if (head->data == letter)
        {
            head->freq += newfreq;
        }
    }
}

int is_in(char letter, struct node *head)
{

    for (; head; head = head->next)
    {
        if (head->data == letter)
            return 1; // oui
    }
    return 0; // non
}
//=====================================================================================================
typedef struct nodeT {
    char data;
    struct nodeT *left, * right;
} * tree;

//very useful
tree ConstructT (char data, tree left, tree right){
    tree B = (tree)malloc(sizeof(struct nodeT));
    B->data = data;
    B->left = left; //first (smaller freq) letter
    B->right = right; //second smaller freq letter
    return B;
}

//print coding tree
void printTREE(tree B){
    if (B!=NULL)
    {
        if (B->left != NULL || B->right !=NULL)
        {
            printf("1 ");
        }
        printTREE(B->left);
        printTREE(B->right);
        if (B->left == NULL && B->right == NULL)
        {
            printf("0%c ", B->data);
        }
    }
}

//rebuild the tree from coding tree string
int i=0;
tree build(char s[]){
    //end of string == \0
    if (s[i]!='\0')
    {
        if (s[i]=='1')
        {
            i++;
            tree left = build(s);
            i++;
            tree right = build(s);
            return ConstructT(' ', left, right);
        }else{
            if (s[i]=='0')
            {
                i++;
                return ConstructT(s[i], NULL, NULL);
            }
        }
    }
}


typedef struct codingtree
{
    tree data;
    int freq;
    struct codingtree *next;
} * codingtree;

/*
codingtree ConstrucCT(tree dataa, int frequ, codingtree next)
{
    codingtree new = (codingtree)malloc(sizeof(struct codingtree));
    new->data = dataa;
    new->freq = frequ;
    new->next = next;
    return new;
}*/

void PushCT(struct codingtree ** headCT, tree dataa, int frequ){
    struct codingtree *tempCT = (struct codingtree *)malloc(sizeof(struct codingtree));
    tempCT->data = dataa;
    tempCT->freq = frequ;
    tempCT->next = NULL;
    **headCT = *tempCT;   
}

codingtree createCT(struct node *head){
    struct codingtree * new;
    //* new = (codingtree)malloc(sizeof(struct tree));
    printf("début ");
    for (; head; head = head->next){
        printf("11 ");
        PushCT(&new, (ConstructT(head->data, NULL, NULL)), head->freq);
        printf("retour 1\n");
    }
    printf("fin\n");
    return new;
}

/*
| |2|| -> ||3|| -> ||4|| -> ||5||
 |
(A)
A is a tree*/
//la je veux faire type codingtree de la 1e linked list
/*
codingtree createCT(struct node *head){
    struct codingtree * new;
    //* new = (codingtree)malloc(sizeof(struct tree));
    printf("début ");
    for (; head; head = head->next){
        printf("11 ");
        new->data = ConstructT(head->data, NULL, NULL);
        printf("22 ");
        new->freq = head->freq;
        printf("33 ");
        new = new->next;
        printf("retour 1\n");
    }
    printf("fin\n");
    return new;
}*/

/*
void saveCT(struct node *list){
    //struct codingtree **headCT = (createCT(list)); //&

    printf("1 ");

    //save les deux premier
    struct codingtree* p1 = *headCT;
    struct codingtree* p2 = (*headCT)->next;

    printf("2 ");

    struct codingtree * result ;
    result->freq= (p1->freq) + (p2->freq);
    result->data = ConstructT(' ', p1->data, p2->data);

    printf("3 ");

    result->next = (*headCT)->next->next;

    printf("4 ");

    //remove les 2 premiers de la liste (head CD et headCDnext)
    free(*headCT);
    free((*headCT)->next);
    //sort pas fait
    printf("retour \n ");
}*/

//=====================================================================================================
//s'inspirer de l'ancien save pour le nouveau
/*
void save(struct node **head){

    //save les deux premier
    struct node * p1 = *head;
    struct node * p2 = (*head)->next;

    struct codingtree * result ;
    result->freq= (p1->freq) + (p2->freq);

    result->data = ConstructT(' ', ConstructT(p1->data, NULL, NULL), ConstructT(p2->data, NULL, NULL));

    result->next = (*head)->next->next;

    free(*head);
    free((*head)->next);
}*/

//_______________________________________________________________________________________________________

//added by me (my bullshit)
/*
void createsubTree(struct node *head)
{
    while ((Length(head))!=1)
    {
        tree tr = ConstructT(' ', ConstructT(head->data, NULL, NULL), ConstructT(head->next->data, NULL, NULL));
        //printTREE(tr);
        int temp = head->freq + head->next->freq;
        Push(&head, ' ', temp);
        Pop(&head);
        Pop(&head);
        InsertSort(&head);
        print(head);
    }
}*/

//_______________________________________________________________________________________________________

void occurency(char *fileNAME)
{
    FILE *file;
    file = fopen(fileNAME, "r");

    struct node *h = NULL;
    struct node **a = &h;
    char c;

    while ((c = getc(file)) != EOF)
    {

        if (is_in(c, h) == 1)
        { // If in the dictionnary
            printf("%c is in the dico\n", c);
            add_freq(h, c, 1);
        }
        if (is_in(c, h) == 0)
        { // If not in the dictionnary
            printf("%c is Not in the dico\n", c);
            Push(a, c, 1);
            a = &((*a)->next);
        }
    }

    print(h);

    InsertSort(&h);
    printf("SORTED\n");
    print(h);

    printf("let's create coding tree\n ");
    struct codingtree * BLabla = createCT(h);
    printf("coding tree created\n");

    printf("let's arrange the coding tree\n ");
    //saveCT(h);
    printf("coding tree arranged\n");
    fclose(file);
}

int main()
{

    // officiel : char * fileNAME ="rle.txt";

    char *test = "test.txt";

    occurency(test);

    

    return 0;
}