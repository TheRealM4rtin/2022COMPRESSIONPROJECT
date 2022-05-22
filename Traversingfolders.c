#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h> 

const char *text = ".txt";
const char *pic = ".bmp";

struct node
{
    char* c;
    struct node *next;
};

void print(struct node *head)
{
    for (; head; head = head->next)
        printf(" - the string is %s\n", head->c);
}

void Push(struct node **head, char* data)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->c = data;
    temp->next = NULL;
    *head = temp;
}

/*The strstr function takes two char pointer arguments,
the first denoting the string to search in
and the other denoting the string to search for.*/

void comparison(struct node *head){
    FILE * header;

    header = fopen("header.txt", "a");
    for (; head; head = head->next){
        char *comp= (head->c);

        char * test1 = strstr(comp, text);
        char * test2 = strstr(comp, pic);

        if (test1 || test2){
            printf("found file to compress : %s\n", comp);
            fprintf(header, "%s\n", comp);
        }
        else
            printf("This is a not to compress : %s\n", comp);

        /*if (test1)
            printf("found .txt file to compress : %s\n", comp);
        else if (test2)
            printf("found .bmp file to compress : %s\n", comp);
        else
            printf("This is a not to compress : %s\n", comp);*/
    }
    fclose(header);
}

void traversal(char *originPath)
{
    char path[1000];
    struct dirent *dp;
    DIR *directory = opendir(originPath);

    struct node *head;

    if (!directory) //empty
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

            Push(&head, path);
            comparison(head);
            traversal(path);
        }
    }
    closedir(directory);
}

int main()
{
    char path[50]; 
    fclose(fopen("header.txt", "w"));
    
    printf("Please enter path the folder : ");
    scanf("%s", path);
    traversal(path);

    return 0;
}

