#include <stdio.h>
#include <stdlib.h>

//Parfait
typedef struct node {      
    char data;
    int freq;
    struct node *next;
}* node;

//Parfait
node Construct(int freq, char data, node next){
    node new = (node)malloc(sizeof(struct node));
    //if(!new) return 0;
    new->freq = freq;
    new->data = data;
    new->next = next;
    return new;
}   

void print(struct node *head){
    for(;head;head=head->next)
    printf(" - frequence of %c is %d\n",head->data,head->freq);
}

void Push(struct node **head, char data, int frequence){
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->data = data;
    temp->freq = frequence;
    temp->next = NULL;
    *head = temp;
}

void swap(struct node **list){

    struct node * p1 = *list;
    struct node * p2 = (*list)->next;
    struct node * p3 = (*list)->next->next;
    (*list) = p2;
    p1->next = p3;
    p2->next = p1;
}

void Sort(struct node **head){
    printf("a\n");
    if((*head)->freq > (*head)->next->freq){
        swap(head);
    }else{
        printf("else\n");
    }
    head = &((*head)->next);
}


void PushEnd(struct node **head, char data, int frequence){

    for(; (*head)!=NULL; )
        head = &((*head)->next);
    Push(head, data, frequence);
}

void add_freq(struct node *head, char letter, int newfreq){
    
    for(;head;head=head->next){
        if( head->data == letter){
            head->freq += newfreq;
        }
    }
}

int is_in(char letter, struct node *head){

    for(;head;head=head->next) {
        if( head->data == letter) return 1; //oui
    }
    return 0; // non
}

void occurency(char *fileNAME){
    FILE * file;
    file = fopen(fileNAME,"r");

    struct node* h = NULL;
    struct node** a = &h;
    char c;

    while ( (c = getc(file)) != EOF ){
        
        if (is_in(c, h) == 1) { //If in the dictionnary
            printf("%c is in the dico\n", c);
            add_freq(h, c, 1);
        }
        if( is_in(c, h) == 0){ //If not in the dictionnary
            printf("%c is Not in the dico\n", c);
            Push(a, c, 1);
            a = &((*a)->next);
        }
    }

    print(h);

    Sort(a);
    printf("SORTED\n");
    print(h);

    fclose(file);
}

int main(){

    // officiel : char * fileNAME ="rle.txt";

    char *test = "test.txt";

    occurency(test);
    
    return 0;
}