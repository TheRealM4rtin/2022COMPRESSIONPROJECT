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

void print(struct node **head){
    struct node * current;
    int i = 0;
    for(current = *head; current; current = current->next){
        printf(" - frequence of %c is %d \n", (*head)->data, (*head)->freq);
        i++;
    }
    printf(" i = %d\n", i);
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

void add_freq(struct node **head, char letter, int newfreq){
    
    for(;*head;*head=(*head)->next){
        if( (*head)->data == letter){
            (*head)->freq += newfreq;
            printf("blblb\n");
        }
        /*else 
            head = &((*head)->next);*/
    }
}

int is_in(char letter, struct node **head){

    for(; (*head)!=NULL;){
        if( (*head)->data == letter) return 1; //oui
        head = &((*head)->next);
    }
    return 0; // non
}

void occurency(char *fileNAME, struct node **head){
    FILE * file;
    file = fopen(fileNAME,"r");

    struct node * first = Construct(1, getc(file), NULL);
    head = &first;
    char c;
    
    printf("first : %c\n", first->data);
    printf("head->first :%c\n", (*head)->data);

    while ( (c = getc(file)) != EOF ){
        
        if (is_in(c, head) == 1) { //If in the dictionnary
            printf("%c is in the dico\n", c);
            add_freq(head,c, 1);
        }
        else /*if( is_in(c, head) == 0)*/{ //If not in the dictionnary
            printf("%c is Not in the dico\n", c);
            //PushEnd(head, c, 1);
            //Push(head, c, 1);
            (*head)->next = Construct(1, c, NULL);
            //head= &(*head)->next;
        }
 
    }

    print(head);

    fclose(file);
}

int main(){

    // officiel : char * fileNAME ="rle.txt";

    char *test = "test.txt";

    struct node ** head = NULL;

    occurency(test, head);
    
    return 0;
}