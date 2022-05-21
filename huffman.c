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
    new->freq = id;
    new->data = data;
    new->next = next;
    return new;
}

void Push(struct node **head, char data, int frequence){
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->data = data;
    temp->freq = frequence;
    *head = temp;
}

void add_freq(struct node **head, int newfreq){
    head->freq += newfreq;
}

int is_in(int char, struct node **head){

    for(; (*head)!=NULL;){
        if( (*head)->data == char) return 1; //oui
        head = &((*head)->next);
    }
    return 0; // non
}

void occurency(char *fileNAME, struct node **head){
    FILE * file;
    file = fopen(fileNAME,"r");

    node head;
    char c, charforhead;
    
    /* we need to create the first node but only one time */
    charforhead = getc(file);
    head = Construct(1, charforhead, NULL);
    

    while (!feof (file)){
        c = getc(file);
        
        if (is_in(c, &head) == 1) { //If in the dictionnary
            add_freq(head, 1); //not sure
        }
        if( is_in(c, &head) == 0){ //If not in the dictionnary
            Construct(1, c, NULL);
        }
 
    }

    fclose(file);
}

int main(){

    // officiel : char * fileNAME ="rle.txt";

    char *test = "test.txt";

    occurency(test);

//try to print
    while(*head != NULL){
        printf("%d", freq);
        printf("%c", data)
        head = &((*head)->next);
    }

    return 0;
}