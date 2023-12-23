#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Invalid argc\n");
        return 1;
    }

    FILE *stream = fopen(argv[1], "w");
    if (stream == NULL)
    {
        printf("Can not find file\n");
        return 1;
    }

    char temp_char;
    printf("CTRL+D to exit\n");
    while((temp_char = getc(stdin)) != EOF)
    {
        if (fputc(temp_char, stream) == EOF){
            printf("Error writing in file");
            break;
        }
    }

    if(fclose(stream) == EOF) {
        printf("Can not close file\n");
        return 1;
    }
    return 0;
}