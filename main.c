#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h> 

const char *text = ".txt";
const char *pic = ".bmp";

//========================================================================================================//

void BlankRemovalComp(char *fileNAME, char * baseCompNAME){
    FILE * file;
    file = fopen(fileNAME,"r");

    FILE * comp;
    char * compNAME;
    sprintf(compNAME, "compBR%s", baseCompNAME);
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

void comparison(struct NodePath *head, char * pathHeader, char * nameFile){
    FILE * header;
    header = fopen(pathHeader, "a");

    if( header == NULL ) {
        printf("Couldn't open %s\n", pathHeader);
        exit(1);
    }

    for (; head; head = head->next){
        char *comp= (head->c);
        char * test1 = strstr(comp, text);
        char * test2 = strstr(comp, pic);

        if (test1 || test2){
            printf("This is a file to compress : %s\n", comp);
            fprintf(header, "%s\n", comp);
            BlankRemovalComp(comp, nameFile);
        }
        else
            printf("This is not a file  to compress : %s\n", comp);
    }
    fclose(header);
}

//========================================================================================================//

void traversal(char *originPath, char * PathHeader)
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
            //printf("\n1e   %s\n", dp->d_name);//the name of the file :)

            PushPath(&head, path);
            comparison(head, PathHeader, dp->d_name);
            traversal(path, PathHeader);
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

    char username[50];
    printf("Please enter the session's user name : ");
    scanf("%s", username);

    char PathHeader[555];
    sprintf(PathHeader, "/home/%s/Desktop/FCtemporary/header.txt", username); //need just /home/%s/Desktop/FCtemporary
    //clean the header file text from last execution
    fclose(fopen(PathHeader, "w"));

    //string to put the path of the user
    char path[50];
    printf("\nPlease enter path the folder : ");
    scanf("%s", path);

    //fonction to get the .txt etc in the folder chosen
    traversal(path, PathHeader);

    return 0;
}
