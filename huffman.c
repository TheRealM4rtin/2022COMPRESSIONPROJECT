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

    char c;
    
    int i = 0, j=0;


    while (!feof (file)){
        c = getc(file);
        
        if (is_in(c, &head) == 1) {
            node->freq += 1;
        }
        if( is_in(c, &head) == 0){
            Construct(1, c, node->next);
        }
 
    }

    fclose(file);
}

int main(){
    char * fileNAME ="rle.txt";
    //float (*vals)[n] = malloc(sizeof(float[n]));

    char array[500];
    int freq[500];

    occurency(fileNAME, &array, &freq);
    for(int n = 0; n < 500; ++n) {
        printf("%d ", array[n]);
    }
    printf("\n");
    return 0;
}