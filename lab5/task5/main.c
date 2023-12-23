#include <stdio.h>
#include <dirent.h>
#include <string.h>

void PrintDirectory(char* directory_path)
{
    DIR *dir;
    struct dirent *entry;
    dir = opendir(directory_path);

    if (dir == NULL)
    {
        printf("Can not open directory %s\n", directory_path);
        return;
    }
    
    while((entry = readdir(dir)) != NULL)
    {
        printf("%s\n", entry->d_name);
    }

    closedir(dir);
}

int main(int argc, char *argv[])
{
    DIR *dir;
    struct dirent *entry;

    if (argc != 2)
    {
        printf("Invalid argc\n");
        return 1;
    }
    printf("Directory form argument: \n");
    PrintDirectory(argv[1]);
    printf("Current directory: \n");
    PrintDirectory(".");
    return 0;
}