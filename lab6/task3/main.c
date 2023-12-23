#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 120
#define MAX_ARGUMENTS 20

int main() {
    char command[MAX_COMMAND_LENGTH];
    
    while (1) {
        char* arguments[MAX_ARGUMENTS];
        fgets(command, sizeof(command), stdin);

        if(strlen(command) < 1)
        {
            printf("can not uderstand comman with length < 1");
            continue;
        }
        
        command[strcspn(command, "\n")] = 0;
    
        int arg_count = 0;
        
        char* token = strtok(command, " ");
        while (token != NULL && arg_count < MAX_ARGUMENTS - 1) {
            arguments[arg_count] = token;
            arg_count++;
            token = strtok(NULL, " ");
        }
        arguments[arg_count] = NULL;
        pid_t pid = fork();

        if (pid == 0) {
            int result = execvp(arguments[0], arguments);
            
            if (result == -1) {
                perror("Can not execute");
                return 1;
            }
            return 0;
        } else {
            wait(NULL);
        }
    }
    
    return 0;
}
