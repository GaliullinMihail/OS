#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Invalid argc\n");
        return 1;
    }

    FILE *stream = fopen(argv[1], "r");
    if (stream == NULL)
    {
        printf("Can not find file\n");
        return 1;
    }
    int n = atoi(argv[2]);
    int counter = 0;
    char temp_char;

    while((temp_char = fgetc(stream)) != EOF)
    {
        fputc(temp_char, stdout);
        if (n!=0)
        {
            if (temp_char == '\n')
                counter++;
            
            if (counter == n)
            {
                fgetc(stdin);
                counter = 0;
            }
        }
    }

    if(fclose(stream) == EOF) {
        printf("Can not close file\n");
        return 1;
    }
    return 0;
}