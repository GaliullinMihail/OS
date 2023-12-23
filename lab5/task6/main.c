#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

void searchFile(char *dirPath, char *fileName, int *numDirectories, int *numFiles) {
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;
    char filePath[1000];

    dir = opendir(dirPath);
    if (dir == NULL) {
        printf("Can not open directory %s\n", dirPath);
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, "..") == 0 || strcmp(entry->d_name, ".") == 0) {
            continue;
        }
        
        sprintf(filePath, "%s/%s", dirPath, entry->d_name);
        lstat(filePath, &fileStat);

        if (S_ISDIR(fileStat.st_mode)) {
            (*numDirectories)++;
            searchFile(filePath, fileName, numDirectories, numFiles);
        } else if (S_ISREG(fileStat.st_mode)) {
            (*numFiles)++;

            if (strcmp(entry->d_name, fileName) == 0) {
                char buffer[80];
                strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&fileStat.st_ctime));
                printf("Path: %s\n", realpath(fileName, NULL));
                printf("Name: %s\n", entry->d_name);
                printf("Size: %ld bytes\n", fileStat.st_size);
                printf("Creation time: %s\n", buffer);
                printf("Permissions: %o\n", fileStat.st_mode & 0777);
                printf("Index number: %lu\n", fileStat.st_ino);
            }
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Invalid number of arguments\n");
        return 1;
    }

    int numDirectories = 0;
    int numFiles = 0;

    searchFile(argv[1], argv[2], &numDirectories, &numFiles);

    printf("Total directories: %d\n", numDirectories);
    printf("Total files: %d\n", numFiles);

    return 0;
}


