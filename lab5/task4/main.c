#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Invalid argc\n");
        return 1;
    }

    if(chmod(argv[1], 0444) == -1)
    {
        printf("Can not get acess to read\n");
        return 1;
    }

    if (chmod(argv[2], 0222) == -1)
    {
        printf("Can not get access to write \n");
        return 1;
    }

    FILE *streamRead = fopen(argv[1], "r");
    FILE *streamWrite = fopen(argv[2], "w");
    if (streamRead == NULL)
    {
        printf("Can not find file to read\n");
        return 1;
    }

    if (streamWrite == NULL)
    {
        printf("Can not find file to write\n");
        fclose(streamRead);
        return 1;
    }
    char temp_char;

    while((temp_char = fgetc(streamRead)) != EOF)
    {
        fputc(temp_char, streamWrite);
    }

    if(fclose(streamRead) == EOF|| fclose(streamWrite) == EOF) {
        printf("Can not close file\n");
        return 1;
    }
    return 0;
}