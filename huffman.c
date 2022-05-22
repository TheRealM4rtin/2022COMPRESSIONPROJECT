#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int freq;
    char data;
    struct node *left, * right, *next, *child;
}* node, * tree;

node ConstructAll(int frequence, char d, node n, tree l, tree r, tree c){
    node new = (node)malloc(sizeof(struct node));

    new->freq = frequence;
    new->data = d;
    new->left = l;
    new->right = r;
    new->next = n;
    new->child = c;

    return new;
}

void printTREE(tree B) {
    if (B!=NULL)
    {
        if (B->left != NULL || B->right !=NULL) printf("1 ");
        printTREE(B->left);
        printTREE(B->right);
        if (B->left == NULL && B->right == NULL) printf("0%c ", B->data);
    }
}

void print(struct node *head) {
    for (; head; head = head->next)
        printf(" - frequence of %c is %d\n", head->data, head->freq);
}

void Push(struct node **head, int frequence, char data, node n, tree l, tree r, tree c) {
    node temp = (node)malloc(sizeof(node));
    temp = ConstructAll(frequence, data, n, l, r, c);
    *head = temp;
}

void SortedInsert(struct node** headRef, struct node* newNode) {
    node current = *headRef;
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

void InsertSort(struct node** headRef) {
    node result = NULL, current = *headRef, next;
    while (current!=NULL) {
        next = current->next;
        SortedInsert(&result, current);
        current = next;
    }
    *headRef = result;
}

void add_freq(struct node *head, char letter, int newfreq) {
    for(; head; head = head->next)
        if (head->data == letter) head->freq += newfreq;
}

int is_in(char letter, struct node *head) {
    for (; head; head = head->next)
        if (head->data == letter) return 1;
    return 0; // is not in
}

void CodingTree(struct node **head){
    node current = *head;

    while(current) {
        printf("AAZ");    
        node node_1 = *head;
        node node_2 = (*head)->next;
        printf("A");
        tree tree_1 = ConstructAll(node_1->freq, node_1->data, NULL, NULL, NULL, NULL);
        tree tree_2 = ConstructAll(node_2->freq, node_2->data, NULL, NULL, NULL, NULL);
        int sum = (tree_1->freq) + (tree_2->freq);
        
        //This is a tree made with 2 trees
        printf("BB");
        tree treeresult = ConstructAll(0, ' ', NULL, tree_1, tree_2, NULL);
        
        //This is a node of a LL made with treeresult 
        //node node_tree = ConstructAll( sum , ' ', (*head)->next->next, NULL, NULL, treeresult);
        
        Push(head, sum, ' ', (*head)->next->next, NULL, NULL, treeresult);
        printf("AA");
        node node_tree = ConstructAll(sum, ' ', (*head)->next->next, NULL, NULL, treeresult);
        printTREE(node_tree);

        current = current->next;
    }
    

/*
    free(*head);
    free((*head)->next);
    free(node_1);
    free(node_2);
*/


}


void occurency(char *fileNAME)
{
    FILE *file;
    file = fopen(fileNAME, "r");

    node h = NULL;
    node *a = &h;
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
            Push(a, 1, c, NULL, NULL, NULL, NULL);
            a = &((*a)->next);
        }
    }
    InsertSort(&h);
    print(h);
    printf("a");
    CodingTree(a);
    printf("b");

    
    fclose(file);
}

int main()
{
    char *test = "test.txt";
    occurency(test);

}