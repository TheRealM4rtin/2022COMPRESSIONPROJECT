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

int is_in(int bufferplusbyte, struct node **head){

    for(; (*head)!=NULL;){
        if( (*head)->id == bufferplusbyte) return 1; //oui
        head = &((*head)->next);
    }
    return 0; // non
}

void occurency(char *fileNAME, char *letter[], int *freq[]){
    FILE * file;
    file = fopen(fileNAME,"r");

    char c1;
    int i = 0, j=0;

    c1 = getc(file);

    while (!feof (file)){
        c1 = getc(file);
        
        while (i < 500 && c1 != letter[i]) {
            i++;
        }
 
        if (i < 500) { //element found at i+1
            *freq[i+1]++;
        } else {        //element not found
            while (j < 500 && NULL != letter[i]) {
                i++;
            }
            if (j < 500) { //element found at i+1
                *letter[i+1]=c1;
                *freq[i+1]=1;
            }
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