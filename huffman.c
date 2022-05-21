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

void insertSort(struct node **head, char data, int frequence){

    while(*head && (*head)->freq > frequence){ //Attention < >
        head = &((*head)->next);
    }
    Push(head, data, frequence);
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
            insertSort(a, c, 1);
            a = &((*a)->next);
        }
    }

    print(h);

    fclose(file);
}

int main(){

    // officiel : char * fileNAME ="rle.txt";

    char *test = "test.txt";

    occurency(test);
    
    return 0;
}