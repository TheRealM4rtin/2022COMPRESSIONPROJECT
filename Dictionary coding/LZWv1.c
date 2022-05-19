/*
ENCODING
Let D be the dictionary
D-1(s) is the code in the dictionary assigned to the seq "s"
P is the seq to be coded :
                we denote the char at index i by P[i]
The concatenation of 2 strings c1 and c2 will be represented
                                        by c1 (+) c2

ENCODING ALGORITHM  buffer is a string, P too ...
Start
    buffer<--empty
    result<--empty
    While [we have not reached the end of P ( i< size(P) ) ] Do
        If (buffer(+)P[i] is in D) then                             concatenation
            buffer<--buffer(+)P[i]                                  concatenation
        Else
            Add D-1(buffer) to result
            Add buffer(+)P[i] to D                                  concatenation
            buffer<--P[i]
        EndIf
        i<--i+1
    EndWhile
    Add D-1(buffer) to result
End

*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char data;
    int id;
    struct node *next;
} *node;

node Create_node(){
    return NULL;
}

node Construct(int id, char data, node next){
    node new;
    new = (node)malloc(sizeof(struct node));
    if(!new) return 0;
    new->id = id;
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

void LZWComp(char *fileNAME, char *compNAME){
    FILE * file;
    FILE * comp;
    file = fopen(fileNAME,"r");
    comp = fopen(compNAME,"w");

    node** head;
    node* follow;
    

    char buffer, byteread;
    int buffer_byte = 0, repetition = 0, i = 256;
    byteread = getc(file); 
    buffer_byte = buffer + byteread;
    head = &(Construct(buffer_byte, byteread, NULL));

    while (!feof (file)){
        
        buffer_byte = buffer + byteread;
        
        

        if (is_in(buffer_byte, (*head)) == 0)
        {

            head = &(Construct(buffer_byte+256, byteread, NULL));
            printf("%c", buffer);
            byteread = getc(file);

        }else //si oui
        {
            buffer = byteread;
            byteread = getc(file);
        }

    }
    fclose(file);
    fclose(comp);
}

/*
DECODING
Let D be the dictionary
D(c) is the corresponding seq to the code "c" in dictionary
P' is the seq to be codes to be decoded :
                we denote the ith code by P'[i]
The concatenation of 2 strings c1 and c2 will be represented
                                        by c1 (+) c2

DECODING ALGORITHM
Start
    buffer<--empty
    result<--empty
    i<--0
    While [we have not reached the end of P' (i< size(P'))] Do
        tempString<--D(P'[i])
        If (buffer(+)tempString[0] is not in D) then                    concatenation
            Add buffer(+)tempString[0] to D                             concatenation
        EndIf
        result<--result(+)tempString                                    concatenation
        buffer<--tempString
        i<--i+1
    EndWhile
End
*/

/*
void LZWDecomp(char *compNAME, char *decompNAME){
    FILE * compfile;
    FILE * decompfile;
    compfile = fopen(compNAME,"r");
    decompfile = fopen(decompNAME,"w");

    char c;
    int repetition = 0;
    while (!feof (compfile)){
        c = getc(compfile);

        if ()
        {
            
        }



    }
    fclose(compfile);
    fclose(decompfile);
}
*/

int main(){
    char * fileNAME ="lzw.txt";
    char * compNAME = "compressedLZW.txt";
    char * decompNAME = "decompressLZW.txt";


    LZWComp(fileNAME, compNAME);
    //LZWDecomp(compNAME, decompNAME);

    return 0;
}
