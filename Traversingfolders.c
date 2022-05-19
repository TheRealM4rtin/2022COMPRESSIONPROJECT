#include <stdio.h>
#include <string.h>
#include <dirent.h> 

void myfilerecursive(char *basePath)
{
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);

   
    if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            printf("%s\n", dp->d_name);
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);

            myfilerecursive(path);
        }
    }

    closedir(dir);
}



int main()
{
   
    char user[50]; 
    printf("Please enter path the folder : ");
    scanf("%s", user);

    myfilerecursive(user);

    return 0;
}

