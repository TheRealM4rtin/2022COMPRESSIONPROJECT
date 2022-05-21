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
        /*else 
            head = &((*head)->next);*/
    }
}

int is_in(char letter, struct node *head){

    for(;head;head=head->next) {
        if( head->data == letter) return 1; //oui
         
    }
    return 0; // non
}

void occurency(char *fileNAME, struct node **head){
    FILE * file;
    file = fopen(fileNAME,"r");

    //struct node * h = Construct(1, getc(file), NULL);
    //head = &first;
    //struct node ** last = &(*head);

    struct node* h = NULL;
    struct node** a = &h;
    char c;

    //printf("first : %c\n", first->data);
    //printf("head->first :%c\n", (*head)->data);

    while ( (c = getc(file)) != EOF ){
        
        if (is_in(c, h) == 1) { //If in the dictionnary
            printf("%c is in the dico\n", c);
            add_freq(h, c, 1);
        }
        if( is_in(c, h) == 0){ //If not in the dictionnary
            printf("%c is Not in the dico\n", c);
            //PushEnd(head, c, 1);
            Push(a, c, 1);
            a = &((*a)->next);
            //head= &(*head)->next;
        }
 
    }

    print(h);

    fclose(file);
}

int main(){

    // officiel : char * fileNAME ="rle.txt";

    char *test = "test.txt";

    struct node ** head = NULL;

    occurency(test, head);
    
    return 0;
}