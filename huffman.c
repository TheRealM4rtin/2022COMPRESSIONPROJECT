#include <stdio.h>
#include <stdlib.h>

//Parfait
typedef struct node {      
    char data;
    int freq;
    struct node *next;
}* node;

node Create_node(){
    return NULL;
}

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
        printf("%d", (*head)->freq);
        printf("%c", (*head)->data);
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

int is_in(int letter, struct node **head){

    for(; (*head)!=NULL;){
        if( (*head)->data == letter) return 1; //oui
        head = &((*head)->next);
    }
    return 0; // non
}

void occurency(char *fileNAME, struct node **head){
    FILE * file;
    file = fopen(fileNAME,"r");

    node first;
    char c, charforhead;
    
    /* we need to create the first node but only one time */
    charforhead = getc(file);
    first = Construct(1, charforhead, NULL);
    

    while (!feof (file)){
        c = getc(file);
        
        if (is_in(c, &first) == 1) { //If in the dictionnary
            add_freq(&first, 1); //not sure
        }
        if( is_in(c, &first) == 0){ //If not in the dictionnary
            Construct(1, c, NULL);
        }
 
    }

    fclose(file);
}

int main(){

    // officiel : char * fileNAME ="rle.txt";

    char *test = "test.txt";

    Create_node();

    occurency(test);

    print(node);
    

    return 0;
}