#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h> 

const char *text = ".txt";
const char *pic = ".bmp";

//========================================================================================================//
/*
void BlankRemovalComp(char *fileNAME){
    FILE * file;
    FILE * comp;

    
    
    //maybe put header in the same directory
    //need a paper '-'
    

    char * compNAME = "compressed.txt";
    //char *compNAME="";
    //sprintf(compNAME, "compressed%s", fileNAME);
    file = fopen(fileNAME,"r");
    comp = fopen(compNAME,"w");

    char c;
    int space = 0;

    while ((c = getc(file)) != EOF)
    {
        if (c == ' '){
            space++;
        }else{
            if (space == 0){
                fprintf(comp, "%c", c);
            }
            if(space == 1){
                fprintf(comp, " ");
                fprintf(comp, "%c", c);
            }
            if (space == 2){
                fprintf(comp, "  ");
                fprintf(comp, "%c", c);
            }
            if (space >= 3){
                char temp[555];
                sprintf(temp, "$%d", space);
                fprintf(comp, "%s", temp);
                fprintf(comp, "%c", c);
            }
            space =0;
        }
    }
    fclose(file);
    fclose(comp);
}
*/
//========================================================================================================//

struct NodePath
{
    char* c;
    struct NodePath *next;
};

void print(struct NodePath *head)
{
    for (; head; head = head->next)
        printf(" - the string is %s\n", head->c);
}

void PushPath(struct NodePath **head, char* data)
{
    struct NodePath *temp = (struct NodePath *)malloc(sizeof(struct NodePath));
    temp->c = data;
    temp->next = NULL;
    *head = temp;
}

void comparison(struct NodePath *head){
    char *small = "~/Desktop/FCtemporary/header.txt";
    FILE * header;
    header = fopen(small, "a");

    if( header == NULL ) {
        printf("Couldn't open %s\n", small);
        exit(1);
    }
    //header = fopen("header.txt", "a");

    for (; head; head = head->next){
        char *comp= (head->c);
        char * test1 = strstr(comp, text);
        char * test2 = strstr(comp, pic);

        if (test1 || test2){
            printf("This is a file to compress : %s\n", comp);
            fprintf(header, "%s\n", comp);

            //BlankRemovalComp(comp);
        }
        else
            printf("This is not a file  to compress : %s\n", comp);
    }
    fclose(header);
}

//========================================================================================================//

void traversal(char *originPath)
{
    char path[1000];
    struct dirent *dp;
    DIR *directory = opendir(originPath);

    struct NodePath *head;

    if (!directory)
        return;

    while ((dp = readdir(directory)) != NULL)
    {
        //The strcmp() compares 2 strings char by char. If the strings are =, the fct returns 0.
        if (strcmp(dp->d_name, "..") != 0 && strcmp(dp->d_name, ".") != 0)
        {
            //The strcpy() fct copies the string pointed by 2 (including the null character) to 1
            strcpy(path, originPath); //copies originPath to path
            //the strcat() function contcatenates (joins) 2 strings. cat(destination, source);
            strcat(path, "/");
            strcat(path, dp->d_name);

            PushPath(&head, path);
            comparison(head);
            traversal(path);
        }
    }

    closedir(directory);
}

//========================================================================================================//

int main()
{
    system("mkdir ~/Desktop/FCtemporary");
    system("touch ~/Desktop/FCtemporary/header.txt");
    system("chmod +rw ~/Desktop/FCtemporary/header.txt");

    //string to put the path of the client
    char path[50];
    printf("Please enter path the folder : ");
    scanf("%s", path);

    //fonction to get the .txt etc in the folder chosen
    traversal(path);

    return 0;
}
