#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/time.h>

void PrintfProcessInformation(char *processName) {
    pid_t pid = getpid();
    pid_t parent_pid = getppid();

    struct timeval ts;
    struct timezone tz;
    gettimeofday(&ts, &tz);
    printf("%s - PID: %d, PPID: %d, Current Time: %02d:%02d:%02d:%03d\n", 
    processName, pid, parent_pid, (int)((ts.tv_sec + 10800) / 3600 % 24), 
    (int)(ts.tv_sec / 60 % 60), (int)(ts.tv_sec % 60), (int)(ts.tv_usec / 1000));
}

int main(){
    pid_t child_first, child_second;

    child_first = fork();

    if (child_first == 0)
    {
        PrintfProcessInformation("child_first");
    }else {
        child_second = fork();
        if(child_second == 0)
        {
            PrintfProcessInformation("child_second");
        } else {
            PrintfProcessInformation("parent");
            system("ps -x");
            wait(NULL);
            wait(NULL);
        }
    }
    return 0;
}