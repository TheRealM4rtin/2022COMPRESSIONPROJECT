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
    if(!new) return 0;
    new->freq = freq;
    new->data = data;
    new->next = next;
    return new;
}   

void print(struct node **head){
    for(; (*head)!=NULL;){
        printf("frequ : %d |", (*head)->freq);
        printf("data : %c\n", (*head)->data);
        head = &((*head)->next);
    }
}

void Push(struct node **head, char data, int frequence){
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->data = data;
    temp->freq = frequence;
    *head = temp;
}

void add_freq(struct node **head, int newfreq){
    (*head)->freq += newfreq;
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

    node first = Construct(1, getc(file), NULL);
    head = &first;
    char c;
    
    printf("first : %c\n", first->data);
    printf("head->first :%c\n", (*head)->data);

    while ( (c = getc(file)) != EOF ){
        
        if (is_in(c, head) == 1) { //If in the dictionnary
            printf("%c is in the dico", c);
            add_freq(&first, 1); //not sure
        }
        if( is_in(c, head) == 0){ //If not in the dictionnary
            printf("%c is Not in the dico\n", c);
            (*head)->next = Construct(1, c, NULL);
        }
 
    }

    print(head);

    fclose(file);
}

int main(){

    // officiel : char * fileNAME ="rle.txt";

    char *test = "test.txt";

    node A = Construct(0, 0, NULL);

    occurency(test, &A);
    
    return 0;
}