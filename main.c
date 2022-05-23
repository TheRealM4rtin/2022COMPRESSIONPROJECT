#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h> 

const char *text = ".txt";
const char *pic = ".bmp";

//========================================================================================================//

double compressionRate(char *fileNAME, char *compNAME){
    FILE * file;
    FILE * comp;
    file = fopen(fileNAME,"r");
    comp = fopen(compNAME,"r");

    char c;
    double I=0, F=0;
    double rate;

    while ((c = getc(file)) != EOF)
    {
        I++;
    }
    //printf("%f\n", I);

    while ((c = getc(comp)) != EOF)
    {
        F++;
    }
    //printf("%f\n", F);

    rate = (100-((F/I)*100));

    fclose(file);
    fclose(comp);
    return rate;
}

//========================================================================================================//

void BlankRemovalComp(char *fileNAME, char * baseCompNAME, char * pathTemp){
    FILE * file;
    file = fopen(fileNAME,"r");

    FILE * comp;
    char compNAME[500];
    sprintf(compNAME, "%s/compBR%s", pathTemp, baseCompNAME);
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

    double compRate;
    compRate = compressionRate(fileNAME, compNAME);

    FILE * stat;
    char statNAME[50];
    sprintf(statNAME, "%s/stat.txt", pathTemp);
    stat = fopen(statNAME, "a");

    char temp[555];
    sprintf(temp, "%s - %s - BR - Compression Rate : %f\n", fileNAME, compNAME, compRate);
    fprintf(stat, "%s", temp);
    //printf("%s", temp);

    fclose(stat);
}

void RLEComp(char *fileNAME, char *baseCompNAME, char *pathTemp){
    FILE * file;
    file = fopen(fileNAME,"r");

    FILE * comp;
    char compNAME[500];
    sprintf(compNAME, "%s/compRLE%s", pathTemp, baseCompNAME);
    comp = fopen(compNAME,"w");

    char c1, c2;
    int repetition = 0;
    c1 = getc(file);

    while (!feof (file)){
        c2 = getc(file);
        if (c1 == c2)
        {
            repetition++;
        }else{
            if (repetition==0)
            {
                fprintf(comp, "%c", c1);
            }else{
                if (repetition >= 3){
                    char temp3[500];
                    repetition++;
                    sprintf(temp3, "$%d%c", repetition, c1);
                    fprintf(comp, "%s", temp3);
                    repetition = 0;
                }
                if (repetition == 2){
                    fprintf(comp, "%c%c%c", c1, c1, c1);
                    repetition = 0;
                }
                if(repetition == 1){
                    fprintf(comp, "%c%c", c1, c1);
                    repetition = 0;
                }
            }
        }
        c1=c2;
    }
    fclose(file);
    fclose(comp);
    double compRate;

    compRate = compressionRate(fileNAME, compNAME);

    FILE * stat;
    char statNAME[50];
    sprintf(statNAME, "%s/stat.txt", pathTemp);
    stat = fopen(statNAME, "a");

    char temp[555];
    sprintf(temp, "%s - %s - RLE - Compression Rate : %f\n", fileNAME, compNAME, compRate);
    fprintf(stat, "%s", temp);
    //printf("%s", temp);

    fclose(stat);
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

//========================================================================================================//

void comparison(struct NodePath *head, char * pathHeader, char * nameFile){
    FILE * header;
    char realPathHeader[555];
    sprintf(realPathHeader, "%s/header.txt", pathHeader);
    header = fopen(realPathHeader, "a");

    if( header == NULL ) {
        printf("Couldn't open %s\n", realPathHeader);
        exit(1);
    }//else    printf("Could open %s\n",realPathHeader);

    for (; head; head = head->next){
        char *compar= (head->c);
        char * test1 = strstr(compar, text);
        char * test2 = strstr(compar, pic);

        if (test1 || test2){
            printf("This is a file to compress : %s\n", compar);
            fprintf(header, "%s\n", compar);
            BlankRemovalComp(compar, nameFile, pathHeader);
            RLEComp(compar, nameFile, pathHeader);
            //comparaison de compression rate
        }
        else
            printf("This is not a file  to compress : %s\n", compar);
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
    system("touch ~/Desktop/FCtemporary/stat.txt");

    char username[50];
    printf("Please enter the session's user name : ");
    scanf("%s", username);

    char PathHeader[555]="";
    sprintf(PathHeader, "/home/%s/Desktop/FCtemporary/header.txt", username);
    //clean the header file text from last execution
    fclose(fopen(PathHeader, "w"));

    char PathStat[555]="";
    sprintf(PathStat, "/home/%s/Desktop/FCtemporary/stat.txt", username);
    //clean the header file text from last execution
    fclose(fopen(PathStat, "w"));

    char fileTemp[555]="";
    sprintf(fileTemp, "/home/%s/Desktop/FCtemporary", username);

    //____________________________________________________

    //string to put the path of the user
    char path[50]="";
    printf("Please enter path the folder : ");
    scanf("%s", path);

    //fonction to get the .txt etc in the folder chosen
    traversal(path, fileTemp);

    return 0;
}
