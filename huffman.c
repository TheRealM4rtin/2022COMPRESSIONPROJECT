#include <stdio.h>
#include <stdlib.h>

typedef struct node {      //minHNode
    char data;
    int freq;
    struct node *next; //left and right dans internet2
} *node;

node Construct(int freq, char data, node next){
    node new;
    new = (node)malloc(sizeof(struct node));
    if(!new) return 0;
    new->freq = id;
    new->data = data;
    new->next = next;
    return new;
}

int is_in(int char, struct node **head){

    for(; (*head)!=NULL;){
        if( (*head)->id == char) return 1; //oui
        head = &((*head)->next);
    }
    return 0; // non
}

void occurency(char *fileNAME, struct node **head){
    FILE * file;
    file = fopen(fileNAME,"r");

    node** head;
    char c, onetimehead;
    
    /* we need to create the first node or the 
    head but only one time */
    onetimehead = getc(file);
    Construct(1, onetimehead, NULL);
    head = &

    while (!feof (file)){
        c = getc(file);
        
        if (is_in(c, &head) == 1) {
            node->freq += 1;
        }
        if( is_in(c, &head) == 0){
            Construct(1, c, NULL);
        }
 
    }

    fclose(file);
}

int main(){
    char * fileNAME ="rle.txt";


    occurency(fileNAME);

    for(int n = 0; n < 500; ++n) {
        printf("%d ", array[n]);
    }
    printf("\n");
    return 0;
}