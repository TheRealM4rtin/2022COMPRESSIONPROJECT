#include <stdio.h>
#include <string.h>
#include <dirent.h> 

void traversal(char *originPath)
{
    char path[1000];
    struct dirent *dp;
    DIR *directory = opendir(originPath);

   
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
            printf("%s\n", path);

            traversal(path);
        }
    }

    closedir(directory);
}


int main()
{
   
    char path[50]; 
    printf("Please enter path the folder : ");
    scanf("%s", path);

    traversal(path);

    return 0;
}

